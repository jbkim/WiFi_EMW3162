/**
******************************************************************************
* @file    stdio_IAR.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2014 MXCHIP Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights 
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is furnished
*  to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************
*/ 
#include <stdlib.h>
#include <yfuns.h>
#include "platform.h"
#include "platform_config.h"
#include "MicoPlatform.h"


#ifdef BOOTLOADER
int putchar(int ch)
{
  MicoUartSend( STDIO_UART, &ch, 1 );
  return ch;
}
#else
size_t __write( int handle, const unsigned char * buffer, size_t size )
{
  UNUSED_PARAMETER(handle);
  
  if ( buffer == 0 )
  {
    return 0;
  }
  
  MicoUartSend( STDIO_UART, (const char*)buffer, size );
  
  return size;
}
#endif
