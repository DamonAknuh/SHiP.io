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


#ifndef __CLOGIC_H
#define __CLOGIC_H

#include <stdint.h>
#include "project_cli.h"

void Calculate_GameState(); 

/**
 * PLACE HOLDER FOR CLASS INFORMATION
 * 
 * @TODO: aknuh add class infromation
 */
class cGObjDrv_c
{
private:
    /* Data */
    
public:

    // I/O Functions
    void cGObj_IO_Up();
    void cGObj_IO_Down();
    void cGObj_IO_Left();
    void cGObj_IO_Right();
    void cGObj_IO_Shoot();
    void cGObj_IO_Exit();

    // Initialization
    cGObjDrv_c();
    bool cGObj_InitCInfo();

    ~cGObjDrv_c();
};

typedef handler_c<cGObjDrv_c> cGObjDrv_Handle;

#endif // __CLOGIC_H