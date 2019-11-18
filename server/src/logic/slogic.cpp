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

#include "project_ser.h"
#include "slogic.h"
#include "ssocket_drv.hpp"

sLogicDrv_c::~sLogicDrv_c()
{

}

sLogicDrv_c::sLogicDrv_c()
{

}

bool sLogicDrv_c::sLogic_InitSInfo()
{
    serverInfo.GAME_OVER = false; 
    serverInfo.ticks = 0;

    for(uint32_t i = 0; i < SIO_MAX_PLAYERS ; i++)
    {
        serverInfo.clientInfo[i].xLoc  = (i*25) + 3;
        serverInfo.clientInfo[i].yLoc  = (i*25) + 3;
        serverInfo.clientInfo[i].state = 1; 
    }
    return true; 
}


void Update_GameState()
{
    sSockDrv_c * sSockDriver    = sSockDrv_Handle::Handler_GetInstance();
    clientPacket_t * packetInfo = NULL;
    clientID_e iD;
    packetTypes_e type; 

    if (!sSockDriver->sSock_GetPacket(packetInfo))
    {
        iD = packetInfo->contents[0].data.clientID;
        type = packetInfo->contents[0].data.type;

        switch (type)
        {
            case CLIENT_DATA:
                serverInfo.clientInfo[iD].xLoc = packetInfo->contents[0].data.x_loc;
                serverInfo.clientInfo[iD].yLoc = packetInfo->contents[0].data.y_loc;
                serverInfo.clientInfo[iD].state = packetInfo->contents[0].data.state;
                break;

            case CLIENT_EXIT:
                serverInfo.clientInfo[iD].state = false;
                break;

            case CLEINT_REG:
            case CLIENT_ACK:
            default:
                std::cout<< "\n| WARNING! UNEXPECTED PACKET TYPE.\n|";
                break;
        }
    }
}