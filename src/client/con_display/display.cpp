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
// library includes.
#include <iostream>
#include <stdint.h>
#include <conio.h> // for kbhit and getch.

// program includes
#include "project_cli.h"
#include "display.h"

char dConsoleDrv_c::ShotHandler(uint32_t row, uint32_t col)
{
    switch (clientInfo.impInput)
    {
        case IO_UP:
                if ( (row < clientInfo.yLoc) && (col == clientInfo.xLoc))
                {
                    return '|';
                }
            break;
        
        case IO_DOWN:
                if ((row > clientInfo.yLoc) &&  (col == clientInfo.xLoc))
                {
                    return '|';
                }
            break;

        case IO_LEFT:
                if ((col < clientInfo.xLoc) && (row == clientInfo.yLoc))
                {
                    return '-';
                }
            break;

        case IO_RIGHT:
                if ((col > clientInfo.xLoc) && (row == clientInfo.yLoc))
                {
                    return '-';
                }
            break;
            
        default:
            break;
    }
    return ' ';
}


/*
 *  Checks if settting avatar character is a valid avatar character. 
 * 
 * Invalid inputs: X, |, -, _, or control chacters
 * 
 * @return true if valid and false if invalid. 
 * 
**/
bool dConsoleDrv_c::ValidateAvatar(char avatar)
{
    if ( (avatar == ' ') || (avatar == '|') || (avatar == '-') || (avatar == '_') || (iscntrl(avatar)) )
    {
        return false;
    }
    
    return true; 
}



bool dConsoleDrv_c::Set_PlayerTwoAvatar(char avatar)
{
    if (ValidateAvatar(avatar))
    {
        player2 = avatar;
        return true; 
    }

    return false; 
}

bool dConsoleDrv_c::Set_PlayerOneAvatar(char avatar)
{
    if (ValidateAvatar(avatar))
    {
        player1 = avatar;
        return true; 
    }

    return false; 
}

void dConsoleDrv_c::Draw_Game()
{
    // clear console window.
    system ("cls");

    // Draw first border. 
    for (uint32_t col = 0; col < GAME_SIZE; col++)
    {
        std::cout << "_";
    }
    std::cout << std::endl;

    // draw main output
    for (uint32_t row = 0; row < GAME_SIZE; row++)
    {
        for (uint32_t col = 0; col < GAME_SIZE; col++)
        {
            if (col == 0 || col == (GAME_SIZE-1)) // Draw vert borders
            {
                std::cout << "|";
            }
            else if (row == clientInfo.yLoc && col == clientInfo.xLoc) // Draw Player1
            {
                std::cout << player1;
            }
            else if (row == clientInfo.fyLoc && col == clientInfo.fxLoc) // Draw Fruit
            {
                std::cout << "+";
            }
            else if(row == clientInfo.pyLoc && col == clientInfo.pxLoc) // Draw Player2
            {
                std::cout << player2;
            }
            else if(clientInfo.shotCounter)
            {
                std::cout << ShotHandler(row, col);
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // print bottom  border
    std::cout << "|";
    for (uint32_t col = 0; col < GAME_SIZE - 2; col++)
    {
        std::cout << "_";
    }
    std::cout << "|";

    std::cout << std::endl;

    std::cout << "Weapons to deploy: " << (uint32_t)clientInfo.weapons << std::endl;

    // ensure that the shot only stays on screen for certain amount of frames. 
    if (clientInfo.shotCounter)
    {
        if ( clientInfo.shotCounter > SHOT_MAX_FRAMES)
        {
            clientInfo.shotCounter = 0;
        }
        else
        {
            clientInfo.shotCounter++; 
        }
        
    }

    // Sleep(10);
}

void dConsoleDrv_c::Setup_Avatars()
{
    bool status = false; 
    char chInput;

    std::cout << "| Please Input a character for your ship\n";

    // SET PLAYER ONE CHARACTER
    while(!status)
    {
        std::cout << "| --> Note: Input must be an non-control character and not one of: '-' , '|' , '_ ' , ' '\n";
        while(!_kbhit()){} // wait for input 
        chInput = _getch();
        status = Set_PlayerOneAvatar(chInput);
        std::cout << "| Entered: "<< chInput << std::endl;
    }

    // SET PLAYER TWO CHARACTER
    status = false; 
    std::cout << "\n|\n| Please Input a character for your enemy ship\n";

    while(!status)
    {
        std::cout << "| --> Note: Input must be an non-control character and not one of: [-|_s ]'\n";
        while(!_kbhit()){} // wait for input 
        chInput = _getch();
        status = Set_PlayerTwoAvatar(chInput);
        std::cout << "| Entered: "<< chInput << std::endl;
    }
}

dConsoleDrv_c::dConsoleDrv_c() :
    player1(DEFAULT_P1),
    player2(DEFAULT_P2)
{

}

dConsoleDrv_c::~dConsoleDrv_c()
{
}
