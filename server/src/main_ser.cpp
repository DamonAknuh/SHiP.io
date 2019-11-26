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

// library includes
#include <iostream>
#include <stdint.h>
#include <winsock2.h>
#include <conio.h> // for kbhit and getch.

// program includes
#include "project_ser.hpp"
#include "slogic.hpp"
#include "ssocket_drv.hpp"


ServerInfo_t serverInfo;

bool Setup_Game()
{
    sSockDrv_c * sSockDriver    = sSockDrv_Handle::Handler_GetInstance();

    if( sSockDriver->sSock_RegisterClient() == false)
    {
        return false; 
    }
    sLogicDrv_c * sLogicDrv    = sLogicDrv_Handle::Handler_GetInstance();

    if ( sLogicDrv->sLogic_InitSInfo() == false)
    {
        return false; 
    }
    return true;
}

int main(int argc, char const *argv[])
{
    std::cout << std::endl;
    std::cout << "________________________________" << std::endl;
    std::cout << "|---------~!WELCOME!~----------|" << std::endl;
    std::cout << "|------------------------------|" << std::endl;
    std::cout << "|---------TO SHiP.IO-----------|" << std::endl;
    std::cout << "|-----------SERVER-------------|" << std::endl;
    std::cout << "|______________________________|_____________________" << std::endl;

    if (!Setup_Game())
    {
        std::cout << "| Failed to setup game" << std::endl;
        exit(0);
    }

    std::cout << "________________________________" << std::endl;
    std::cout << "|-------~FINISHED SETUP~-------|" << std::endl;
    std::cout << "|______________________________|" << std::endl;

    while(!serverInfo.GAME_OVER)
    {
        if (_kbhit() && _getch() == 't')
        {
            break;
        }

        Update_GameState();
        Update_Clients();
    }

    exit(0);
}

