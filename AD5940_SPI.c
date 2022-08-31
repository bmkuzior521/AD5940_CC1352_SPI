/*!
 *****************************************************************************
 @file:    AD5940_SPI.c
 @author:  $Author: nxu2 $
 @brief:   Basic register read/write test example.
 @version: $Revision: 766 $
 @date:    $Date: 2017-08-21 14:09:35 +0100 (Mon, 21 Aug 2017) $
 -----------------------------------------------------------------------------

Copyright (c) 2017-2019 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.

*****************************************************************************/

/**
 * This example shows how to read/write AD5940 registers through SPI.
 * Use function called AD5940_ReadReg and AD5940_WriteReg.
**/
//#include "Drivers/AD5940Lib/ad5940.h"
#include "ad5940.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include <ti/display/Display.h>
#include "BIOZ-2Wire.h"
extern Display_Handle disp;

#define APPBUFF_SIZE 512
uint32_t AppBuff[APPBUFF_SIZE];

/* It's your choice here how to do with the data. Here is just an example to print them to UART */
int32_t BIOZShowResult(uint32_t *pData, uint32_t DataCount)
{
  float freq;

  fImpCar_Type *pImp = (fImpCar_Type*)pData;
  AppBIOZCtrl(BIOZCTRL_GETFREQ, &freq);

  /*Process data*/
  int i;
  for(i=0;i<DataCount;i++)
  {
        Display_printf(disp, 0, 0, "Freq:%.2f ", freq);
    //printf("RzMag: %f Ohm , RzPhase: %f \n",AD5940_ComplexMag(&pImp[i]), AD5940_ComplexPhase(&pImp[i])*180/MATH_PI);
        Display_printf(disp, 0, 0, "Impedance:(Real,Image) = (%f,%f)\n", pImp[i].Real, pImp[i].Image);
  }
  return 0;
}

/* Initialize AD5940 basic blocks like clock */
static int32_t AD5940PlatformCfg(void)
{
  CLKCfg_Type clk_cfg;
  FIFOCfg_Type fifo_cfg;
  AGPIOCfg_Type gpio_cfg;

  /* Use hardware reset */
  AD5940_HWReset();
  /* Platform configuration */
  AD5940_Initialize();
  /* Step1. Configure clock */
  clk_cfg.ADCClkDiv = ADCCLKDIV_1;
  clk_cfg.ADCCLkSrc = ADCCLKSRC_XTAL;
  clk_cfg.SysClkDiv = SYSCLKDIV_1;
  clk_cfg.SysClkSrc = SYSCLKSRC_XTAL;
  clk_cfg.HfOSC32MHzMode = bFALSE;
  clk_cfg.HFOSCEn = bFALSE;
  clk_cfg.HFXTALEn = bTRUE;
  clk_cfg.LFOSCEn = bTRUE;
  AD5940_CLKCfg(&clk_cfg);
  /* Step2. Configure FIFO and Sequencer*/
  fifo_cfg.FIFOEn = bFALSE;
  fifo_cfg.FIFOMode = FIFOMODE_FIFO;
  fifo_cfg.FIFOSize = FIFOSIZE_4KB;                       /* 4kB for FIFO, The reset 2kB for sequencer */
  fifo_cfg.FIFOSrc = FIFOSRC_DFT;
  fifo_cfg.FIFOThresh = 4;
  AD5940_FIFOCfg(&fifo_cfg);                             /* Disable to reset FIFO. */
  fifo_cfg.FIFOEn = bTRUE;
  AD5940_FIFOCfg(&fifo_cfg);                             /* Enable FIFO here */

  /* Step3. Interrupt controller */
  AD5940_INTCCfg(AFEINTC_1, AFEINTSRC_ALLINT, bTRUE);           /* Enable all interrupt in Interrupt Controller 1, so we can check INTC flags */
  AD5940_INTCCfg(AFEINTC_0, AFEINTSRC_DATAFIFOTHRESH, bTRUE);   /* Interrupt Controller 0 will control GP0 to generate interrupt to MCU */
  AD5940_INTCClrFlag(AFEINTSRC_ALLINT);
  /* Step4: Reconfigure GPIO */
  gpio_cfg.FuncSet = GP6_SYNC|GP5_SYNC|GP4_SYNC|GP2_TRIG|GP1_SYNC|GP0_INT;
  gpio_cfg.InputEnSet = AGPIO_Pin2;
  gpio_cfg.OutputEnSet = AGPIO_Pin0|AGPIO_Pin1|AGPIO_Pin4|AGPIO_Pin5|AGPIO_Pin6;
  gpio_cfg.OutVal = 0;
  gpio_cfg.PullEnSet = 0;

  AD5940_AGPIOCfg(&gpio_cfg);
  AD5940_SleepKeyCtrlS(SLPKEY_UNLOCK);  /* Allow AFE to enter sleep mode. */
  return 0;
}

