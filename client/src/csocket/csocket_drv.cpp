
/********************************************************************************************
    MIT License                                                                             
    Copyright (c) 2019 Damon Hunka                                                          
                                                                                           
    Permission is hereby granted, free of charge, to any person obtaining a copy            
    of this software and associated documentation files (the "Software"), to deal           
    in the Software without restriction, including without limitation the rights            
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell               
    copies of the Software, and to permit persons to whom the Software is                   
    furnished to do so, subject to the following conditions:                                
                                                                                          
    The above copyright notice and this permission notice shall be included in all          
    copies or substantial portions of the Software.                                         
                                                                                         
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR              
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE             
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                  
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,           
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER D`EALINGS IN THE           
    SOFTWARE.                                                                               
**************************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <conio.h> 
#include <ws2tcpip.h>


#include "csocket_drv.hpp"
#include "project_cli.hpp"
#include "display.hpp"

/**
 * Initialization functionj for the the socket 
 * Should bind the socket and register the client with the server side application. 
 * 
 * @todo: aknuh add further function infromation
 * @reference https://github.com/spectre1989/odin/blob/c75d394ef2dfe9d71b8229836a304449f36e1940/code/client.cpp
 */
cSockDrv_c::cSockDrv_c() :
    lastFailed(0),
    m_Flags(0)
{
    SOCKET sock;
    // Initialize the winsock. 
    WORD winsock_version = SIO_WINSOCK_VER;

    if( WSAStartup( winsock_version, &winsock_data ) )
    {
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! WSAStartup failed: %d", lastFailed);
        exit(0);
    }

    sock = socket( SIO_ADDRESS_FAMILY, SIO_SOCKET_TYPE, SIO_SOCKET_PTCOL);

    if( sock == INVALID_SOCKET )
    {
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! socket failed: %d", lastFailed);
        exit(0);
    }

    m_Sock.handle = sock;
    m_AddressSize = sizeof(server_address);

    
    server_address.sin_family           = SIO_ADDRESS_FAMILY;
    server_address.sin_port             = htons( SIO_PORT_BINDING );
    server_address.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS_EFF);  // find by command promt ipconfig

}


bool cSockDrv_c::cSock_RegisterClient()
{
    clientPacket_t * const iPacketInfo = (clientPacket_t*) iPacketBuff;
    std::string serverAddress; 

    bool repeat = false; 
    char p2Avatar;
    int32_t revStatus; 

    // GET SERVER IP ADDRESS
    serverAddress = cSock_GetIPAddress();
    
    char tempCArray[serverAddress.size() + 1];
    strcpy(tempCArray, serverAddress.c_str());

    server_address.sin_family   = SIO_ADDRESS_FAMILY;
    server_address.sin_port     = htons( SIO_PORT_BINDING );
    server_address.sin_addr.S_un.S_addr = inet_addr(tempCArray);  // find by command promt ipconfig


    std::cout << "|\n|_________________________________________________________________________________" << std::endl;
    std::cout << "| Sending Join request to server... " << std::endl;

    // SEND JOIN REQUEST
    if (!cSock_SendPacket(CLIENT_REG))
    {
        return false; 
    }

    // RECIEVE CLIENT ID
    do
    {
        revStatus = recvfrom(m_Sock.handle, iPacketBuff, SIO_PACKET_SIZE, m_Flags, (SOCKADDR*)&from, &m_AddressSize );
        if( revStatus == SOCKET_ERROR)
        {
            if (WSAGetLastError()  !=  SIO_WOULD_BLOCK_ERR){
                std::cout << "| ERROR Registering recvfrom returned: " << WSAGetLastError() << std::endl;
            }
            repeat = true; 
        }
        else
        {
            if (iPacketInfo->header.data.type == CLIENT_REG)
            { // todo add checks for corret addy family and ports.
                dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance();
                g_ClientID = (clientID_e) iPacketInfo->header.data.clientID;

                if (g_ClientID == CLIENT_1)
                {
                    p2Avatar = iPacketInfo->contents[CLIENT_2].data.avatar;
                    g_pClientID = CLIENT_2;
                }
                else if (g_ClientID == CLIENT_2)
                {
                    p2Avatar = iPacketInfo->contents[CLIENT_1].data.avatar;
                    g_pClientID = CLIENT_1;
                }

                dConsoleDrv->Set_PlayerTwoAvatar(p2Avatar);

                std::cout << "| Success!\n";
                std::cout << "| You are player number: " << (uint32_t)g_ClientID + 1  << std::endl;
                std::cout << "| Opponent chosen Avatar: " << p2Avatar;
                repeat = false;
            }
            else 
            {
                std::cout<< "| Unexpected Packet Type [" << iPacketInfo->header.data.type <<  "], retrying...\n";
                repeat = true; 
            }
        }
    } while (repeat);

    u_long enable = 1; 
    revStatus = ioctlsocket(m_Sock.handle, FIONBIO , &enable);
    if( revStatus == SOCKET_ERROR )
    {
        std::cout << "| ERROR ioctlsocket returned: " << WSAGetLastError() << std::endl;
        repeat = true; 
    }

    return true; 
}


