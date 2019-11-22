
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
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE           
    SOFTWARE.                                                                               
**************************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <conio.h> 
#include <ws2tcpip.h>


#include "csocket_drv.hpp"
#include "project_cli.h"
#include "display.h"

/**
 * Initialization functionj for the the socket 
 * Should bind the socket and register the client with the server side application. 
 * 
 * @todo: aknuh add further function infromation
 * @reference https://github.com/spectre1989/odin/blob/c75d394ef2dfe9d71b8229836a304449f36e1940/code/client.cpp
 */
cSockDrv_c::cSockDrv_c() :
    lastFailed(0)
{
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
}

bool cSockDrv_c::sSock_GetPacket()
{
    SOCKADDR_IN from;
    int32_t revStatus;     // todo consolidate
    int32_t addressSize  = sizeof(server_address);
    int32_t flags = 0; 

    revStatus = recvfrom(sock, iPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&from, &addressSize );
    if( revStatus == SOCKET_ERROR )
    {
        printf( "recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError() );
        return false; 
    }

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
        serverAddress = IP_ADDRESS_HOME;
        status = true;  // temp

        std::cout << "| Entered: "<< serverAddress << std::endl;
    }

    return serverAddress;
}

bool cSockDrv_c::cSock_RegisterClient()
{
    clientPacket_t * const iPacketInfo = (clientPacket_t*) iPacketBuff;
    std::string serverAddress; 
    SOCKADDR_IN from;
    bool repeat = false; 
    char p2Avatar;
    int32_t revStatus; 
    int32_t flags = 0;
    int32_t addressSize  = sizeof(serverAddress); // todo change these to class wide. 

    // GET SERVER IP ADDRESS
    serverAddress = cSock_GetIPAddress();
    
    char tempCArray[serverAddress.size() + 1];
    strcpy(tempCArray, serverAddress.c_str());

    server_address.sin_family = SIO_ADDRESS_FAMILY;
    server_address.sin_port = htons( SIO_PORT_BINDING );
    server_address.sin_addr.S_un.S_addr = inet_addr(tempCArray);  // find by command promt ipconfig


    std::cout << "|\n|_________________________________________________________________________________" << std::endl;
    std::cout << "| Sending Join request to server... ";

    // SEND JOIN REQUEST
    if (!cSock_SendPacket(CLIENT_REG))
    {
        return false; 
    }

    // RECIEVE CLIENT ID
    do
    {
        revStatus = recvfrom(sock, iPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&from, &addressSize );
        if( revStatus == SOCKET_ERROR )
        {
            printf( "recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError() );
            repeat = true; 
        }
        else
        {
            iPacketBuff[revStatus] = 0;

            if (iPacketInfo->header.data.type == CLIENT_REG)
            { // todo add checks for corret addy family and ports.
                dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance();
                clientInfo.clientID = iPacketInfo->header.data.clientID;

                if (clientInfo.clientID == CLIENT_1)
                {
                    p2Avatar = iPacketInfo->contents[CLIENT_2].data.avatar;
                }
                else if (clientInfo.clientID == CLIENT_2)
                {
                    p2Avatar = iPacketInfo->contents[CLIENT_1].data.avatar;
                }

                dConsoleDrv->Set_PlayerTwoAvatar(p2Avatar);

                std::cout<< "Success!\n";
                std::cout << "| You are player number: " << (uint32_t)clientInfo.clientID + 1;
                std::cout << "| Opponent chosen Avatar: " << p2Avatar;
            }
            else 
            {
                std::cout<< "   Failed!!\n";
                repeat = true; 
            }
            //printf( "%d.%d.%d.%d:%d - %s", clientAddress[i].sin_addr.S_un.S_un_b.s_b1, clientAddress[i].sin_addr.S_un.S_un_b.s_b2, clientAddress[i].sin_addr.S_un.S_un_b.s_b3, clientAddress[i].sin_addr.S_un.S_un_b.s_b4, clientAddress[i].sin_port, OPacketBuff );
        }
    } while (repeat);
    
    return true; 
}

bool cSockDrv_c::cSock_SendData()
{
    bool flags = 0;
    if(SOCKET_ERROR == 
        sendto(sock, OPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&server_address, sizeof( server_address )))
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
    clientID_e iD = (clientID_e) clientInfo.clientID;
//  ensure zerod packet contents
    packetInfo->contents[0].bits = 0;
    packetInfo->contents[1].bits = 0;
    packetInfo->header.bits = 0;

    packetInfo->header.data.type = mode;
    packetInfo->header.data.clientID = iD;

    switch (mode)
    {
        case CLIENT_DATA:
            packetInfo->contents[iD].data.x_loc = clientInfo.xLoc;
            packetInfo->contents[iD].data.y_loc = clientInfo.yLoc;
            packetInfo->contents[iD].data.shot  = (clientInfo.shotCounter == 1);
            packetInfo->contents[iD].data.sdir  = clientInfo.impInput;
            packetInfo->contents[iD].data.state = clientInfo.GAME_OVER;

            if (!cSock_SendData())
            { 
                return false; 
            }
            break;

        case CLIENT_ACK:

            break;

        case CLIENT_EXIT:

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
