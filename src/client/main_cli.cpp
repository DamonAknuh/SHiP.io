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


// Customized Includes
#include "../project.h"
#include "project_cli.h"
#include "socket_drv.hpp"
#include "logic.h"

// GLOBAL VARIABLE.
// TODO: extern in header file. 
bool GAME_OVER = false;
clientInfo_t clientInfo;

bool SetupGame()
{
    // Driver instantiation and registeration.
    cSockDriver_c * cSockDriver = cSockDriver_Handle::Handler_GetInstance();


    GAME_OVER = false; 

    clientInfo.xLoc = 5;
    clientInfo.yLoc = 5; 
    clientInfo.fxLoc = 25;
    clientInfo.fyLoc = 25; 
    clientInfo.weapons = 0; 

    clientInfo.input = IO_NULL;

    // register cleitn program with the server application. 
    if( cSockDriver->cSock_RegisterClient() == false)
    {
        return false; 
    }

    return true;
}


// http://paste4btc.com/Lu9Cvpd9
// https://www.youtube.com/watch?v=E_-lMZDi7Uw
void Draw_Game()
{
    // clear console window.
    system ("cls");

    // Draw first border. 
    for (uint32_t i = 0; i < GAME_SIZE+2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (uint32_t i = 0; i < GAME_SIZE; i++)
    {
        for (uint32_t j = 0; j < GAME_SIZE; j++)
        {
            if (j == 0)
            {
                std::cout << "#";
            }
            if (i == clientInfo.yLoc && j == clientInfo.xLoc)
            {
                std::cout << "O";
            }
            else if (i == clientInfo.fyLoc && j == clientInfo.fxLoc)
            {
                std::cout << "F";
            }
            else
            {
                std::cout << " ";
            }


            if (j == GAME_SIZE - 1)
            {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }

    for (uint32_t i = 0; i < GAME_SIZE+2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    std::cout << "Weapons to deploy: " << clientInfo.weapons << std::endl;
}

void Get_Input()
{
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
        default:
            clientInfo.input = IO_NULL;
            break;
        }
    }
}

void Send_Data()
{

}

int main(int argc, char const *argv[])
{
    // Game Initialization;
    if (!SetupGame())
    {
        printf("ERROR: Setup Game Failed");
    }
    
    // main game loop
    while(!GAME_OVER)
    {
        Draw_Game();
        Get_Input();
        Calculate_GameState();
        Send_Data(); 
    }

    return 0;
}