/* !!Change the application parameters here if you want to change it to none-default value */
void AD5940BIOZStructInit(void)
{
  AppBIOZCfg_Type *pBIOZCfg;
  AppBIOZGetCfg(&pBIOZCfg);

  pBIOZCfg->SeqStartAddr = 0;
  pBIOZCfg->MaxSeqLen = 512;

    pBIOZCfg->SinFreq = 20e3;           /* 20kHz. This value is ignored if SweepEn = bTRUE */
    pBIOZCfg->RcalVal = 10000.0;    /* Value of RCAl on the evaluaiton board */
    pBIOZCfg->HstiaRtiaSel = HSTIARTIA_200;

    /* Configure Switch matrix */
    pBIOZCfg->DswitchSel = SWD_CE0;
    pBIOZCfg->PswitchSel = SWP_CE0;
    pBIOZCfg->NswitchSel = SWN_AIN2;
    pBIOZCfg->TswitchSel = SWN_AIN2;

  /* Configure Sweep Parameters */
  pBIOZCfg->SweepCfg.SweepEn = bTRUE;
  pBIOZCfg->SweepCfg.SweepStart = 1000;
  pBIOZCfg->SweepCfg.SweepStop = 200000.0;
  pBIOZCfg->SweepCfg.SweepPoints = 40;  /* Maximum is 100 */
  pBIOZCfg->SweepCfg.SweepLog = bFALSE;

    pBIOZCfg->BIOZODR = 5;         /* ODR(Sample Rate) 5Hz */
    pBIOZCfg->NumOfData = -1;       /* Never stop until you stop it manually by AppBIOZCtrl() function */
}

static AD5940Err AppIMPMeasureGen(void)
{
  AD5940Err error = AD5940ERR_OK;

  uint32_t WaitClks;
  ClksCalInfo_Type clks_cal;

  AppBIOZCfg_Type *pBIOZCfg;
    AppBIOZGetCfg(&pBIOZCfg);

  clks_cal.DataType = DATATYPE_DFT;
  clks_cal.DftSrc = pBIOZCfg->DftSrc;
  clks_cal.DataCount = 1L<<(pBIOZCfg->DftNum+2); /* 2^(DFTNUMBER+2) */
  clks_cal.ADCSinc2Osr = pBIOZCfg->ADCSinc2Osr;
  clks_cal.ADCSinc3Osr = pBIOZCfg->ADCSinc3Osr;
//  clks_cal.ADCAvgNum = pBIOZCfg->ADCAvgNum;
  clks_cal.RatioSys2AdcClk = pBIOZCfg->SysClkFreq/pBIOZCfg->AdcClkFreq;
  AD5940_ClksCalculate(&clks_cal, &WaitClks);

  AD5940_AGPIOSet(AGPIO_Pin2); /* Set GPIO2, clear others that under control */
  /* Measure Impedance */
  AD5940_WriteReg(REG_AFE_SWCON, (0x5<<BITP_AFE_SWCON_DMUXCON)|(5<<BITP_AFE_SWCON_PMUXCON)\
    |(0x9<<BITP_AFE_SWCON_NMUXCON)|(0x5<<BITP_AFE_SWCON_TMUXCON)|\
      BITM_AFE_SWCON_T9CON);

  AD5940_AFECtrlS(AFECTRL_HSTIAPWR|AFECTRL_INAMPPWR|AFECTRL_EXTBUFPWR|\
    AFECTRL_WG|AFECTRL_DACREFPWR|AFECTRL_HSDACPWR|\
      AFECTRL_SINC2NOTCH|AFECTRL_DCBUFPWR, bTRUE);
  AD5940_AFECtrlS(AFECTRL_ADCPWR|AFECTRL_SINC2NOTCH, bTRUE);  /* Enable Waveform generator */

    /* Delay for ADC power up */
    AD5940_Delay10us(16*250*100000);
  AD5940_AFECtrlS(AFECTRL_ADCCNV|AFECTRL_ADCPWR|AFECTRL_DFT, bTRUE);  /* Start ADC convert and DFT */
  /* Wait for ADC and DFT to finish converting samples */
  AD5940_Delay10us(WaitClks* (pBIOZCfg->AdcClkFreq/pBIOZCfg->SysClkFreq)*100000);
  AD5940_AFECtrlS(AFECTRL_ADCPWR|AFECTRL_ADCCNV|AFECTRL_DFT|AFECTRL_SINC2NOTCH/*|AFECTRL_WG*/, bFALSE);  /* Stop ADC convert and DFT */
  AD5940_AGPIOClr(AGPIO_Pin2); /* Clr GPIO2 */
  return AD5940ERR_OK;
}

