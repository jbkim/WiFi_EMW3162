/**
******************************************************************************
* @file    platform.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides all MICO Peripherals mapping table and platform
*          specific funcgtions.
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
#include "platform.h"
#include "platform_config.h"
#include "platform_peripheral.h"
#include "platform_config.h"
#include "PlatformLogging.h"
#include "spi_flash_platform_interface.h"
#include "wlan_platform_common.h"



/******************************************************
*                      Macros
******************************************************/

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
*               Function Declarations
******************************************************/
extern WEAK void PlatformEasyLinkButtonClickedCallback(void);
extern WEAK void PlatformEasyLinkButtonLongPressedCallback(void);
extern WEAK void bootloader_start(void);

/******************************************************
*               Variables Definitions
******************************************************/

/* This table maps STM32 pins to GPIO definitions on the schematic
* A full pin definition is provided in <WICED-SDK>/include/platforms/BCM943362WCD4/platform.h
*/

static uint32_t _default_start_time = 0;
static mico_timer_t _button_EL_timer;

const platform_gpio_t platform_gpio_pins[] =
{
  /* Common GPIOs for internal use */
  [MICO_SYS_LED]                      = { GPIOB,  10 }, 
  [MICO_RF_LED]                       = { GPIOA,  4 }, 
  [BOOT_SEL]                          = { GPIOB,  1 }, 
  [MFG_SEL]                           = { GPIOB,  0 }, 
  [EasyLink_BUTTON]                   = { GPIOA,  1 }, 
  [STDIO_UART_RX]                     = { GPIOA,  3 },  
  [STDIO_UART_TX]                     = { GPIOA,  2 },  

  /* GPIOs for external use */
  [MICO_GPIO_2]                       = { GPIOB,  2 },
  [MICO_GPIO_8]                       = { GPIOA , 2 },
  [MICO_GPIO_9]                       = { GPIOA,  1 },
  [MICO_GPIO_12]                      = { GPIOA,  3 },
  [MICO_GPIO_16]                      = { GPIOC, 13 },
  [MICO_GPIO_17]                      = { GPIOB, 10 },
  [MICO_GPIO_18]                      = { GPIOB,  9 },
  [MICO_GPIO_19]                      = { GPIOB, 12 },
  [MICO_GPIO_27]                      = { GPIOA, 12 },  
  [MICO_GPIO_29]                      = { GPIOA, 10 },
  [MICO_GPIO_30]                      = { GPIOB,  6 },
  [MICO_GPIO_31]                      = { GPIOB,  8 },
  [MICO_GPIO_33]                      = { GPIOB, 13 },
  [MICO_GPIO_34]                      = { GPIOA,  5 },
  [MICO_GPIO_35]                      = { GPIOA, 10 },
  [MICO_GPIO_36]                      = { GPIOB,  1 },
  [MICO_GPIO_37]                      = { GPIOB,  0 },
  [MICO_GPIO_38]                      = { GPIOA,  4 },
};

const platform_i2c_t *platform_i2c_peripherals = NULL;

