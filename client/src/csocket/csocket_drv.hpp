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

#ifndef __SOCKET_DRV_H
#define __SOCKET_DRV_H

// Library Includes
#include <stdint.h>
#include <winsock2.h>

// Program Includes. 
#include "project_cli.h"


#define IP_ADDRESS_HOME "192.168.0.17"
#define IP_ADDRESS_ECS  "134.87.162.25"
#define IP_ADDRESS_SCHL "134.87.162.25" 


/**
 * PLACE HOLDER FOR CLASS INFORMATION
 * 
 * @TODO: aknuh add class infromation
 */
class cSockDrv_c
{
public:
    
    cSockDrv_c();
    ~cSockDrv_c();
    bool cSock_RegisterClient();
    bool cSock_SendPacket(packetTypes_e mode);
    void cSock_RecieveData(uint64_t &input);

private:
    bool cSock_SendData();
    std::string cSock_GetIPAddress();


private:
    SOCKET sock; 
    SOCKADDR_IN server_address;
    WSADATA winsock_data;
    char OPacketBuff[SIO_PACKET_SIZE];
    char iPacketBuff[SIO_PACKET_SIZE];
    uint32_t lastFailed; 
};

typedef handler_c<cSockDrv_c> cSockDrv_Handle;


#endif // __SOCKET_DRV_H