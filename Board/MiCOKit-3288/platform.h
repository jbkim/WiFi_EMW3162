/**
******************************************************************************
* @file    platform.h
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides all MICO Peripherals defined for current platform.
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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
  

   
/******************************************************
 *                   Enumerations
 ******************************************************/




typedef enum
{
    MICO_SYS_LED,
    MICO_RF_LED,
    BOOT_SEL,
    MFG_SEL,
    Standby_SEL,
    EasyLink_BUTTON,
    STDIO_UART_RX,  
    STDIO_UART_TX,  


    MICO_GPIO_1,
    MICO_GPIO_2,   
    MICO_GPIO_3,
    MICO_GPIO_4,
    MICO_GPIO_5,
    MICO_GPIO_6,
    MICO_GPIO_7,
    MICO_GPIO_8,
    MICO_GPIO_9,
    MICO_GPIO_10,
    MICO_GPIO_11,
    MICO_GPIO_12,
    MICO_GPIO_13,
    MICO_GPIO_14,
    MICO_GPIO_15,
    MICO_GPIO_16,
    MICO_GPIO_17,
    MICO_GPIO_18,
    MICO_GPIO_19,
    MICO_GPIO_20,
    MICO_GPIO_21,
    MICO_GPIO_22,
    MICO_GPIO_23,
    MICO_GPIO_24,
    MICO_GPIO_25,
    MICO_GPIO_26,
    MICO_GPIO_27,
    MICO_GPIO_28,
    MICO_GPIO_29,
    MICO_GPIO_30,
    MICO_GPIO_31,
    MICO_GPIO_32,
    MICO_GPIO_33,
    MICO_GPIO_34,
    MICO_GPIO_35,
    MICO_GPIO_36,
    MICO_GPIO_37,
    MICO_GPIO_38,
    MICO_GPIO_39,
    MICO_GPIO_40,

    MICO_GPIO_MAX, /* Denotes the total number of GPIO port aliases. Not a valid GPIO alias */
    MICO_GPIO_NONE,
} mico_gpio_t;

typedef enum
{
    MICO_SPI_1,
    MICO_SPI_MAX, /* Denotes the total number of SPI port aliases. Not a valid SPI alias */
    MICO_SPI_NONE,
} mico_spi_t;

typedef enum
{
    MICO_I2C_1,
    MICO_I2C_MAX, /* Denotes the total number of I2C port aliases. Not a valid I2C alias */
    MICO_I2C_NONE,
} mico_i2c_t;

typedef enum
{
    MICO_PWM_R,
    MICO_PWM_G,
    MICO_PWM_B,
    MICO_PWM_MAX, /* Denotes the total number of PWM port aliases. Not a valid PWM alias */
    MICO_PWM_NONE,
} mico_pwm_t;

typedef enum
{
    MICO_ADC_1,
    MICO_ADC_2,
    MICO_ADC_3,
    MICO_ADC_MAX, /* Denotes the total number of ADC port aliases. Not a valid ADC alias */
    MICO_ADC_NONE,
} mico_adc_t;

typedef enum
{
    MICO_UART_1,
    MICO_UART_2,
    MICO_UART_MAX, /* Denotes the total number of UART port aliases. Not a valid UART alias */
    MICO_UART_NONE,
} mico_uart_t;

typedef enum
{
  MICO_SPI_FLASH,
  MICO_INTERNAL_FLASH,
  MICO_FLASH_MAX,
} mico_flash_t;

#define USE_MICO_SPI_FLASH
//#define SFLASH_SUPPORT_MACRONIX_PARTS
//#define SFLASH_SUPPORT_SST_PARTS
#define SFLASH_SUPPORT_WINBOND_PARTS


#ifdef BOOTLOADER
#define STDIO_UART       MICO_UART_1
#define STDIO_UART_BAUDRATE (921600)   
#else
#define STDIO_UART       MICO_UART_1
#define STDIO_UART_BAUDRATE (115200)   
#endif
   
#define UART_FOR_APP     MICO_UART_2
#define MFG_TEST         MICO_UART_1
#define CLI_UART         MICO_UART_1

/* Components connected to external I/Os*/


/* I/O connection <-> Peripheral Connections */
#define MICO_I2C_CP         (MICO_I2C_1)



#ifdef __cplusplus
} /*extern "C" */
#endif

