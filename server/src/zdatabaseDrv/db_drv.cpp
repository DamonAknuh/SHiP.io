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

// Library Includes
#include <iostream>
#include <stdint.h>
#include <sqlite3.h>

// Program Includes. 
#include "project_ser.hpp"
#include "db_drv.hpp"

//https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.html

bool dataBaseDrv_c::dB_InitDB()
{

    std::cout << "| Initializing Scores Database ... ";

    int32_t status;
    // char *zErrMsg = 0;

    status = sqlite3_open("scores.db", &db);
    if (status)
    {
        std::cout << "| ERROR: Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
    }

//     char const * sql = "CREATE TABLE SCORES(AVATAR CHAR    PRIMARY KEY NOT NULL,SCORE          INT    NOT NULL);";

//     status = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
//     if ( status != SQLITE_OK)
//     {
//         std::cout << "| ERROR: Can't create table: " << sqlite3_errmsg(db) << std::endl;
//         return false;
//     }
//     std::cout << " Sucess!" << std::endl;

//     std::cout << "|_____________________________________________________" << std::endl;
    
    return true; 
}


dataBaseDrv_c::dataBaseDrv_c()
{


}

dataBaseDrv_c::~dataBaseDrv_c()
{

    sqlite3_close(db);
}