bool cSockDrv_c::sSock_GetPacket()
{
    clientPacket_t * const packetInfo  = (clientPacket_t*) iPacketBuff;
    packetInfo->contents[0].bits = 0;
    packetInfo->contents[1].bits = 0;
    packetInfo->header.bits = 0;

    SOCKADDR_IN from;
    int32_t revStatus;     // todo consolidate

    revStatus = recvfrom(m_Sock.handle, iPacketBuff, SIO_PACKET_SIZE, m_Flags, (SOCKADDR*)&from, &m_AddressSize );

    if( revStatus == SOCKET_ERROR)
    {
        return false; 
    }
    //todo: damonhunka do error condition for non-blocking shit
    return true;
}

std::string cSockDrv_c::cSock_GetIPAddress()
{
    std::string serverAddress;
    bool status = false; 
    std::cout << "|\n|_________________________________________________________________________________" << std::endl;
    std::cout << "| Enter the IP address of the server: \n";

    while(!status)
    {
        std::cout << "| --> Note: Input must in form of [ddd.ddd.ddd.ddd]\n";
        while(!_kbhit()){} // wait for input 
        // std::cin>>serverAddress;// "192.168.0.17" 
        // status = validateIPAddress(serverAddress); //@todo: 
        serverAddress = IP_ADDRESS_EFF;
        status = true;  // temp

        std::cout << "| Entered: "<< serverAddress << std::endl;
    }

    return serverAddress;
}

bool cSockDrv_c::cSock_SendData()
{
    if(SOCKET_ERROR == 
        sendto(m_Sock.handle, OPacketBuff, SIO_PACKET_SIZE, m_Flags, (SOCKADDR*)&server_address, sizeof( server_address )))
    {
        printf( "\n !ERROR: Sendto failed: %d\n", WSAGetLastError());
        return false;
    }

    return true; 
}


bool cSockDrv_c::cSock_SendPacket(packetTypes_e mode)
{
    dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance(); // @todo: Architectural violation
    clientPacket_t * const packetInfo = (clientPacket_t*) OPacketBuff;
    clientID_e iD = (clientID_e) g_ClientID;
//  ensure zerod packet contents
    packetInfo->contents[0].bits = 0;
    packetInfo->contents[1].bits = 0;
    packetInfo->header.bits = 0;

    packetInfo->header.data.type = mode;
    packetInfo->header.data.clientID = iD;

    switch (mode)
    {
        case CLIENT_DATA:
            packetInfo->contents[iD].data.x_loc = clientInfo.pInfo[iD].xLoc;
            packetInfo->contents[iD].data.y_loc = clientInfo.pInfo[iD].yLoc;
            packetInfo->contents[iD].data.shot  = !!(clientInfo.shotCounter); // mask to 2 bits.
            packetInfo->contents[iD].data.sdir  = clientInfo.impInput;
            packetInfo->contents[iD].data.state = clientInfo.GAME_OVER;

            if (!cSock_SendData())
            { 
                return false; 
            }
            break;

        case CLIENT_SCRS:
            if (!cSock_SendData())
            { 
                return false; 
            }
            break;

        case CLIENT_EXIT:
            packetInfo->contents[iD].data.shot  = !!(clientInfo.shotCounter); // mask to 2 bits.
            packetInfo->contents[iD].data.sdir  = clientInfo.impInput;
            if (!cSock_SendData())
            { 
                return false; 
            }
            break;
        
        case CLIENT_REG:
            packetInfo->header.data.response = dConsoleDrv->player1; // send avatar information

            if (!cSock_SendData())
            { 
                return false; 
            }
            break;
        
        default: // unknown mode detected
            return false; 
    }

    return true;
}

void cSockDrv_c::cSock_RecieveData(uint64_t &input)
{

}


cSockDrv_c::~cSockDrv_c()
{
    // attempt to show last error condition before exit. 
    if(!lastFailed)
    {
        std::cout<< "LAST FAILED: " <<  lastFailed << std::endl;
    }

    WSACleanup();
}
