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
#include "clogic.h"

#include <cstdlib>


cGObjDrv_c::cGObjDrv_c()
{

}

bool cGObjDrv_c::cGObj_InitCInfo()
{
    // randomly spawn fruit on map
    clientInfo.fxLoc = (rand() % SIO_EFF_GAME_SIZE_X) + 1;
    clientInfo.fyLoc = (rand() % SIO_GAME_SIZE_Y);

    // set weapons to 0
    clientInfo.weapons = 0;  
    clientInfo.shotCounter = 0;

    // temporary untill can handle it in sock initialization.
    // todo make logic layer a class driver object.
    if (clientInfo.clientID == 0)
    {
        clientInfo.xLoc = 4;
        clientInfo.yLoc = 3;

        clientInfo.pxLoc = SIO_GAME_SIZE_X - 4;
        clientInfo.pyLoc = SIO_GAME_SIZE_Y - 3;

    }
    else if (clientInfo.clientID == 1)
    {
        clientInfo.xLoc = SIO_GAME_SIZE_X - 4;
        clientInfo.yLoc = SIO_GAME_SIZE_Y - 3;

        clientInfo.pxLoc = 4;
        clientInfo.pyLoc = 3;

    }

    clientInfo.impInput = IO_NULL; // reset shot to zero
    clientInfo.input = IO_NULL;

    clientInfo.GAME_OVER = false; 

    return true; 
}

cGObjDrv_c::~cGObjDrv_c()
{
    // no-op
}


void Calculate_GameState()
{
    cGObjDrv_c * cGObjDrv = cGObjDrv_Handle::Handler_GetInstance();

    switch(clientInfo.input)
    {
        case (IO_LEFT):
            cGObjDrv->cGObj_IO_Left();
            break;

        case (IO_RIGHT):
            cGObjDrv->cGObj_IO_Right();
            break;

        case (IO_UP):
            cGObjDrv->cGObj_IO_Up();
            break;

        case (IO_DOWN):
            cGObjDrv->cGObj_IO_Down();
            break;

        case (IO_SHOOT):
            cGObjDrv->cGObj_IO_Shoot();
            break;

        case (IO_EXIT):
            cGObjDrv->cGObj_IO_Exit();
            break;
    }
}

