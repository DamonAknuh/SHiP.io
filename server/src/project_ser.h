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


#ifndef __PROJECT_SER_H
#define __PROJECT_SER_H
#include "../../include/project.h"


/*************************************************************************************************/
/*                            GLOBAL DEFINTIONS                                                  */
/***** ********************************************************************************************/

/*************************************************************************************************/
/*                            ENUMs TYPEDEFS & STRUCTURES                                        */
/*************************************************************************************************/

typedef struct
{
    uint8_t  GAME_OVER;
    uint8_t  clientID;
    

    uint8_t  xLoc;
    uint8_t  yLoc;
    uint8_t  weapons; 
    uint16_t input;
    uint16_t impInput;
    uint8_t  shotCounter;

    uint8_t  pxLoc;
    uint8_t  pyLoc;

    uint8_t  fxLoc;
    uint8_t  fyLoc;
    // more to come. 
}ServerInfo_t;

extern ServerInfo_t serverInfo;


/*************************************************************************************************/
/*                            PACKET INFORMATION                                                 */
/*************************************************************************************************/



#endif // __PROJECT_SER_H