const platform_uart_t platform_uart_peripherals[] =
{
  [MICO_UART_1] =
  {
    .port                         = USART2,
    .pin_tx                       = &platform_gpio_pins[STDIO_UART_TX],
    .pin_rx                       = &platform_gpio_pins[STDIO_UART_RX],
    .pin_cts                      = NULL,
    .pin_rts                      = NULL,
    .tx_dma_config =
    {
      .controller                 = DMA1,
      .stream                     = DMA1_Stream6,
      .channel                    = DMA_Channel_4,
      .irq_vector                 = DMA1_Stream6_IRQn,
      .complete_flags             = DMA_HISR_TCIF6,
      .error_flags                = ( DMA_HISR_TEIF6 | DMA_HISR_FEIF6 ),
    },
    .rx_dma_config =
    {
      .controller                 = DMA1,
      .stream                     = DMA1_Stream5,
      .channel                    = DMA_Channel_4,
      .irq_vector                 = DMA1_Stream5_IRQn,
      .complete_flags             = DMA_HISR_TCIF5,
      .error_flags                = ( DMA_HISR_TEIF5 | DMA_HISR_FEIF5 | DMA_HISR_DMEIF5 ),
    },
  },
  [MICO_UART_2] =
  {
    .port                         = USART1,
    .pin_tx                       = &platform_gpio_pins[MICO_GPIO_30],
    .pin_rx                       = &platform_gpio_pins[MICO_GPIO_29],
    .pin_cts                      = NULL,
    .pin_rts                      = NULL,
    .tx_dma_config =
    {
      .controller                 = DMA2,
      .stream                     = DMA2_Stream7,
      .channel                    = DMA_Channel_4,
      .irq_vector                 = DMA2_Stream7_IRQn,
      .complete_flags             = DMA_HISR_TCIF7,
      .error_flags                = ( DMA_HISR_TEIF7 | DMA_HISR_FEIF7 ),
    },
    .rx_dma_config =
    {
      .controller                 = DMA2,
      .stream                     = DMA2_Stream2,
      .channel                    = DMA_Channel_4,
      .irq_vector                 = DMA2_Stream2_IRQn,
      .complete_flags             = DMA_LISR_TCIF2,
      .error_flags                = ( DMA_LISR_TEIF2 | DMA_LISR_FEIF2 | DMA_LISR_DMEIF2 ),
    },
  },
};

platform_uart_driver_t platform_uart_drivers[MICO_UART_MAX];

const platform_flash_t platform_flash_peripherals[] =
{
  [MICO_SPI_FLASH] =
  {
    .flash_type                   = FLASH_TYPE_SPI,
    .flash_start_addr             = 0x000000,
    .flash_length                 = 0x200000,
  },
  [MICO_INTERNAL_FLASH] =
  {
    .flash_type                   = FLASH_TYPE_INTERNAL,
    .flash_start_addr             = 0x08000000,
    .flash_length                 = 0x80000,
  },
};

platform_flash_driver_t platform_flash_drivers[MICO_FLASH_MAX];

#if defined ( USE_MICO_SPI_FLASH )

/* spi flash bus pins. Used by platform/drivers/spi_flash/spi_flash_platform.c */
const platform_gpio_t spi_flash_spi_pins[] =
{
  [FLASH_PIN_SPI_CS  ]          = { GPIOA, 15 },
  [FLASH_PIN_SPI_CLK ]          = { GPIOB,  3 },
  [FLASH_PIN_SPI_MOSI]          = { GPIOA,  7 },
  [FLASH_PIN_SPI_MISO]          = { GPIOB,  4 },
};

const platform_spi_t spi_flash_spi =
{
  .port                         = SPI1,
  .gpio_af                      = GPIO_AF_SPI1,
  .peripheral_clock_reg         = RCC_APB2Periph_SPI1,
  .peripheral_clock_func        = RCC_APB2PeriphClockCmd,
  .pin_mosi                     = &spi_flash_spi_pins[FLASH_PIN_SPI_MOSI],
  .pin_miso                     = &spi_flash_spi_pins[FLASH_PIN_SPI_MISO],
  .pin_clock                    = &spi_flash_spi_pins[FLASH_PIN_SPI_CLK],
  .tx_dma =
  {
    .controller                 = DMA2,
    .stream                     = DMA2_Stream5,
    .channel                    = DMA_Channel_3,
    .irq_vector                 = DMA2_Stream5_IRQn,
    .complete_flags             = DMA_HISR_TCIF5,
    .error_flags                = ( DMA_HISR_TEIF5 | DMA_HISR_FEIF5 ),
  },
  .rx_dma =
  {
    .controller                 = DMA2,
    .stream                     = DMA2_Stream0,
    .channel                    = DMA_Channel_3,
    .irq_vector                 = DMA2_Stream0_IRQn,
    .complete_flags             = DMA_LISR_TCIF0,
    .error_flags                = ( DMA_LISR_TEIF0 | DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 ),
  },
};

const spi_flash_device_t spi_flash_device =
{
    .speed       = 40000000,
    .mode        = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_HIGH | SPI_USE_DMA | SPI_MSB_FIRST),
    .bits        = 8
};
#endif

