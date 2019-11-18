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

// library includes
#include <iostream>
#include <stdint.h>
#include <winsock2.h>
#include <conio.h> // for kbhit and getch.

// program includes
#include "project_ser.h"
#include "ssocket_drv.hpp"


ServerInfo_t serverInfo;

bool Setup_Game()
{
    sSockDrv_c * sSockDriver    = sSockDriver_Handle::Handler_GetInstance();

    if( sSockDriver->sSock_RegisterClient() == false)
    {
        return false; 
    }
}

int main(int argc, char const *argv[])
{
    if (!Setup_Game())
    {
        std::cout << "| Failed to setup game" << std::endl;
        exit(0);
    }

    while(serverInfo.GAME_OVER)
    {

        if (_kbhit() && _getch() == 't')
        {
            break;
        }
    }

    exit(0);
}

