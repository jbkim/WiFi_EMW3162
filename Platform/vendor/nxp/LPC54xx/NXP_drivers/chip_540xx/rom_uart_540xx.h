/*
 * @brief LPC412x UART ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __ROM_UART_412x_H_
#define __ROM_UART_412x_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup UARTROM_412x CHIP: LPC412x UART ROM Driver
 * @ingroup CHIP_412x_Drivers
 * @{
 */

/**
 * @brief UART ROM driver - UART errors in UART configuration used in uart_init function
 */
#define OVERRUN_ERR_EN		(1 << 0)	/*!< Bit 0: Enable overrun error */
#define UNDERRUN_ERR_EN		(1 << 1)	/*!< Bit 1: Enable underrun error */
#define FRAME_ERR_EN		(1 << 2)	/*!< Bit 2: enable frame error */
#define PARITY_ERR_EN		(1 << 3)	/*!< Bit 3: enable parity error */
#define RXNOISE_ERR_EN		(1 << 4)	/*!< Bit 4: enable receive noise error */

/**
 * Macros for UART errors
 */
/*!< Enable all the UART errors */
#define ALL_ERR_EN			(OVERRUN_ERR_EN | UNDERRUN_ERR_EN | FRAME_ERR_EN | PARITY_ERR_EN | \
							 RXNOISE_ERR_EN)
/*!< Disable all the errors */
#define NO_ERR_EN			(0)

/**
 * Transfer mode values in UART parameter structure.
 * Used in uart_get_line & uart_put_line function
 */
/*!< 0x00: uart_get_line: stop transfer when the buffer is full */
/*!< 0x00: uart_put_line: stop transfer when the buffer is empty */
#define TX_MODE_BUF_EMPTY		(0x00)
#define RX_MODE_BUF_FULL		(0x00)
/*!< 0x01: uart_get_line: stop transfer when CRLF are received */
/*!< 0x01: uart_put_line: transfer stopped after reaching \0 and CRLF is sent out after that */
#define TX_MODE_SZERO_SEND_CRLF	(0x01)
#define RX_MODE_CRLF_RECVD		(0x01)
/*!< 0x02: uart_get_line: stop transfer when LF are received */
/*!< 0x02: uart_put_line: transfer stopped after reaching \0. And LF is sent out after that */
#define TX_MODE_SZERO_SEND_LF	(0x02)
#define RX_MODE_LF_RECVD		(0x02)
/*!< 0x03: uart_get_line: RESERVED */
/*!< 0x03: uart_put_line: transfer stopped after reaching \0 */
#define TX_MODE_SZERO			(0x03)

/**
 * @brief UART ROM driver modes
 */
#define DRIVER_MODE_POLLING		(0x00)	/*!< Polling mode */
#define DRIVER_MODE_INTERRUPT	(0x01)	/*!< Interrupt mode */
#define DRIVER_MODE_DMA			(0x02)	/*!< DMA mode */

/**
 * @brief UART ROM driver UART handle
 */
typedef void *UART_HANDLE_T;

/**
 * @brief UART ROM driver UART callback function
 */
typedef void (*UART_CALLBK_T)(uint32_t err_code, uint32_t n);

/**
 * @brief UART ROM driver configutaion structure
 */
typedef struct {
	uint32_t sys_clk_in_hz;		/*!< System clock in Hz */
	uint32_t baudrate_in_hz;	/*!< Baud rate in Hz */
	uint8_t  config;			/*!< Configuration value */
								/*!<  bit1:0  Data Length: 00: 7 bits length, 01: 8 bits length, others: reserved */
								/*!<  bit3:2  Parity: 00: No Parity, 01: reserved, 10: Even, 11: Odd */
								/*!<  bit4:   Stop Bit(s): 0: 1 Stop bit, 1: 2 Stop bits */
	uint8_t sync_mod;			/*!< Sync mode settings */
								/*!<  bit0:  Mode: 0: Asynchronous mode, 1: Synchronous  mode */
								/*!<  bit1:  0: Un_RXD is sampled on the falling edge of SCLK */
								/*!<         1: Un_RXD is sampled on the rising edge of SCLK */
								/*!<  bit2:  0: Start and stop bits are transmitted as in asynchronous mode) */
								/*!<         1: Start and stop bits are not transmitted) */
								/*!<  bit3:  0: The UART is a  slave in Synchronous mode */
								/*!<         1: The UART is a master in Synchronous mode */
	uint16_t error_en;			/*!< Errors to be enabled */
								/*!<  bit0: Overrun Errors Enabled */
								/*!<  bit1: Underrun Errors Enabled */
								/*!<  bit2: FrameErr Errors Enabled */
								/*!<  bit3: ParityErr Errors Enabled */
								/*!<  bit4: RxNoise Errors Enabled */
} UART_CONFIG_T;

/**
 * @brief UART ROM driver parameter structure
 */
typedef struct {
	uint8_t         *buffer;		/*!< Pointer to data buffer */
	uint32_t        size;			/*!< Size of the buffer */
	uint16_t        transfer_mode;	/*!< Transfer mode settings */
									/*!<   0x00: uart_get_line: stop transfer when the buffer is full */
									/*!<   0x00: uart_put_line: stop transfer when the buffer is empty */
									/*!<   0x01: uart_get_line: stop transfer when CRLF are received */
									/*!<   0x01: uart_put_line: transfer stopped after reaching \0 and CRLF is sent out after that */
									/*!<   0x02: uart_get_line: stop transfer when LF are received */
									/*!<   0x02: uart_put_line: transfer stopped after reaching \0 and LF is sent out after that */
									/*!<   0x03: uart_get_line: RESERVED */
									/*!<   0x03: uart_put_line: transfer stopped after reaching \0 */
	uint8_t        driver_mode;   // 0x00: Polling mode, function is blocked until transfer is finished.
																// 0x01: Intr mode, function exit immediately, callback function is invoked when transfer is finished.
                                // 0x02: DMA mode, in case DMA block is available, data transferred by Uart is precessed by DMA, 
                                //       and data size is buffer size, not controlled by transfer_mode
                                //       DMA req function is called for Uart DMA channel setup, 
                                //       then DMA callback function indicate that transfer is finished. 
  uint8_t        dma_num;       // DMA channel number in case DMA mode is enabled.
  UART_CALLBK_T  callback_func_pt; 	// callback function
  uint32_t       dma;           // DMA handler
} UART_PARAM_T;

/**
 * @brief UART ROM driver APIs structure
 */
typedef struct UARTD_API {
	uint32_t (*uart_get_mem_size)(void);
	UART_HANDLE_T (*uart_setup)(uint32_t base_addr, uint8_t *ram);
	uint32_t (*uart_init)(UART_HANDLE_T handle, UART_CONFIG_T *set);
	//--polling functions--//
	uint8_t (*uart_get_char)(UART_HANDLE_T handle);
	void (*uart_put_char)(UART_HANDLE_T handle, uint8_t data);
	uint32_t (*uart_get_line)(UART_HANDLE_T handle, UART_PARAM_T * param);
	uint32_t (*uart_put_line)(UART_HANDLE_T handle, UART_PARAM_T * param);
	//--interrupt functions--//
	void (*uart_isr)(UART_HANDLE_T handle);
  uint32_t  (*uart_get_firmware_version)( void );
} UARTD_API_T;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROM_UART_412x_H_ */
