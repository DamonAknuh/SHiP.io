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

#ifndef __SOCKET_DRV_H
#define __SOCKET_DRV_H

// Library Includes
#include <stdint.h>
#include <winsock2.h>

// Program Includes. 
#include "project.h"

/**
 * PLACE HOLDER FOR CLASS INFORMATION
 * 
 * @TODO: aknuh add class infromation
 */
class cSockDriver_c
{
public:
    
    cSockDriver_c();
    ~cSockDriver_c();
    bool cSock_RegisterClient();    ///< Parses image header information
    void cSock_SendData(uint64_t input);     ///< Stores Pixel Array and information
    void cSock_RecieveData();   ///< Manipulates the bmp file into pixel Art.    

private:

    uint8_t clientID; 
    SOCKET sock; 
    SOCKADDR_IN local_address;
};

typedef handler_c<cSockDriver_c> cSockDriver_Handle;


#endif // __SOCKET_DRV_H