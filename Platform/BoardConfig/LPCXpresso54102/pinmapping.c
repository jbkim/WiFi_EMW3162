/***
 *File: gpio_pinmapping.h
 *board or platform  pin mapping. such as: gpio, i2c, spi, uart, pwm, adc,etc.
 *different board may have different configs.
 *
 *Created by Jerry Yu @ 2014-DEC-09.
 *
 * */

#include "platform.h"


/* Pin muxing table, only items that need changing from their default pin
   state are in this table.please look up the ckt. Not every pin is mapped. */
STATIC const PINMUX_GRP_T default_pinmuxing[] = {
	/* UART */
	{0, 0,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* UART0 RX */
	{0, 1,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* UART0 TX */

	{0, 2,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* NC */
    /* WIFI */
	{0, 3,  (IOCON_FUNC0 | IOCON_GPIO_MODE | IOCON_DIGITAL_EN)}, /* Wifi reset*/
	{0, 4,  (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN  | IOCON_GPIO_MODE)}, /* Wifi IRQ */
	{0, 22, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* Wifi wakeup host */
	{0, 21, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF)}, /* Wifi 32K clock. CLKOUT-CT32B3_MAT0 (GPIO input) */
	{1, 6,  (IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /* Wifi SPI1 CLK ,SCK1-CT32B1_MAT2 (SPI CLK) */
	{1, 7,  (IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /* Wifi SPI1 MOSI1-CT32B1_MAT2 (SPI MOSI) */
	{1, 14,  (IOCON_FUNC4 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /*Wifi SPI1 MISO */  
	{1, 15,  (IOCON_MODE_REPEATER)}, /*Wifi SPI1 SSEL0 (CS)*/

	/* Misc */
// 	{0, 22, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* NIOBE_CLKIN (GPIO input) */
// 	{0, 21, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* CLKOUT-CT32B3_MAT0 (GPIO input) */
	{0, 26, (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /* MICROSD_CDn (GPIO input) ####NOT WORKING #####*/
	{0, 9,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* I2S_RX_SDA (GPIO input) */
	{0, 11, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* SCK0-I2S_CLK (CT2_MAT1) used for DEBUG1 #####*/
	{0, 13, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* MIS0-I2S_WS (GPIO input) used for DEBUG2 ####*/
	{0, 18, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* I2S_TX_SDA (GPIO input) */
	{0, 19, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* IF_JTAG_TDI (GPIO input) */

//	{0, 15, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* SWO */
//	{0, 16, (IOCON_FUNC5 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* SWCLK_TCK */
//	{0, 17, (IOCON_FUNC5 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* SWDIO */

	/* I2C */
	{0, 23, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN | IOCON_STDI2C_EN)}, /* I2C0_SCL (SCL) */
	{0, 24, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN | IOCON_STDI2C_EN)}, /* I2C0_SDA-WAKEUP (SDA) */

	/* Sensor related */
//	{0, 4,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* GYR_INT1 (GPIO input) */
	{0, 5,  (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* AM_PX_INT (GPIO input) */
	{0, 6,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* ACCL_INT1 (GPIO input) */
	{0, 7,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* ACCL_INT2 (GPIO input) */
	{0, 8,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* MAG_DRDY (GPIO input) */
	{0, 10, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* MAG_INT3 (GPIO input) */
	{0, 20, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* AUDIO_INT (GPIO input) */
	{0, 25, (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* SEN300_INT (GPIO input) */

	/* Bridge */
	{0, 12, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* BRIDGE_MOSI (SPI MOSI) */
	{0, 14, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* BRIDGE_SSEL (SPISSEL) */
	{0, 27, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN | IOCON_STDI2C_EN)}, /* BRIDGE_SCL (SCL) */
	{0, 28, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN | IOCON_STDI2C_EN)}, /* BRIDGE_SDA (SDA) */
	{0, 29, (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* BRIDGE_GPIO (GPIO) */
	{0, 30, (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /* BRIDGE_INTR (GPIO) */
	{1, 3,  (IOCON_FUNC5 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* BRIDGE_SCK (SCK) */
	{1, 4,  (IOCON_FUNC5 | IOCON_MODE_INACT | IOCON_DIGITAL_EN)}, /* BRIDGE_MISO (MISO) */

	/* SDMMC card interface NOT USED so set them as GPIOs */
	/* P1_5 left as GPIO with pull-up - the default state */
	{1, 5,  (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN)}, /*  */
	// {1, 6,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* SCK1-CT32B1_MAT2 (SPI CLK) */
	// {1, 7,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* MOSI1-CT32B1_MAT2 (SPI MOSI) */
	{1, 8,  (IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGITAL_EN)}, /* MISO1-CT32B1_MAT3 (SPI MISO) */
};

/* Sets up default system pin muxing */
void Board_SetupMuxing(void)
{
	/* Enable IOCON clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_IOCON_SetPinMuxing(LPC_IOCON, default_pinmuxing, sizeof(default_pinmuxing) / sizeof(PINMUX_GRP_T));

	/* IOCON clock left on, this is needed if CLKIN is used. */
}




