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
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER D`EALINGS IN THE           
    SOFTWARE.                                                                               
**************************************************************************************************/

#ifndef __DB_DRV_HPP
 #define __DB_DRV_HPP


// Library Includes
#include <stdint.h>

 // Program Includes. 
#include <sqlite3.h>
#include "project_ser.hpp"


class dataBaseDrv_c
{

private:
    bool    dB_Select(char avatar);
    bool    dB_Update(char avatar, uint32_t score);
    bool    dB_Insert(char avatar, int32_t score);

private:
    sqlite3 *db;
    /* data */
public:

    bool    dB_SelectTop();
    void    dB_UpdateWinner(char avatar);
    bool    dB_InitDB();
    dataBaseDrv_c();
    ~dataBaseDrv_c();
};


typedef handler_c<dataBaseDrv_c> dataBase_Handle;

 #endif // ifndef_DB_DRV_HPP