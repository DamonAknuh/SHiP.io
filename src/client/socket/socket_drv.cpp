
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


#include "socket_drv.hpp"

/**
 * Initialization functionj for the the socket 
 * Should bind the socket and register the client with the server side application. 
 * 
 * @todo: aknuh add further function infromation
 * @reference https://github.com/spectre1989/odin/blob/c75d394ef2dfe9d71b8229836a304449f36e1940/code/client.cpp
 */
cSockDrv_c::cSockDrv_c()
{
    // Initialize the winsock. 
    WORD winsock_version = SIO_WINSOCK_VER;
    WSADATA winsock_data;

    if( WSAStartup( winsock_version, &winsock_data ) )
    {
        printf( "\n| ERROR! WSAStartup failed: %d", WSAGetLastError() );
        exit(0);
    }

    sock = socket( SIO_ADDRESS_FAMILY, SIO_SOCKET_TYPE, SIO_SOCKET_PTCOL);

    if( sock == INVALID_SOCKET )
    {
        printf( "\n| ERROR! socket failed: %d", WSAGetLastError() );
        exit(0);
    }
}

bool cSockDrv_c::cSock_RegisterClient()
{
    bool status = false; 
    std::string serverAddress; 
    std::cout << "| Enter the IP address of the server: \n";

    // SET PLAYER ONE CHARACTER
    while(!status)
    {
        std::cout << "| --> Note: Input must in form of [ddd.ddd.ddd.ddd]\n";
        while(!_kbhit()){} // wait for input 
        // std::cin>>serverAddress;// "192.168.0.17" 
        // status = validateIPAddress(serverAddress); //@todo: 
        serverAddress = "192.168.0.17";
        status = true; 

        std::cout << "| Entered: "<< serverAddress << std::endl;
    }
    char tempCArray[serverAddress.size() + 1];
    strcpy(tempCArray, serverAddress.c_str());
    server_address.sin_addr.S_un.S_addr = inet_addr(tempCArray);  // find by command promt ipconfig

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
