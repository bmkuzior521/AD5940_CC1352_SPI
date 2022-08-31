/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC1352R1_LAUNCHXL
#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== CCFG ========
 */


/*
 *  ======== GPIO ========
 */
extern const uint_least8_t CONFIG_GPIO_LED_0_CONST;
#define CONFIG_GPIO_LED_0 6

extern const uint_least8_t CONFIG_GPIO_LED_1_CONST;
#define CONFIG_GPIO_LED_1 7

extern const uint_least8_t CONFIG_SPI_MASTER_READY_CONST;
#define CONFIG_SPI_MASTER_READY 15

extern const uint_least8_t CONFIG_SPI_SLAVE_READY_CONST;
#define CONFIG_SPI_SLAVE_READY 21

extern const uint_least8_t AD5490_CS_CONST;
#define AD5490_CS 17

extern const uint_least8_t AD5940_RST_CONST;
#define AD5940_RST 22

/* Owned by CONFIG_SPI_MASTER as  */
extern const uint_least8_t CONFIG_GPIO_SPI_MASTER_SCLK_CONST;
#define CONFIG_GPIO_SPI_MASTER_SCLK 10

/* Owned by CONFIG_SPI_MASTER as  */
extern const uint_least8_t CONFIG_GPIO_SPI_MASTER_MISO_CONST;
#define CONFIG_GPIO_SPI_MASTER_MISO 8

/* Owned by CONFIG_SPI_MASTER as  */
extern const uint_least8_t CONFIG_GPIO_SPI_MASTER_MOSI_CONST;
#define CONFIG_GPIO_SPI_MASTER_MOSI 9

/* Owned by CONFIG_UART2_0 as  */
extern const uint_least8_t CONFIG_GPIO_UART2_0_TX_CONST;
#define CONFIG_GPIO_UART2_0_TX 13

/* Owned by CONFIG_UART2_0 as  */
extern const uint_least8_t CONFIG_GPIO_UART2_0_RX_CONST;
#define CONFIG_GPIO_UART2_0_RX 12

/* Owned by CONFIG_SPI_MASTER as  */
extern const uint_least8_t CONFIG_GPIO_SPI_MASTER_SS_CONST;
#define CONFIG_GPIO_SPI_MASTER_SS 11

/* The range of pins available on this device */
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== SPI ========
 */

/*
 *  MOSI: DIO9
 *  MISO: DIO8
 *  SCLK: DIO10
 *  SS: DIO11
 *  LaunchPad SPI Bus with Chip Select
 */
extern const uint_least8_t              CONFIG_SPI_MASTER_CONST;
#define CONFIG_SPI_MASTER               0
#define CONFIG_TI_DRIVERS_SPI_COUNT     1


/*
 *  ======== Timer ========
 */

extern const uint_least8_t                  CONFIG_TIMER_0_CONST;
#define CONFIG_TIMER_0                      0
#define CONFIG_TI_DRIVERS_TIMER_COUNT       1


/*
 *  ======== UART2 ========
 */

/*
 *  TX: DIO13
 *  RX: DIO12
 *  XDS110 UART
 */
extern const uint_least8_t                  CONFIG_UART2_0_CONST;
#define CONFIG_UART2_0                      0
#define CONFIG_TI_DRIVERS_UART2_COUNT       1


/*
 *  ======== GPTimer ========
 */

extern const uint_least8_t                  CONFIG_GPTIMER_0_CONST;
#define CONFIG_GPTIMER_0                    0
#define CONFIG_TI_DRIVERS_GPTIMER_COUNT     1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
