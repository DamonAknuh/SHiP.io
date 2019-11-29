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
#include "project_cli.hpp"


#define IP_ADDRESS_HOME "192.168.0.17"
#define IP_ADDRESS_ECS  "134.87.162.25"
#define IP_ADDRESS_SCHL "134.87.162.25" 
#define IP_ADDRESS_ELW  "134.87.161.7"

#define IP_ADDRESS_355  "134.87.165.226"


#define IP_ADDRESS_EFF  IP_ADDRESS_355

typedef struct 
{
    SOCKET handle;
}mySocket;


/**
 * PLACE HOLDER FOR CLASS INFORMATION
 * 
 * @TODO: aknuh add class infromation
 */
class cSockDrv_c
{
private:
    bool cSock_SendData();
    std::string cSock_GetIPAddress();

private:

    bool m_UnRegistered;
    mySocket m_Sock; 
    SOCKADDR_IN server_address;
    SOCKADDR_IN from; 
    WSADATA winsock_data;
    

    uint32_t lastFailed; 
    int32_t  m_Flags;
    int32_t  m_AddressSize;
    char OPacketBuff[SIO_PACKET_SIZE];

public:
    char iPacketBuff[SIO_PACKET_SIZE];

public:
    
    cSockDrv_c();
    ~cSockDrv_c();
    bool cSock_RegisterClient();
    bool cSock_SendPacket(packetTypes_e mode);
    void cSock_RecieveData(uint64_t &input);
    bool sSock_GetPacket();

};

typedef handler_c<cSockDrv_c> cSockDrv_Handle;


#endif // __SOCKET_DRV_H