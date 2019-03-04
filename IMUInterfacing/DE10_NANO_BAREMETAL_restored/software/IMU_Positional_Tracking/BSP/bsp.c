/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               This BSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                             ALTERA SOC
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>

#include  <bsp.h>
#include  <bsp_int.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/


#define  CV_REG_GPIO_DR1 (*((CPU_REG32 *)0xFF709000))
#define  CV_REG_GPIO_DDR1 (*((CPU_REG32 *)0xFF709004))

#define  WD0_CRR  (*((CPU_REG32 *)0xFFD0200C))


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              BSP_Init()
*
* Description : Initialise the BSP.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_Init (void)
{

    BSP_Int_Init();

    BSP_LED_Init();

    return;
}


/*
*********************************************************************************************************
*                                           BSP_CPU_ClkFreq()
*
* Description : Return the CPU clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : CPU clock frequency in Hz.
*
* Caller(s)   : Various.
*
* Note(s)     : Currently hard coded in this example.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    return (800000000u);
}


/*
*********************************************************************************************************
*                                         BSP_Periph_ClkFreq()
*
* Description : Return the private peripheral clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : Clock frequency in Hz.
*
* Caller(s)   : Various.
*
* Note(s)     : Currently hard coded in this example.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_Periph_ClkFreq (void)
{
    return (200000000u);
}



/*
*********************************************************************************************************
*                                            BSP_LED_Init()
*
* Description : Initialise user LEDs.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_Init (void)
{

	CV_REG_GPIO_DDR1 |= DEF_BIT_24;
}


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON the HPS led.
*
* Argument(s) : void
*
* Return(s)   : none..
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_On   (void)
{
	CV_REG_GPIO_DR1 |= DEF_BIT_24;

}


/*
*********************************************************************************************************
*                                             BSP_LED_Off()
*
* Description : Turn OFF the HPS connected led.
*
* Argument(s) : void
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_Off  (void)
{
	CV_REG_GPIO_DR1 &= ~(DEF_BIT_24);
}


/*
*********************************************************************************************************
*                                        BSP_WatchDog_Reset()
*
* Description : Reset the platform watchdog.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_WatchDog_Reset  (void)
{
    WD0_CRR = 0x76;
}
