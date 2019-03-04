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
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  ARM_PRIV_PERIPH_BASE  (0xFFFEC000)                     /* CPU private peripheral base address.                 */

#define  ARM_GIC_INT_SRC_CNT   (256u)


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void        BSP_Init           (void);

CPU_INT32U  BSP_CPU_ClkFreq    (void);

CPU_INT32U  BSP_Periph_ClkFreq (void);

void        BSP_LED_Init       (void);

void        BSP_LED_On         (void);

void        BSP_LED_Off        (void);

void        BSP_BranchPredictorEn (void);

void        BSP_L2C310Config   (void);

void        BSP_CachesEn       (void);

void        BSP_WatchDog_Reset (void);

#endif /* BSP_PRESENT */
