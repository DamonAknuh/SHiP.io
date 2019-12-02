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
//library includes
#include <iostream>


// program includes
#include "project_ser.hpp"
#include "slogic.hpp"
#include "ssocket_drv.hpp"
#include "db_drv.hpp"


sLogicDrv_c::~sLogicDrv_c()
{

}

sLogicDrv_c::sLogicDrv_c()
{

}

bool sLogicDrv_c::sLogic_InitSInfo()
{
    int xStartingLoc[2] = {SIO_P1_XSTART, SIO_P2_XSTART};
    int yStartingLoc[2] = {SIO_P1_YSTART, SIO_P2_YSTART};
    serverInfo.GAME_OVER = false; 
    serverInfo.ticks = 0;


    for(uint32_t i = 0; i < SIO_MAX_PLAYERS ; i++)
    {
        serverInfo.clientInfo[i].xLoc  = xStartingLoc[i];
        serverInfo.clientInfo[i].yLoc  = yStartingLoc[i];
        serverInfo.clientInfo[i].state = 0; 
        serverInfo.clientInfo[i].shot  = 0; 
        serverInfo.clientInfo[i].sdir  = 0; 
    }
    return true; 
}

void sLogicDrv_c::sLogic_Unpack()
{
    dataBaseDrv_c * dataBaseDrv = dataBase_Handle::Handler_GetInstance(); 
    sSockDrv_c *     sSockDriver  =  sSockDrv_Handle::Handler_GetInstance();
    clientPacket_t * packetInfo   = (clientPacket_t*) sSockDriver->iPacketBuff;

    clientID_e    iD   = (clientID_e)    packetInfo->header.data.clientID;
    packetTypes_e type = (packetTypes_e) packetInfo->header.data.type;


    std::cout << "|__________________|PACKET|__________________________________" << std::endl;
    std::cout << "| Client ID: " << iD << std::endl;
    std::cout << "| Packet Type: " << type << std::endl; 
    std::cout << "|" << std::endl;

    switch (type)
    {
        case CLIENT_DATA:
            serverInfo.clientInfo[iD].xLoc  = packetInfo->contents[iD].data.x_loc;
            serverInfo.clientInfo[iD].yLoc  = packetInfo->contents[iD].data.y_loc;
            serverInfo.clientInfo[iD].state = packetInfo->contents[iD].data.state;
            serverInfo.clientInfo[iD].shot  = packetInfo->contents[iD].data.shot;
            serverInfo.clientInfo[iD].sdir  = packetInfo->contents[iD].data.sdir;

            std::cout << "| xLoc:   " << (uint32_t) serverInfo.clientInfo[iD].xLoc  << std::endl; 
            std::cout << "| yLoc:   " << (uint32_t) serverInfo.clientInfo[iD].yLoc  << std::endl; 
            std::cout << "| state:  " << (uint32_t) serverInfo.clientInfo[iD].state << std::endl; 
            std::cout << "| shot:   " << (uint32_t) serverInfo.clientInfo[iD].shot  << std::endl; 
            break;

        case CLIENT_EXIT:
            // if recieving end game packet. send exit game packet to client. 
            serverInfo.GAME_OVER = true; 
            serverInfo.clientInfo[iD].state = false;
            serverInfo.clientInfo[iD].shot  = packetInfo->contents[iD].data.shot;
            serverInfo.clientInfo[iD].sdir  = packetInfo->contents[iD].data.sdir;
            dataBaseDrv->dB_UpdateWinner(serverInfo.clientInfo[iD].avatar);
            if ( iD == CLIENT_1)
            {
                sSockDriver->sSock_SendPacket(CLIENT_EXIT, CLIENT_2);
            }
            else if (iD == CLIENT_2)
            {
                sSockDriver->sSock_SendPacket(CLIENT_EXIT, CLIENT_1);
            }
            break;

        case CLIENT_REG:
        case CLIENT_SCRS:
        default:
            std::cout << "\n| WARNING! UNEXPECTED PACKET TYPE.\n|";
            break;
    }

    serverInfo.updateCli = iD;
    
}

void Update_GameState()
{
    sLogicDrv_c * sLogicDrv    = sLogicDrv_Handle::Handler_GetInstance();
    sSockDrv_c *  sSockDriver  = sSockDrv_Handle::Handler_GetInstance();

    if (sSockDriver->sSock_GetPacket())
    {
        sLogicDrv->sLogic_Unpack();
    }

}


void Update_Clients()
{
    sSockDrv_c *  sSockDriver  = sSockDrv_Handle::Handler_GetInstance();

    if (serverInfo.updateCli == CLIENT_1)
    {
        if (!sSockDriver->sSock_SendPacket(CLIENT_DATA, CLIENT_2))
        {
            std::cout<< " | ERROR! Failed to send packet" << std::endl;
        }
    }
    else if (serverInfo.updateCli == CLIENT_2)
    {
        if (!sSockDriver->sSock_SendPacket(CLIENT_DATA, CLIENT_1))
        {
            std::cout<< " | ERROR! Failed to send packet" << std::endl;
        }
    }
}