/* Wi-Fi control pins. Used by platform/MCU/wlan_platform_common.c
* SDIO: EMW1062_PIN_BOOTSTRAP[1:0] = b'00
* gSPI: EMW1062_PIN_BOOTSTRAP[1:0] = b'01
*/
const platform_gpio_t wifi_control_pins[] =
{
  [WIFI_PIN_RESET]           = { GPIOB, 14 },
};

/* Wi-Fi SDIO bus pins. Used by platform/MCU/STM32F2xx/EMW1062_driver/wlan_SDIO.c */
const platform_gpio_t wifi_sdio_pins[] =
{
  [WIFI_PIN_SDIO_OOB_IRQ] = { GPIOA,  0 },
  [WIFI_PIN_SDIO_CLK    ] = { GPIOB, 15 },
  [WIFI_PIN_SDIO_CMD    ] = { GPIOA,  6 },
  [WIFI_PIN_SDIO_D0     ] = { GPIOB,  7 },
  [WIFI_PIN_SDIO_D1     ] = { GPIOA,  8 },
  [WIFI_PIN_SDIO_D2     ] = { GPIOA,  9 },
  [WIFI_PIN_SDIO_D3     ] = { GPIOB,  5 },
};


/******************************************************
*           Interrupt Handler Definitions
******************************************************/

MICO_RTOS_DEFINE_ISR( USART1_IRQHandler )
{
  platform_uart_irq( &platform_uart_drivers[MICO_UART_2] );
}

MICO_RTOS_DEFINE_ISR( USART2_IRQHandler )
{
  platform_uart_irq( &platform_uart_drivers[MICO_UART_1] );
}

MICO_RTOS_DEFINE_ISR( DMA1_Stream6_IRQHandler )
{
  platform_uart_tx_dma_irq( &platform_uart_drivers[MICO_UART_1] );
}

MICO_RTOS_DEFINE_ISR( DMA2_Stream7_IRQHandler )
{
  platform_uart_tx_dma_irq( &platform_uart_drivers[MICO_UART_2] );
}

MICO_RTOS_DEFINE_ISR( DMA1_Stream5_IRQHandler )
{
  platform_uart_rx_dma_irq( &platform_uart_drivers[MICO_UART_1] );
}

MICO_RTOS_DEFINE_ISR( DMA2_Stream2_IRQHandler )
{
  platform_uart_rx_dma_irq( &platform_uart_drivers[MICO_UART_2] );
}


/******************************************************
*               Function Definitions
******************************************************/

void platform_init_peripheral_irq_priorities( void )
{
  /* Interrupt priority setup. Called by WICED/platform/MCU/STM32F2xx/platform_init.c */
  NVIC_SetPriority( RTC_WKUP_IRQn    ,  1 ); /* RTC Wake-up event   */
  NVIC_SetPriority( SDIO_IRQn        ,  2 ); /* WLAN SDIO           */
  NVIC_SetPriority( DMA2_Stream3_IRQn,  3 ); /* WLAN SDIO DMA       */
  //NVIC_SetPriority( DMA1_Stream3_IRQn,  3 ); /* WLAN SPI DMA        */
  NVIC_SetPriority( USART1_IRQn      ,  6 ); /* MICO_UART_1         */
  NVIC_SetPriority( USART2_IRQn      ,  6 ); /* MICO_UART_2         */
  NVIC_SetPriority( DMA1_Stream6_IRQn,  7 ); /* MICO_UART_1 TX DMA  */
  NVIC_SetPriority( DMA1_Stream5_IRQn,  7 ); /* MICO_UART_1 RX DMA  */
  NVIC_SetPriority( DMA2_Stream7_IRQn,  7 ); /* MICO_UART_2 TX DMA  */
  NVIC_SetPriority( DMA2_Stream2_IRQn,  7 ); /* MICO_UART_2 RX DMA  */
  NVIC_SetPriority( EXTI0_IRQn       , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI1_IRQn       , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI2_IRQn       , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI3_IRQn       , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI4_IRQn       , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI9_5_IRQn     , 14 ); /* GPIO                */
  NVIC_SetPriority( EXTI15_10_IRQn   , 14 ); /* GPIO                */
}

