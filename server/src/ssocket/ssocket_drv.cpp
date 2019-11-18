
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
        exit(0);
    }

    // CREATE THE SOCKET
    sock = socket( SIO_ADDRESS_FAMILY, SIO_SOCKET_TYPE, SIO_SOCKET_PTCOL);

    if( sock == INVALID_SOCKET )
    {
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! socket failed: %d", lastFailed);
        exit(0);
    }

    // BIND THE SOCKET
    if ( bind (sock, (SOCKADDR*)&local_address, sizeof(local_address) ) == SOCKET_ERROR ) 
    {   
        lastFailed = WSAGetLastError();
        printf( "\n| ERROR! socket failed: %d", lastFailed);
        exit(0);
    }
}

bool sSockDrv_c::sSock_RegisterClient()
{



    return true;
}

bool sSockDrv_c::sSock_SendData()
{
    bool flags = 0;
    if(SOCKET_ERROR == 
        sendto(sock, iPacketBuff, SIO_PACKET_SIZE, flags, (SOCKADDR*)&local_address, sizeof( local_address )))
    {
        printf( "\n !ERROR: Sendto failed: %d\n", WSAGetLastError());
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
