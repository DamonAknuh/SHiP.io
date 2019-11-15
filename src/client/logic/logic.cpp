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


#include "project_cli.h"
#include "project.h"
#include "logic.h"

#include <cstdlib>

void Logic_IO_Up()
{
    int8_t tempYLoc = clientInfo.yLoc-1;

    if ((tempYLoc != clientInfo.pyLoc) && (clientInfo.xLoc != clientInfo.pxLoc)) // handle player player conflict. 
    {
        if (tempYLoc < 0)
        {
            tempYLoc = GAME_SIZE-1;
        }
        else if(tempYLoc > GAME_SIZE)
        {
            tempYLoc = 1; 
        }

        if((tempYLoc == clientInfo.fyLoc) && (clientInfo.fxLoc == clientInfo.xLoc)) // handles fruit pickup
        {
            // increment weapons.
            clientInfo.weapons++;

            // spwan the fruit randomly again. 
            clientInfo.fxLoc = rand() % EFF_GAME_SIZE;
            clientInfo.fyLoc = rand() % EFF_GAME_SIZE;
        }
        clientInfo.yLoc = tempYLoc;
    }
}


void Logic_IO_Down()
{
    uint8_t tempYLoc = clientInfo.yLoc + 1;

    if ((tempYLoc != clientInfo.pyLoc) && (clientInfo.xLoc != clientInfo.pxLoc)) // handle player player conflict. 
    {
        tempYLoc = tempYLoc % EFF_GAME_SIZE;

        if((tempYLoc == clientInfo.fyLoc) && (clientInfo.fxLoc == clientInfo.xLoc)) // handles fruit pickup
        {
            // increment weapons.
            clientInfo.weapons++;

            // spwan the fruit randomly again. 
            clientInfo.fxLoc = rand() % EFF_GAME_SIZE;
            clientInfo.fyLoc = rand() % EFF_GAME_SIZE;
        }


        clientInfo.yLoc = tempYLoc;
    }

}

    

void Logic_IO_Right()
{
    uint8_t tempXLoc = clientInfo.xLoc + 1;

    if ((tempXLoc != clientInfo.pxLoc) && (clientInfo.yLoc != clientInfo.pyLoc)) // handle player player conflict. 
    {
        tempXLoc = tempXLoc % EFF_GAME_SIZE;

        if((tempXLoc == clientInfo.fxLoc) && (clientInfo.fyLoc == clientInfo.yLoc)) // handles fruit pickup
        {
            // increment weapons.
            clientInfo.weapons++;

            // spwan the fruit randomly again. 
            clientInfo.fxLoc = rand() % EFF_GAME_SIZE;
            clientInfo.fyLoc = rand() % EFF_GAME_SIZE;
        }
        
        
           clientInfo.xLoc = tempXLoc;
    } 
}

void Logic_IO_Left()
{
    int8_t tempXLoc = clientInfo.xLoc - 1;

    if ((tempXLoc != clientInfo.pxLoc) && (clientInfo.yLoc != clientInfo.pyLoc)) // handle player player conflict. 
    {
        if (tempXLoc < 0)
        {
            tempXLoc = GAME_SIZE-1;
        }
        else if(tempXLoc > GAME_SIZE)
        {
            tempXLoc = 1; 
        }

        if((tempXLoc == clientInfo.fxLoc) && (clientInfo.fyLoc == clientInfo.yLoc)) // handles fruit pickup
        {
            // increment weapons.
            clientInfo.weapons++;

            // spwan the fruit randomly again. 
            clientInfo.fxLoc = rand() % EFF_GAME_SIZE;
            clientInfo.fyLoc = rand() % EFF_GAME_SIZE;
        }


        clientInfo.xLoc = tempXLoc;
    }
}


void Logic_IO_Exit()
{

}


void Calculate_GameState()
{
    switch(clientInfo.input)
    {
        case (IO_LEFT):
            Logic_IO_Left();
            break;

        case (IO_RIGHT):
            Logic_IO_Right();
            break;

        case (IO_UP):
            Logic_IO_Up();
            break;

        case (IO_DOWN):
            Logic_IO_Down();
            break;

        case (IO_EXIT):
            clientInfo.GAME_OVER = true;
            break;
    }

}