static void _button_EL_irq_handler( void* arg )
{
  (void)(arg);
  int interval = -1;
  
  if ( MicoGpioInputGet( (mico_gpio_t)EasyLink_BUTTON ) == 0 ) {
    _default_start_time = mico_get_time()+1;
    mico_start_timer(&_button_EL_timer);
  } else {
    interval = mico_get_time() + 1 - _default_start_time;
    if ( (_default_start_time != 0) && interval > 50 && interval < RestoreDefault_TimeOut){
      /* EasyLink button clicked once */
      PlatformEasyLinkButtonClickedCallback();
    }
    mico_stop_timer(&_button_EL_timer);
    _default_start_time = 0;
  }
}

static void _button_EL_Timeout_handler( void* arg )
{
  (void)(arg);
  _default_start_time = 0;
  PlatformEasyLinkButtonLongPressedCallback();
}

void init_platform( void )
{
  MicoGpioInitialize( (mico_gpio_t)MICO_SYS_LED, OUTPUT_PUSH_PULL );
  MicoGpioOutputLow( (mico_gpio_t)MICO_SYS_LED );
  MicoGpioInitialize( (mico_gpio_t)MICO_RF_LED, OUTPUT_OPEN_DRAIN_NO_PULL );
  MicoGpioOutputHigh( (mico_gpio_t)MICO_RF_LED );
  
  MicoGpioInitialize((mico_gpio_t)BOOT_SEL, INPUT_PULL_UP);
  MicoGpioInitialize((mico_gpio_t)MFG_SEL, INPUT_PULL_UP);
  
  //  Initialise EasyLink buttons
  MicoGpioInitialize( (mico_gpio_t)EasyLink_BUTTON, INPUT_PULL_UP );
  mico_init_timer(&_button_EL_timer, RestoreDefault_TimeOut, _button_EL_Timeout_handler, NULL);
  MicoGpioEnableIRQ( (mico_gpio_t)EasyLink_BUTTON, IRQ_TRIGGER_BOTH_EDGES, _button_EL_irq_handler, NULL );

  MicoFlashInitialize( MICO_SPI_FLASH );
}

#ifdef BOOTLOADER
const unsigned char CRC8Table[]={
  0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
  157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
  35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
  190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
  70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
  219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
  101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
  248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
  140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
  17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
  175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
  50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
  202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
  87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
  233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
  116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};
#define SizePerRW                   (4096)
static uint8_t data[SizePerRW];

uint8_t CRC8_Table(uint8_t crc8_ori, uint8_t *p, uint32_t counter)
{
  uint8_t crc8 = crc8_ori;
  for( ; counter > 0; counter--){
    crc8 = CRC8Table[crc8^*p];
    p++;
  }
  return(crc8);
}

