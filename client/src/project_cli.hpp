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


#ifndef __PROJECT_CLI_H
#define __PROJECT_CLI_H

// library includes
#include <stdint.h>

// program includes. 
#include "../../include/project.hpp"

/*************************************************************************************************/
/*                            GLOBAL DEFINTIONS                                                  */
/***** ********************************************************************************************/


#define UP_SHOT             (0)
#define DOWN_SHOT           (1)
#define LEFT_SHOT           (2)
#define RIGHT_SHOT          (3)

#define DEFAULT_P1          ('O')
#define DEFAULT_P2          ('E')

#define SHOT_MAX_FRAMES      (2)

/*************************************************************************************************/
/*                           ENUMs TYPEDEFS & STRUCTURES                                         */
/*************************************************************************************************/
typedef struct 
{
    uint8_t  xLoc;
    uint8_t  yLoc;
    uint8_t  state;
    uint8_t  shot;
    uint8_t  sdir;
    uint8_t  avatar;
}pInfo_t;

typedef enum
{
    IO_LEFT  = 0,
    IO_RIGHT = 1,
    IO_UP    = 2,
    IO_DOWN  = 3, 
    IO_SHOOT,
    IO_EXIT,
    IO_NULL,
}inputs_e;

typedef struct
{
    uint8_t     GAME_OVER;
    
    pInfo_t     pInfo[SIO_MAX_PLAYERS];

    uint8_t     weapons; 
    uint16_t    input;
    uint16_t    impInput;
    uint8_t     shotCounter;
    uint8_t     pShotCounter;
    uint8_t     update;

    uint8_t     fxLoc;
    uint8_t     fyLoc;

    // more to come. 
}clientInfo_t;

extern clientID_e g_ClientID;
extern clientID_e g_pClientID;


extern clientInfo_t clientInfo;

/*************************************************************************************************/
/*                            PACKET INFORMATION                                                 */
/*************************************************************************************************/


#endif // __PROJECT_CLI_H