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


#ifndef __PROJECT_CLI_H
#define __PROJECT_CLI_H

// library includes
#include <stdint.h>

// program includes. 
#include "project.h"

/*************************************************************************************************/
/*                            GLOBAL DEFINTIONS                                                  */
/***** ********************************************************************************************/


#define GAME_SIZE (50)

/*************************************************************************************************/
/*                            TYPEDEFS & STRUCTURES                                              */
/*************************************************************************************************/

typedef enum
{
    IO_LEFT = 0,
    IO_RIGHT,
    IO_UP,
    IO_DOWN,
    IO_SHOOT,
    IO_EXIT,
    IO_NULL,
}inputs_e;


typedef struct
{
    uint8_t  clientID;
    uint8_t  xLoc;
    uint8_t  yLoc; 
    uint8_t  fxLoc;
    uint8_t  fyLoc;
    uint8_t  weapons;
    uint16_t input; 
    // more to come. 
}clientInfo_t;

extern clientInfo_t clientInfo;

/*************************************************************************************************/
/*                            PACKET INFORMATION                                                 */
/*************************************************************************************************/

typedef struct
{
    union
    {
        struct 
        {
                uint32_t type        : 1; // 0 for registration 1 for input data.
                uint32_t clientID    : 1; // client ID for the two client programs.
                uint32_t state       : 1; // 0 for dead 1 for alive 
                uint32_t resv        : 13;
                uint32_t x_loc       : 8;
                uint32_t y_loc       : 8;
        } data; 
        uint32_t bits; 
    };
}cData_t; 


typedef struct 
{
    union
    {
        cData_t data[SIO_MAX_PLAYERS];
        uint8_t PACKET_DATA[SIO_PACKET_SIZE];
    };
} clientPacket_t;

#endif // __PROJECT_CLI_H