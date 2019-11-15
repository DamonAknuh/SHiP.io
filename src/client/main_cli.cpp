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

// GLOBAL VARIABLE.
// TODO: extern in header file. 
bool GAME_OVER = false;
clientInfo_t clientInfo;

bool SetupGame()
{
    // Driver instantiation and registeration.
    cSockDriver_c * cSockDriver = cSockDriver_Handle::Handler_GetInstance();


    clientInfo.GAME_OVER = false; 


    clientInfo.fxLoc = (rand() % EFF_GAME_SIZE) + 1;
    clientInfo.fyLoc = (rand() % EFF_GAME_SIZE) + 1;
    clientInfo.weapons = 0;  

    // temporary untill can handle it in sock initialization.
    clientInfo.xLoc = 5;
    clientInfo.yLoc = 5; 
    clientInfo.pxLoc = 15;
    clientInfo.pyLoc = 15;


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
    for (uint32_t col = 0; col < GAME_SIZE; col++)
    {
        std::cout << "_";
    }
    std::cout << std::endl;

    for (uint32_t row = 0; row < GAME_SIZE; row++)
    {
        for (uint32_t col = 0; col < GAME_SIZE; col++)
        {
            if (col == 0 || col == (GAME_SIZE-1)) // draw vert borders
            {
                std::cout << "|";
            }
            else if (row == clientInfo.yLoc && col == clientInfo.xLoc)
            {
                std::cout << "O";
            }
            else if (row == clientInfo.fyLoc && col == clientInfo.fxLoc)
            {
                std::cout << "+";
            }
            else if(row == clientInfo.pyLoc && col == clientInfo.pxLoc)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for (uint32_t col = 0; col < GAME_SIZE; col++)
    {
        std::cout << "_";
    }
    std::cout << std::endl;

    std::cout << "Weapons to deploy: " << clientInfo.weapons << std::endl;
    Sleep(10);
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

