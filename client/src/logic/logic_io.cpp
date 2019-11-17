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
#include "logic.h"
#include "display.h"

#include <cstdlib>

void cGObjDrv_c::cGObj_IO_Up()
{
    int8_t tempYLoc = clientInfo.yLoc-1;

    if ((tempYLoc != clientInfo.pyLoc) || (clientInfo.xLoc != clientInfo.pxLoc)) // handle player player conflict. 
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

        // Only want to save last input when not currently shooting lasers. 
        if (!clientInfo.shotCounter)
        {
            clientInfo.impInput = IO_UP;
        }
    }
}


void cGObjDrv_c::cGObj_IO_Down()
{
    uint8_t tempYLoc = clientInfo.yLoc + 1;

    if ((tempYLoc != clientInfo.pyLoc) || (clientInfo.xLoc != clientInfo.pxLoc)) // handle player player conflict. 
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

        // Only want to save last input when not currently shooting lasers. 
        if (!clientInfo.shotCounter)
        {
            clientInfo.impInput = IO_DOWN;
        }
    }

}

    

void cGObjDrv_c::cGObj_IO_Right()
{
    uint8_t tempXLoc = clientInfo.xLoc + 1;

    if ((tempXLoc != clientInfo.pxLoc) || (clientInfo.yLoc != clientInfo.pyLoc)) // handle player player conflict. 
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

        // Only want to save last input when not currently shooting lasers. 
        if (!clientInfo.shotCounter)
        {
            clientInfo.impInput = IO_RIGHT;
        }
    } 
}

void cGObjDrv_c::cGObj_IO_Left()
{
    int8_t tempXLoc = clientInfo.xLoc - 1;

    if ((tempXLoc != clientInfo.pxLoc) || (clientInfo.yLoc != clientInfo.pyLoc)) // handle player player conflict. 
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

        // Only want to save last input when not currently shooting lasers. 
        if (!clientInfo.shotCounter)
        {
            clientInfo.impInput = IO_LEFT;
        }
        
    }
}


void cGObjDrv_c::cGObj_IO_Exit()
{
    clientInfo.GAME_OVER = true;
}

void cGObjDrv_c::cGObj_IO_Shoot()
{
    dConsoleDrv_c * dConsoleDrv = dConsoleDrv_Handle::Handler_GetInstance();

    if (clientInfo.weapons && !clientInfo.shotCounter){ // check that player has a weapon to use and not currently cooling down. 
        switch (clientInfo.impInput)
        {
            case (IO_LEFT):
                // if players are on same plane, and valid shot left. 
                if ((clientInfo.yLoc == clientInfo.pyLoc) && (clientInfo.xLoc > clientInfo.pxLoc))
                {
                    dConsoleDrv->Set_PlayerTwoAvatar('X');
                    clientInfo.GAME_OVER = true; 
                }
                break;

            case (IO_RIGHT):
                if ((clientInfo.yLoc == clientInfo.pyLoc) && (clientInfo.xLoc < clientInfo.pxLoc))
                {
                    dConsoleDrv->Set_PlayerTwoAvatar('X');
                    clientInfo.GAME_OVER = true; 
                }
                break;

            case (IO_UP):
                if ((clientInfo.xLoc == clientInfo.pxLoc) && (clientInfo.yLoc > clientInfo.pyLoc))
                {
                    dConsoleDrv->Set_PlayerTwoAvatar('X');
                    clientInfo.GAME_OVER = true; 
                }
                break;

            case (IO_DOWN):
                if ((clientInfo.xLoc == clientInfo.pxLoc) && (clientInfo.yLoc < clientInfo.pyLoc))
                {
                    dConsoleDrv->Set_PlayerTwoAvatar('X');
                    clientInfo.GAME_OVER = true; 
                }
                break;

            case (IO_NULL): // initial condition for shooting. nothing happens. 
            default:
                break;
        }
        clientInfo.shotCounter = 1; 
        clientInfo.weapons--;
    }
   
}