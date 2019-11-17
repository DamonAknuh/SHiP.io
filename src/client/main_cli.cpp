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


// Libary Includes
#include <iostream>
#include <stdint.h>
#include <winsock2.h> // for socket implementation. 
#include <stdbool.h>
#include <conio.h> // for kbhit and getch.
#include <windows.h>


// Customized Includes
#include "../project.h"
#include "project_cli.h"
#include "socket_drv.hpp"
#include "logic.h"
#include "display.h"

clientInfo_t clientInfo;

bool SetupGame()
{
    // Driver instantiation and registeration.
    // Socket Driver
    cSockDrv_c * cSockDriver    = cSockDriver_Handle::Handler_GetInstance();
    // Game object Driver
    cGObjDrv_c * cGObjDrv       = cGObjDrv_Handle::Handler_GetInstance();
    // Output driver
    dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance();

    // input functiont to grab the ASCII characters to represent the ships. 
    dConsoleDrv->Setup_Avatars();
    
    // register cleitn program with the server application. 
    if( cSockDriver->cSock_RegisterClient() == false)
    {
        return false; 
    }

    if (cGObjDrv->cGObj_InitCInfo() == false)
    {
        return false; 
    }

    return true;
}


// http://paste4btc.com/Lu9Cvpd9
// https://www.youtube.com/watch?v=E_-lMZDi7Uw
void Draw_Game()
{
    dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance();

    dConsoleDrv->Draw_Game();
}

void Get_Input()
{
    clientInfo.input = IO_NULL; // no IO detected

    char inputCh; 
    if (_kbhit())
    {
        inputCh = _getch(); 

        switch (inputCh)
        {
        case 'a':
            clientInfo.input  = IO_LEFT;
            break;
        case 'd':
            clientInfo.input  = IO_RIGHT;
            break;
        case 'w':
            clientInfo.input  = IO_UP;
            break;
        case 's':
            clientInfo.input  = IO_DOWN;
            break;
        case ' ':
            clientInfo.input  = IO_SHOOT;
            break;
        case 't':
            clientInfo.input  = IO_EXIT;
            break;
        }
    }
}

void Send_Data()
{

}

int main(int argc, char const *argv[])
{
    std::cout << "WELCOME TO THE SHiP.IO GAME!\n|\n";
    // Game Initialization;
    if (!SetupGame())
    {
        printf("ERROR: Setup Game Failed");
        exit(0);
    }
    
    // main game loop
    while(!clientInfo.GAME_OVER)
    {
        Draw_Game();
        Get_Input();
        Calculate_GameState();
        Send_Data();

        Sleep(5);
    }

    return 0;
}

