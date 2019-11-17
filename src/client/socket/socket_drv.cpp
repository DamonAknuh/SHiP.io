
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

#include <stdio.h>
#include "socket_drv.hpp"


/**
 * Initialization functionj for the the socket 
 * Should bind the socket and register the client with the server side application. 
 * 
 * @todo: aknuh add further function infromation
 */
cSockDrv_c::cSockDrv_c()
{
    // Initialize the winsock. 
    WORD winsock_version = SIO_WINSOCK_VER;
    WSADATA winsock_data;

    if( WSAStartup( winsock_version, &winsock_data ) )
    {
        printf( "WSAStartup failed: %d", WSAGetLastError() );
        exit(0);
    }

    sock = socket( SIO_ADDRESS_FAMILY, SIO_SOCKET_TYPE, SIO_SOCKET_PTCOL);

    if( sock == INVALID_SOCKET )
    {
        printf( "ERROR! socket failed: %d", WSAGetLastError() );
        exit(0);
    }

}

bool cSockDrv_c::cSock_RegisterClient()
{
    return true; 
}


void cSockDrv_c::cSock_SendData(uint64_t input)
{

}

void cSockDrv_c::cSock_RecieveData(uint64_t &input)
{

}


cSockDrv_c::~cSockDrv_c()
{

    WSACleanup();
}
