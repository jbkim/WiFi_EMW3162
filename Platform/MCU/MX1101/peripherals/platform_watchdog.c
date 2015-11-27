/**
******************************************************************************
* @file    MicoDriverWdg.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide WDG driver functions.
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


#include "MICOPlatform.h"
#include "MICORTOS.h"
#include "common.h"
#include "Debug.h"
#include "watchdog.h"

#include "platform.h"
#include "platform_config.h"

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Variables Definitions
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

OSStatus platform_watchdog_init( uint32_t timeout_ms )
{
// PLATFORM_TO_DO
#ifdef MICO_DISABLE_WATCHDOG
  return kUnsupportedErr;
#else
  OSStatus err = kNoErr;
  require_action( timeout_ms < 4000 && timeout_ms > 0, exit, err = kParamErr );

  if ( timeout_ms > 3000 )
  	WdgEn(WDG_STEP_4S);
  else if ( timeout_ms > 1000 )
  	WdgEn(WDG_STEP_3S);
  else
  	WdgEn(WDG_STEP_1S);

exit:
	return err;
#endif
}

OSStatus platform_watchdog_deinit( void )
{
    // PLATFORM_TO_DO
    WdgDis();
    return kNoErr;
}

bool platform_watchdog_check_last_reset( void )
{
    return false;
}

OSStatus platform_watchdog_kick( void )
{
#ifndef MICO_DISABLE_WATCHDOG
	WdgFeed();
	return kNoErr;
#else
	return kNoErr;
#endif
}