void init_platform_bootloader( void )
{
  OSStatus err = kNoErr;
  
  MicoGpioInitialize( (mico_gpio_t)MICO_SYS_LED, OUTPUT_PUSH_PULL );
  MicoGpioOutputLow( (mico_gpio_t)MICO_SYS_LED );
  MicoGpioInitialize( (mico_gpio_t)MICO_RF_LED, OUTPUT_OPEN_DRAIN_NO_PULL );
  MicoGpioOutputHigh( (mico_gpio_t)MICO_RF_LED );
  
  MicoGpioInitialize((mico_gpio_t)BOOT_SEL, INPUT_PULL_UP);
  MicoGpioInitialize((mico_gpio_t)MFG_SEL, INPUT_PULL_UP);
  
  /* Specific operations used in EMW3165 production */
#define NEED_RF_DRIVER_COPY_BASE    ((uint32_t)0x08008000)
#define TEMP_RF_DRIVER_BASE         ((uint32_t)0x08040000)
#define TEMP_RF_DRIVER_END          ((uint32_t)0x0807FFFF)
  
  const uint8_t isDriverNeedCopy = *(uint8_t *)(NEED_RF_DRIVER_COPY_BASE);
  const uint32_t totalLength = ( DRIVER_FLASH_SIZE < 0x40000)?  DRIVER_FLASH_SIZE:0x40000;
  const uint8_t crcResult = *(uint8_t *)(TEMP_RF_DRIVER_END);
  uint8_t targetCrcResult = 0;
  
  uint32_t copyLength;
  uint32_t destStartAddress_tmp = DRIVER_START_ADDRESS;
  uint32_t sourceStartAddress_tmp = TEMP_RF_DRIVER_BASE;
  uint32_t i;
  
  if ( isDriverNeedCopy != 0x0 )
    return;
  
  platform_log( "Bootloader start to copy RF driver..." );
  /* Copy RF driver to SPI flash */
  err = MicoFlashInitialize( (mico_flash_t)MICO_FLASH_FOR_DRIVER );
  require_noerr(err, exit);
  err = MicoFlashInitialize( (mico_flash_t)MICO_INTERNAL_FLASH );
  require_noerr(err, exit);
  err = MicoFlashErase( MICO_FLASH_FOR_DRIVER, DRIVER_START_ADDRESS, DRIVER_END_ADDRESS );
  require_noerr(err, exit);
  platform_log( "Time: %d", mico_get_time_no_os() );
  
  for(i = 0; i <= totalLength/SizePerRW; i++){
    if( i == totalLength/SizePerRW ){
      if(totalLength%SizePerRW)
        copyLength = totalLength%SizePerRW;
      else
        break;
    }else{
      copyLength = SizePerRW;
    }
    printf(".");
    err = MicoFlashRead( MICO_INTERNAL_FLASH, &sourceStartAddress_tmp, data , copyLength );
    require_noerr( err, exit );
    err = MicoFlashWrite( MICO_FLASH_FOR_DRIVER, &destStartAddress_tmp, data, copyLength);
    require_noerr(err, exit);
  }
  
  printf("\r\n");
  /* Check CRC-8 check-sum */
  platform_log( "Bootloader start to verify RF driver..." );
  sourceStartAddress_tmp = TEMP_RF_DRIVER_BASE;
  destStartAddress_tmp = DRIVER_START_ADDRESS;
  
  for(i = 0; i <= totalLength/SizePerRW; i++){
    if( i == totalLength/SizePerRW ){
      if(totalLength%SizePerRW)
        copyLength = totalLength%SizePerRW;
      else
        break;
    }else{
      copyLength = SizePerRW;
    }
    printf(".");
    err = MicoFlashRead( MICO_FLASH_FOR_DRIVER, &destStartAddress_tmp, data, copyLength );
    require_noerr( err, exit );
    
    targetCrcResult = CRC8_Table(targetCrcResult, data, copyLength);
  }
  
  printf("\r\n");
  //require_string( crcResult == targetCrcResult, exit, "Check-sum error" ); 
  if( crcResult != targetCrcResult ){
    platform_log("Check-sum error");
    while(1);
  }
  /* Clear RF driver from temperary storage */
  platform_log("Bootloader start to clear RF driver temporary storage...");
  
  err = MicoFlashInitialize( (mico_flash_t)MICO_INTERNAL_FLASH );
  require_noerr(err, exit);  
  
  /* Clear copy tag */
  err = MicoFlashErase(MICO_INTERNAL_FLASH, NEED_RF_DRIVER_COPY_BASE, NEED_RF_DRIVER_COPY_BASE);
  require_noerr(err, exit);
  
exit:
  MicoFlashFinalize( MICO_INTERNAL_FLASH );
  MicoFlashFinalize( MICO_FLASH_FOR_DRIVER );
}

#endif

void MicoSysLed(bool onoff)
{
  if (onoff) {
    MicoGpioOutputHigh( (mico_gpio_t)MICO_SYS_LED );
  } else {
    MicoGpioOutputLow( (mico_gpio_t)MICO_SYS_LED );
  }
}

void MicoRfLed(bool onoff)
{
  if (onoff) {
    MicoGpioOutputLow( (mico_gpio_t)MICO_RF_LED );
  } else {
    MicoGpioOutputHigh( (mico_gpio_t)MICO_RF_LED );
  }
}

bool MicoShouldEnterMFGMode(void)
{
  if(MicoGpioInputGet((mico_gpio_t)BOOT_SEL)==false && MicoGpioInputGet((mico_gpio_t)MFG_SEL)==false)
    return true;
  else
    return false;
}

bool MicoShouldEnterBootloader(void)
{
  if(MicoGpioInputGet((mico_gpio_t)BOOT_SEL)==false && MicoGpioInputGet((mico_gpio_t)MFG_SEL)==true)
    return true;
  else
    return false;
}