void AD5940_Main(void)
{
//      uint32_t temp;
//      AD5940PlatformCfg();
//      AD5940BIOZStructInit(); /* Configure your parameters in this function */
//      //AppBIOZSeqMeasureGen();
//      Display_printf(disp, 0, 0, "Yo\n");
//      AppIMPMeasureGen();
//      BIOZShowResult(AppBuff, temp); /* Show the results to UART */

//      AppBIOZInit(AppBuff, APPBUFF_SIZE);    /* Initialize BIOZ application. Provide a buffer, which is used to store sequencer commands */
//      AppBIOZCtrl(BIOZCTRL_START, 0);         /* Control BIOZ measurement to start. Second parameter has no meaning with this command. */

//      while(1)
//      {
//        /* Check if interrupt flag which will be set when interrupt occurred. */
//        //if(AD5940_GetMCUIntFlag())
//        //{
////          AD5940_ClrMCUIntFlag(); /* Clear this flag */
////          temp = APPBUFF_SIZE;
//          AppBIOZISR(AppBuff, &temp); /* Deal with it and provide a buffer to store data we got */
//          BIOZShowResult(AppBuff, temp); /* Show the results to UART */
//        //}
//      }
  unsigned long temp, i;
  /**
   * Hardware reset can always put AD5940 to default state.
   * We recommend to use hardware reset rather than software reset
   * because there are some situations that SPI won't work, for example, AD59840 is in hibernate mode,
   * or AD5940 system clock is 32kHz that SPI bus clock should also be limited..
   * */
  AD5940_HWReset();
//  Display_printf(disp, 0, 0, "HW GOOD\n");
  /**
   * @note MUST call this function whenever there is reset happened. This function will put AD5940 to right state.
   *       The reset can be software reset or hardware reset or power up reset.
  */
  AD5940_Initialize();
//  Display_printf(disp, 0, 0, "INIT GOOd\n");
  /**
   * Normal application code starts here.
  */
  /**
   * Read register test.
  */
  temp = AD5940_ReadReg(REG_AFECON_ADIID);
  Display_printf(disp, 0, 0, "Read ADIID register, got: 0x%04lx\n", temp);
  if(temp != AD5940_ADIID)
      Display_printf(disp, 0, 0, "Read register test failed.\n" );
  else
      Display_printf(disp, 0, 0, "Read register test pass\n");
  /**
   * Write register test.
   * */
  srand(0x1234);
  i =10000;
  while(i--)
  {
    static unsigned long count;
    static unsigned long data;
    /* Generate a 32bit random data */
    data = rand()&0xffff;
    data <<= 16;
    data |= rand()&0xffff;
    count ++;	/* Read write count */
    /**
     * Register CALDATLOCK is 32-bit width, it's readable and writable.
     * We use it to test SPI register access.
    */
    AD5940_WriteReg(REG_AFE_CALDATLOCK, data);
    temp = AD5940_ReadReg(REG_AFE_CALDATLOCK);
    if(temp != data)
        Display_printf(disp, 0, 0, "Write register test failed @0x%08lx\n", data);
    if(!(count%1000))
        Display_printf(disp, 0, 0, "Read/Write has been done %ld times, latest data is 0x%08lx\n", count, data);
  }
  Display_printf(disp, 0, 0, "SPI read/write test completed");
  while(1);
}

