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

#ifndef __PROJECT_H
 #define __PROJECT_H

#include <winsock2.h>
#include <stdio.h>
#include <assert.h>

/*************************************************************************************************/
/*                            GLOBAL DEFINTIONS                                                  */
/*************************************************************************************************/



#define SIO_WINSOCK_VER         (0x202)
#define SIO_ADDRESS_FAMILY      (AF_INET)
#define SIO_SOCKET_TYPE         (SOCK_DGRAM)
#define SIO_SOCKET_PTCOL        (IPPROTO_UDP)
#define SIO_PORT_BINDING        (9999)

#define SIO_MAX_PLAYERS         (2)
#define SIO_PACKET_SIZE         (256)
#define SIO_GAME_SIZE_X         (40)
#define SIO_EFF_GAME_SIZE_X     (SIO_GAME_SIZE_X-2)
#define SIO_GAME_SIZE_Y         (25)

#define SIO_P1_XSTART           (4)
#define SIO_P1_YSTART           (3)
#define SIO_P2_XSTART           (SIO_GAME_SIZE_X - SIO_P1_XSTART)
#define SIO_P2_YSTART           (SIO_GAME_SIZE_Y - SIO_P1_YSTART)
#define SIO_MAX_LDRBOARD        (5)


#define SIO_WOULD_BLOCK_ERR     (10035)
#define UNUSED(x) ((void) x)

/*************************************************************************************************/
/*                            ENUMs TYPEDEFS & STRUCTURES                                        */
/*************************************************************************************************/

typedef enum
{
    CLIENT_DATA = 0,
    CLIENT_REG  = 1,
    CLIENT_EXIT = 2,
    CLIENT_SCRS = 4,
} packetTypes_e;

typedef enum
{
    CLIENT_1 = 0,
    CLIENT_2 = 1,
} clientID_e;

typedef struct
{
    char    avatar;
    uint8_t score; 
} cScores_t; 

typedef struct
{
    cScores_t entry[SIO_MAX_LDRBOARD];
}topScores_t;

extern topScores_t topScores;

typedef struct
{
    union
    {
        struct 
        {
                uint32_t type        : 4; // 0 for registration 1 for input data.
                uint32_t clientID    : 1; // client ID for the two client programs.
                uint32_t resv        : 3;
                uint32_t response    : 8;
                uint32_t length      : 16; 
        } data; 
        uint32_t bits; 
    }; 
}cHeader_t;

typedef struct
{
    union
    {
        struct 
        {
                uint32_t state       : 1; // 0 for dead 1 for alive 
                uint32_t shot        : 1;
                uint32_t sdir        : 2; 
                uint32_t avatar      : 8; // reserved
                uint32_t resv        : 4; // reserved
                uint32_t x_loc       : 8;
                uint32_t y_loc       : 8;

        } data; 
        uint32_t bits; 
    };
}cData_t; 

typedef struct 
{
    cHeader_t header;

    union
    {
        cScores_t   scores[SIO_MAX_LDRBOARD]; // @tdo: get rid of magic numbers.
        cData_t     contents[SIO_MAX_PLAYERS];
        uint8_t     PACKET_BYTES[SIO_PACKET_SIZE];
    };
} clientPacket_t;

/*************************************************************************************************/
/*                            CLASS  DEFINTIONS                                                  */
/*************************************************************************************************/

// note not thread safe.
template<typename T>
class handler_c
{
public:
    static T* Handler_GetInstance()
    {
        if (mHandle == NULL)
        {
            mHandle = new T; 
        }
        assert(mHandle != NULL);
        return mHandle;
    }

    static void ST_DestoryInstance()
    {
        delete mHandle;
    }
protected:
    handler_c();
    ~handler_c();
private:
    handler_c(handler_c const&);
    handler_c& operator=(handler_c const&);
    static T* mHandle;
};

template <class T> T* handler_c<T>::mHandle=NULL;

#endif // __PROJECT_H