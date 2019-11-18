
/********************************************************************************************
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


#include "ssocket_drv.hpp"
#include "project_ser.h"

/**
 * Initialization functionj for the the socket 
 * Should bind the socket and register the client with the server side application. 
 * 
 * @todo: aknuh add further function infromation
 * @reference https://github.com/spectre1989/odin/blob/c75d394ef2dfe9d71b8229836a304449f36e1940/code/client.cpp
 */
sSockDrv_c::sSockDrv_c() :
    lastFailed(0)
{
    // Initialize the winsock. 
    WORD winsock_version = SIO_WINSOCK_VER;

    // START UP WINSOCKET
    if( WSAStartup( winsock_version, &winsock_data ) )
    {
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! WSAStartup failed: %d", lastFailed);
        return;
    }

    // CREATE THE SOCKET
    sock = socket( SIO_ADDRESS_FAMILY, SIO_SOCKET_TYPE, SIO_SOCKET_PTCOL);

    if( sock == INVALID_SOCKET )
    {
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! socket creation failed: %d", lastFailed);
        return;
    }

    // BIND THE SOCKET
    localAddress.sin_family        = SIO_ADDRESS_FAMILY;
    localAddress.sin_port          = htons( SIO_PORT_BINDING );
    localAddress.sin_addr.s_addr   = INADDR_ANY;

    if ( bind (sock, (SOCKADDR*)&localAddress, sizeof(localAddress) ) == SOCKET_ERROR ) 
    {   
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! socket binding failed: %d", lastFailed);
        return;
    }
}

bool sSockDrv_c::sSock_RegisterClient()
{
    int revStatus; 
    int flags = 0;
    int32_t addressSize  = sizeof(clientAddress[0]);

    for(uint32_t i = 0; i < SIO_MAX_PLAYERS; i++)
    {
        std::cout<< "| Registering Client: " << i << "...\n";
        revStatus = recvfrom(sock, OPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&clientAddress[i], &addressSize );
        
        if( revStatus == SOCKET_ERROR )
        {
            printf( "recvfrom returned SOCKET_ERROR, WSAGetLastError() %d", WSAGetLastError() );
        }
        else
        {
            OPacketBuff[revStatus] = 0;
            printf( "%d.%d.%d.%d:%d - %s", clientAddress[i].sin_addr.S_un.S_un_b.s_b1, clientAddress[i].sin_addr.S_un.S_un_b.s_b2, clientAddress[i].sin_addr.S_un.S_un_b.s_b3, clientAddress[i].sin_addr.S_un.S_un_b.s_b4, clientAddress[i].sin_port, OPacketBuff );
        }
        std::cout<< "\n|\n| Successfully Registered Client: " << i << "...\n";
    }
    return true;
}

bool sSockDrv_c::sSock_SendData()
{
    bool flags = 0;
    if(SOCKET_ERROR == 
        sendto(sock, iPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&clientAddress, sizeof( clientAddress )))
    {
        lastFailed = WSAGetLastError();
        printf( "\n !ERROR: Sendto failed: %d\n", lastFailed);
        return false;
    }

    return true; 
}


bool sSockDrv_c::sSock_SendPacket(packetTypes_e mode)
{
    // clientPacket_t * const packetInfo = (clientPacket_t*) iPacketBuff;

    // packetInfo->contents[0].bits = 0;

    // switch (mode)
    // {
    //     case CLIENT_DATA:
    //         packetInfo->contents[0].data.type = CLIENT_DATA;

    //         break;
    //     case CLIENT_ACK:
    //         packetInfo->contents[0].data.type = CLIENT_ACK;

    //         break;

    //     case CLIENT_EXIT:
    //         packetInfo->contents[0].data.type = CLIENT_EXIT;

    //         break;
        
    //     case CLIENT_REG:
    //         packetInfo->contents[0].data.type = CLIENT_REG;

    //         if (!sSock_SendData())
    //         { 
    //             return false; 
    //         }
    //         break;
        
    //     default: // unknown mode detected
    //         return false; 
    // }

    return true;
}

void sSockDrv_c::sSock_RecieveData(uint64_t &input)
{

}


sSockDrv_c::~sSockDrv_c()
{
    // attempt to show last error condition before exit. 
    if(!lastFailed)
    {
        std::cout<< "LAST FAILED: " <<  lastFailed << std::endl;
    }
    WSACleanup();
}
