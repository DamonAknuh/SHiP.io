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
#include <stdlib.h>  // atoi

// Program Includes. 
#include "project_ser.hpp"
#include "db_drv.hpp"

topScores_t topScores; 
volatile uint32_t m_CurScores;
uint32_t counter= 0; ; 

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "| %s: ", (const char*)data);
    for(i = 0; i<argc; i++) {
        m_CurScores = atoi(argv[i]);
        printf(" %s = %d", azColName[i], m_CurScores);
    }
    printf("\n");
    return 0;
}

static int callbackTop(void *data, int argc, char **argv, char **azColName)
{
    fprintf(stderr, "| %s ", (const char*)data);

    topScores.entry[counter].avatar =  argv[0][0];
    topScores.entry[counter].score  =  atoi(argv[1]);

    std::cout << (counter+1) << "). Avatar: " <<  topScores.entry[counter].avatar << " with " << (uint32_t)topScores.entry[counter].score << " wins" <<  std::endl;
    
    counter++;
    return 0;
}


void dataBaseDrv_c::dB_UpdateWinner(char avatar)
{

    std::cout << "|__________________|UPDATING SCORES|___________________________________" << std::endl;

    if (dB_Select(avatar) == false)
    {
        
    }

    m_CurScores = m_CurScores + 1; 
    if (dB_Update(avatar, m_CurScores) == false)
    {
        
    }

    std::cout << "|______________________________________________________________________" << std::endl;
}

bool dataBaseDrv_c::dB_SelectTop()
{

    counter = 0;
    const char* data = "   --> SQL TOP 5 QUERY RESULT: ";
    char const * sqlSelectTop = "SELECT * FROM SCORES ORDER BY SCORE DESC LIMIT 5";
    int32_t status = 0; 
    char *zErrMsg = 0;


    std::cout << "|______________|SELECTING TOP SCORES|__________________________________" << std::endl;
    std::cout << "|\n| Selecting Top 5 Scores ... " << std::endl;
    std::cout << "| SQL Select Command: " << sqlSelectTop << std::endl;

    status = sqlite3_exec(db, sqlSelectTop, callbackTop, (void*)data , &zErrMsg);
    if ( status != SQLITE_OK)
    {
        std::cout << "|    WARNING: failed to select top 5 scores: " << sqlite3_errmsg(db) << std::endl;
        return false; 
    }
    std::cout << "| Success!" << std::endl;
    std::cout << "|______________________________________________________________________" << std::endl;


    return true; 
}


bool dataBaseDrv_c::dB_Select(char avatar)
{
    std::cout << "| Selecting Scores ... " << std::endl;
    const char* data = "SQL QUERY RESULT: ";
    int32_t status = 0; 
    char *zErrMsg = 0;
    char sqlSelect[60] = {};

    sprintf(sqlSelect,"SELECT SCORE FROM SCORES WHERE AVATAR='%c'", avatar);
    std::cout << "| SQL Select Command: " << sqlSelect << std::endl;

    status = sqlite3_exec(db, sqlSelect, callback, (void*)data , &zErrMsg);
    if ( status != SQLITE_OK)
    {
        std::cout << "|    WARNING: failed to select scores: " << sqlite3_errmsg(db) << std::endl;
        return false; 
    }

    std::cout << "|    Success!" << std::endl;
    return true; 
}

bool dataBaseDrv_c::dB_Update(char avatar, uint32_t score)
{
    int32_t status = 0; 
    char *zErrMsg = 0;
    char sqlUpdate[60] = {};

    sprintf(sqlUpdate,"UPDATE SCORES SET SCORE=%d WHERE AVATAR='%c'", score, avatar);
    std::cout <<  "| SQL Update Command: " << sqlUpdate << std::endl;

    status = sqlite3_exec(db, sqlUpdate, NULL, 0 , &zErrMsg);
    if ( status != SQLITE_OK)
    {
        std::cout << "|    WARNING: failed to update scores: " << sqlite3_errmsg(db) << std::endl;
        return false; 
        //@todo 
    }

    
    std::cout << "|    Success!" << std::endl;


    dB_SelectTop();

    return true; 
}

bool dataBaseDrv_c::dB_Insert(char avatar, int32_t score)
{
    const char* data = "Callback function called";
    char  sqlInsert[60] = {};
    int32_t status = 0; 
    char *zErrMsg = 0;

    sprintf(sqlInsert, "INSERT INTO SCORES(AVATAR, SCORE) VALUES ('%c', %d)",  avatar, score);

    std::cout << "| SQL Insert Command: " << sqlInsert << std::endl;

    std::cout << "| Updating Scores ... ";

    status = sqlite3_exec(db, sqlInsert, callback, (void*)data , &zErrMsg);
    if ( status != SQLITE_OK)
    {
        std::cout << "|    WARNING: failed to update scores: " << sqlite3_errmsg(db) << std::endl;
        return false; 
    }
    std::cout << "|    Success!" << std::endl;
    return true; 
}
//https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.html

bool dataBaseDrv_c::dB_InitDB()
{

    std::cout << "| Initializing Scores Database ... " << std::endl; 

    int32_t status;


    status = sqlite3_open("scores.db", &db);
    if (status)
    {
        std::cout << "|    ERROR: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // char const * sql = "CREATE TABLE SCORES(AVATAR CHAR    PRIMARY KEY NOT NULL,SCORE          INT    NOT NULL);";

    // char *zErrMsg = 0;
    // status = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    // if ( status != SQLITE_OK)
    // {
    //     std::cout << "|    ERROR: Can't create table: " << sqlite3_errmsg(db) << std::endl;
    //     return false;
    // }
    // std::cout << "     Success!" << std::endl;

    // for ( uint32_t i = '!'; i <= '~'; i++)
    // {
    //     dB_Insert((char)i, 0);

    // }




    std::cout << "|______________________________________________________________________" << std::endl;
    
    return true; 
}


dataBaseDrv_c::dataBaseDrv_c()
{


}

dataBaseDrv_c::~dataBaseDrv_c()
{

    sqlite3_close(db);
}