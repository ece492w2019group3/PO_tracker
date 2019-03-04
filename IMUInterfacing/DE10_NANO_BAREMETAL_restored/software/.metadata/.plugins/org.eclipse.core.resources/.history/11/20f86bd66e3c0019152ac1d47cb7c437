/*
 * dispensing.c

 *
 *  Created on: Mar 26, 2018
 *      Author: vanselow
 */
#include "../models/models.h"
#include "../pwm/pwm.h"
#include "../adc/adc.h"
#include "../tasks.h"
#include "dispensing.h"

#include <ucos_ii.h>
#include <cpu.h>
#define TASK_STACK_SIZE 4096
#define	PAUSE_TARGETS_SIZE 4

const int32_t pause_targets[PAUSE_TARGETS_SIZE] = {50, 25, 10, 5};

CPU_STK PourTaskStk[TASK_STACK_SIZE];

extern OS_EVENT * pouring_semaphore;

// For simultaneous dispensing
void SimultaneousDispenseTaskInit(recipe * dispensing_recipe)
{
	uint8_t os_err = 0;
	uint8_t task_priority = POUR_TASK_PRIORITY;
	os_err = OSTaskCreateExt((void (*)(void *)) SimultaneousDispenseTask,   /* Create the start task.                               */
							 (void          * ) dispensing_recipe,
							 (OS_STK        * )&PourTaskStk[TASK_STACK_SIZE - 1],
							 (INT8U           ) task_priority,
							 (INT16U          ) task_priority,  // reuse prio for ID
							 (OS_STK        * )&PourTaskStk[0],
							 (INT32U          ) TASK_STACK_SIZE,
							 (void          * )0,
							 (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

	if (os_err != OS_ERR_NONE)
	{

	}
}

void OrderedDispenseTaskInit(recipe * dispensing_recipe)
{
	uint8_t os_err = 0;
	uint8_t task_priority = POUR_TASK_PRIORITY;
	os_err = OSTaskCreateExt((void (*)(void *)) OrderedDispenseTask,   /* Create the start task.                               */
							 (void          * ) dispensing_recipe,
							 (OS_STK        * )&PourTaskStk[TASK_STACK_SIZE - 1],
							 (INT8U           ) task_priority,
							 (INT16U          ) task_priority,  // reuse prio for ID
							 (OS_STK        * )&PourTaskStk[0],
							 (INT32U          ) TASK_STACK_SIZE,
							 (void          * )0,
							 (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

	if (os_err != OS_ERR_NONE)
	{

	}
}

void SimultaneousDispenseTask(void * p_arg)
{
	uint8_t states[3] = { 0 };
	uint8_t done[3] = { 0 };
	uint8_t pause[3] = { 0 };
	int32_t target_volumes[3] = { 0 };
	uint8_t err = 0;
	recipe dispensing_recipe = *(recipe*)p_arg;
	for(int i = 0; i < 3; i++)
	{
		target_volumes[i] = getTargetVolume(i, dispensing_recipe.ingredients[i].amount);
	}
	while(!(done[0] & done[1] & done[2]))
	{
		for(int i = 0; i < 3; i++)
		{
			int32_t pause_target = pause_targets[states[i]];
			
			if(done[i])
			{
				ControlMotor(i, 0);
			}
			else if(pause[i] > 0)
			{
				ControlMotor(i, 0);
				pause[i]--;
			}
			else
			{
				ControlMotor(i, 100);
				if((getCurrentVolume(i) - target_volumes[i] < pause_target))
				{
					if(states[i] < PAUSE_TARGETS_SIZE - 1)
					{
						states[i]++;
						pause[i] = 5;
					}
					else
					{
						done[i] = 1;
						ControlMotor(i, 0);
					}
				}
			}
		}
		OSTimeDlyHMSM(0, 0, 0, 50); // Check every 50ms
	}

	OSSemPost(pouring_semaphore);
    OSTaskDel(OS_PRIO_SELF);
}

void OrderedDispenseTask(void * p_arg)
{
	uint8_t err = 0;

	recipe dispensing_recipe = *(recipe*)p_arg;

	for(int order = 0; order < 3; order++)
	{
		for(int i = 0; i < 3; i++)
		{
			if(dispensing_recipe.ingredients[i].order == order)
			{
				int16_t amount = dispensing_recipe.ingredients[i].amount;
				int32_t target_volume = getTargetVolume(i, amount);
				
				for(int j = 0; j < PAUSE_TARGETS_SIZE; j++)
				{			
					ControlMotor(i, 100);
					while((getCurrentVolume(i) - target_volume > pause_targets[j]))
					{
						OSTimeDlyHMSM(0, 0, 0, 50); // Check every 50ms
					}
					ControlMotor(i, 0);
					OSTimeDlyHMSM(0, 0, 0, 250); // Wait 1s for levels to stabilize, then pour again
				}
			}
		}
	}

	OSSemPost(pouring_semaphore);
    OSTaskDel(OS_PRIO_SELF);
}



