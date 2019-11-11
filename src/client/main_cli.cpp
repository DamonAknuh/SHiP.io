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


// Libary Includes
#include <stdio.h>
#include <stdint.h>
#include <winsock2.h>
#include <stdbool.h>


// Customized Includes
#include "../project.h"
#include "project_cli.h"

// GLOBAL VARIABLE.
// TODO: extern in header file. 
bool GAME_OVER = false;
bool WINSOCK   = false; 



clientInfo_t client_info;


bool GC_Reg_Client()
{
    // register client with server and recieve unique client code. 


    return true; 
}

void CG_Setup()
{
    if (WINSOCK)
    {
        WORD winsock_version = 0x202;
        WSADATA winsock_data;

        if( WSAStartup( winsock_version, &winsock_data ) )
        {
            printf( "WSAStartup failed: %d", WSAGetLastError() );
            exit(0);
        }
    }

    // Register Client with server;
    if (!GC_Reg_Client)
    {
        printf("failed to register client with server");

        exit(0);
    }



    // Initialize Game setup variable
    GAME_OVER = false;
}

void CG_teardown()
{


    
}


int main(int argc, char const *argv[])
{

    CG_Setup();

    while(!GAME_OVER)
    {
        CG_Draw();
        CG_GetInput(); 
        CG_SendInput();


    }

    CG_teardown();
    return 0;
}

