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



#ifndef __PROJECT_H
#define __PROJECT_

#include <winsock2.h>



/*************************************************************************************************/
/*                            GLOBAL DEFINTIONS                                                  */
/*************************************************************************************************/

#define SIO_WINSOCK_VER     (0x202)
#define SIO_ADDRESS_FAMILY  (AF_INET)
#define SIO_SOCKET_TYPE     (SOCK_DGRAM)
#define SIO_SOCKET_PTCOL    (IPPROTO_UDP)
#define SIO_PORT_BINDING    (9999)

#define SIO_MAX_PLAYERS     (2)
#define SIO_PACKET_SIZE     (256)


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