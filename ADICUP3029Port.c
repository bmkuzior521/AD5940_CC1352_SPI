/*!
 *****************************************************************************
 @file:    ADICUP3029Port.c
 @author:  Neo Xu
 @brief:   The port for ADI's ADICUP3029 board.
 -----------------------------------------------------------------------------

Copyright (c) 2017-2019 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.

*****************************************************************************/

#include <AD5940.h>
#include <stdint.h>
//#include <board.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/display/Display.h>
#include <stdbool.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/cpu.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

/* Driver configuration */
#include "ti_drivers_config.h"

extern AD_CS;
extern AD_RS;
extern SPI_Handle      masterSpi;
extern SPI_Params      spiParams;
extern SPI_Transaction transaction;
extern SPI_Transaction AD5940_transaction;
extern bool            transferOK;
extern int32_t         status;

extern Display_Handle disp;

/**
	@brief Using SPI to transmit N bytes and return the received bytes. This function targets to 
         provide a more efficient way to transmit/receive data.
	@param pSendBuffer :{0 - 0xFFFFFFFF}
      - Pointer to the data to be sent.
	@param pRecvBuff :{0 - 0xFFFFFFFF}
      - Pointer to the buffer used to store received data.
	@param length :{0 - 0xFFFFFFFF}
      - Data length in SendBuffer.
	@return None.
**/
void AD5940_ReadWriteNBytes(unsigned char *pSendBuffer,unsigned char *pRecvBuff,unsigned long length)
{      uint8_t  tx[4];
       uint8_t  rx[4];
    if(length==1){
        /*
         * Packet Setup
         */
           transaction.count = 1;
           transaction.txBuf = (void *)pSendBuffer;
           transaction.rxBuf = (void *)rx;
           transferOK = SPI_transfer(masterSpi, &transaction);
    }
    else if(length==2){
        /*
         * Packet Setup
         */
//           tx[0] = (*pSendBuffer>>8);
//           tx[1] = (*pSendBuffer&0xff);

           transaction.count = 2;
           transaction.txBuf = (void *)pSendBuffer;
           transaction.rxBuf = (void *)pRecvBuff;
           transferOK = SPI_transfer(masterSpi, &transaction);
    }
    else if(length==4){
        /*
         * Packet Setup
         */
//           tx[0] = (*pSendBuffer>>24)&0xff;
//           tx[1] = (*pSendBuffer>>16)&0xff;
//           tx[2] = (*pSendBuffer>>8)&0xff;
//           tx[3] = (*pSendBuffer)&0xff;

           transaction.count = 4;
           transaction.txBuf = (void *)pSendBuffer;
           transaction.rxBuf = (void *)pRecvBuff;
           transferOK = SPI_transfer(masterSpi, &transaction);
    }
    else{
        Display_printf(disp, 0, 0, "R/W Length Error\n");
        while (1);
    }
            if (transferOK)
            {
//                Display_printf(disp, 0, 0, "TX GOOD!!\n");
            }
            else
            {
                Display_printf(disp, 0, 0, "Unsuccessful master SPI transfer");
                while(1){
                    AD5940_Delay10us(1000);
                    break;
                }
            }
}

void AD5940_CsClr(void)
{
    GPIO_write(AD5490_CS, 0);
}

void AD5940_CsSet(void)
{
    GPIO_write(AD5490_CS, 1);
}

void AD5940_RstSet(void)
{
    GPIO_write(AD5940_RST, 1);
}

void AD5940_RstClr(void)
{
    GPIO_write(AD5940_RST, 0);
}

void AD5940_Delay10us(uint32_t time)
{
    unsigned long i;
        for(i=0; i<time; i++){
          CPUdelay(75); //160
        }
}

uint32_t AD5940_GetMCUIntFlag(void)
{
//   return ucInterrupted;
}

uint32_t AD5940_ClrMCUIntFlag(void)
{

//   ucInterrupted = 0;
   return 1;
}

/* Functions that used to initialize MCU platform */

uint32_t AD5940_MCUResourceInit(void *pCfg)
{
  GPIO_init();
  SPI_init();

  /*
   * GPIO Config
   */

//      GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_HIGH);
//      GPIO_setConfig(Board_GPIO_LED1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);
      AD5940_CsSet();
      AD5940_RstSet();
      AD5940_Delay10us(20);

  /*
   * SPI Config
   */

      SPI_Params_init(&spiParams);
      spiParams.frameFormat = SPI_POL0_PHA0;
      spiParams.transferMode = SPI_MODE_BLOCKING;
      spiParams.bitRate = 400000;
      spiParams.dataSize = 8;
      spiParams.mode = SPI_MASTER;




  AD5940_CsSet();
  AD5940_RstSet();
  AD5940_Delay10us(20);

  /*
   * SPI Open
   */
      masterSpi = SPI_open(CONFIG_SPI_MASTER, &spiParams);

      //debug
      if (masterSpi == NULL) {
          Display_printf(disp, 0, 0, "Error initializing master SPI\n");
          //while (1);
          }
       else {
          Display_printf(disp, 0, 0, "Master SPI initialized\n");
          }
//        #ifdef DEBUG
//            System_printf("BME Read Fail.\n");
//            System_flush();
//        #endif

//      uint8_t txt[2];
//      uint8_t rxt[2];
//      txt[0] = 0x20;
//      txt[1] = 0x51;
//      AD5940_CsSet();
//
//
//      transaction.count = 2;
//                 transaction.txBuf = (void *)txt;
//                 transaction.rxBuf = (void *)rxt;
//                 while(1){
//                 AD5940_CsClr();
//                 transferOK = SPI_transfer(masterSpi, &transaction);
//                 AD5940_CsSet();
//                 if (transferOK)
//                         {
//                             Display_printf(disp, 0, 0, "Master received: %s", rxt);
//                         }
//                         else
//                         {
//                             Display_printf(disp, 0, 0, "Unsuccessful master SPI transfer");
//                         }}

  return 0;
}

/* MCU related external line interrupt service routine */
void Ext_Int0_Handler()
{

//   ucInterrupted = 1;
  /* This example just set the flag and deal with interrupt in AD5940Main function. It's your choice to choose how to process interrupt. */
}

