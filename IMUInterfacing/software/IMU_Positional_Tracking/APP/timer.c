/*
 * timer.c
 *
 *  Created on: Nov 1, 2017
 *      Author: nemtech
 */

#include <cpu.h>
#include <lib_def.h>
#include <bsp.h>
#include <bsp_int.h>

#include <hps.h>
#include <socal.h>

#include "lib_def.h"
#include "os_cpu.h"
#include "timer.h"

void InitHPSTimerInterrupt(INT32U time, BSP_INT_FNCT_PTR handler) {
	// This version will use the oscl_clk based timers on the HPS core
	// Process
	// Choose one of the four timers (oscl timer 0, oscl timer 1, sptimer 0, sptimer 1)
	// Set to use user-defined count mode
	// Choose timer value should be equal to osc1_clk (50000000 HZ) == 2FAF080 actuall is 100000000
	// PSEUDOCODE:
	//  - Disable the timer
	//  - Program the Timer Mode: User Defined
	//  - Initialize the vector table: source 201 for oscl_0_timer
	//  - Set the interrupt mask to unmasked
	//  - Load the counter value
	//  - Enable the timer

	ARM_OSCL_TIMER_0_REG_CONTROL &= ARM_OSCL_TIMER_0_DISABLE;

	ARM_OSCL_TIMER_0_REG_CONTROL |= ARM_OSCL_TIMER_0_USER_MODE;

	ARM_OSCL_TIMER_0_REG_CONTROL &= ARM_OSCL_TIMER_0_INT_UNMASKED;

	ARM_OSCL_TIMER_0_REG_LOADCOUNT = time; // 250000000 of the oscl_clk should be one second

	BSP_IntVectSet   (201u,   // 201 is source for oscl_timer 0
	                         1,	    // prio
							 DEF_BIT_00,	    // cpu target list
							 handler  // ISR
							 );

	ARM_OSCL_TIMER_0_REG_CONTROL |= ARM_OSCL_TIMER_0_ENABLE;

	BSP_IntSrcEn(201u);
}


void Empty_TimerISR_Handler(CPU_INT32U cpu_id) {
	// Do stuff


	// READ EOI Reg to clear interrupt (PAGE 23-10/23-11 of Cyclone V Hard Processor System
	// Technical Reference Manual
	volatile int32_t status = ARM_OSCL_TIMER_0_REG_EOI;
}

