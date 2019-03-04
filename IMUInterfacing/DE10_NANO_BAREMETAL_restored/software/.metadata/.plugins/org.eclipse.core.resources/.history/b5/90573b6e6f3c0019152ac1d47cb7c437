#include  <os.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command_controller.h"
#include "../HWLIBS/alt_i2c.h"
#include "../models/models.h"
#include "../dispensing/dispensing.h"
#include "../i2c_driver/i2c_driver.h"
#include "../adc/adc.h"
#include "../tasks.h"
#include "../basic_io.h"
#include "../UART/uart.h"
#include <string.h>

#define CMD_QUEUE_SIZE 1
#define CONTROLLER_STACK_SIZE 4096
#define DISPENSING_STACK_SIZE 4096

CPU_STK Controller_Task_Stack[CONTROLLER_STACK_SIZE];
CPU_STK Dispensing_Task_Stack[DISPENSING_STACK_SIZE];

OS_EVENT* cmd_queue;
void* cmd_msg_queue[CMD_QUEUE_SIZE];

static command_controller cmd_controller;
OS_EVENT * controller_semaphore;
OS_EVENT * pouring_semaphore;


/*
* Processes commands and launches dispensing or level reading depending on outcome
*/
void CommandProcessingTask(void *p_arg)
{
    command_t command;
    char hlep[2] = { 0 };
    command_controller * ctrl = (command_controller *)p_arg;
    while(true)
    {
        //Use I2C to read new command from the PROWF
    	UART_print("Waiting for a command!\r\n");
        read((void *)&command, sizeof(command_t)); 
        command_handler(ctrl, command);
        snprintf(hlep, 2, "%d", command);
        UART_print("Command handled!\r\n");
        UART_print(hlep);
    	//OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

void command_handler(command_controller * controller, command_t command)
{
    recipe* my_recipe = (recipe *)malloc(sizeof(recipe));
    uint8_t os_err;
    switch(command)
    {
        case READ_LEVELS:
            read_levels();
            break;
        case DISPENSE_REQUEST:
        	UART_print("Dispense request!\r\n");
        	OSSemPend(controller_semaphore, 0, &os_err);
            write((void *)&(controller->state), sizeof(dispensing_status));
            leds_set(7, controller->state);
            if(controller->state == ACCEPTING)
            {
            	UART_print("Ready to pour current request!\r\n");
            	OSSemPost(controller_semaphore);
            	get_recipe(my_recipe);
				dispense(controller, my_recipe);
            }
            else
            {
            	UART_print("Too busy to pour current request!\r\n");
            	OSSemPost(controller_semaphore);
            }
            break;
        default:
            break;
    }

}

void get_recipe(recipe * my_recipe)
{
    read((void*)my_recipe, sizeof(recipe));
}

void read_levels(void)
{
    //Read levels from the dac into this array
    uint16_t levels[3] = { 0 };
    for(int i = 0; i < 3; i++)
    {
    	levels[i] = HTONS(getCurrentVolume(i));
    }
    write((void *)&(levels[0]), sizeof(levels));
}

void dispense(command_controller * controller, recipe * my_recipe)
{
	uint8_t os_err;
    OSSemPend(controller_semaphore, 0, &os_err);
	if(controller->state == DISPENSING)
	{
		UART_print("Busy cancel pour\r\n");
        OSSemPost(controller_semaphore);
		return;
	}
	UART_print("Continue to pour\r\n");
    controller->state = DISPENSING;
    UART_print("Setting back to dispensing\r\n");
    if(controller->current_recipe != NULL)
	{
    	free(controller->current_recipe);
	}

    controller->current_recipe = my_recipe;
    OSSemPost(controller_semaphore);


    os_err = OSTaskCreateExt((void (*)(void *)) DispensingTask,   /* Create the start task.                               */
                                     (void          * ) controller,
                                     (OS_STK        * )&Dispensing_Task_Stack[CONTROLLER_STACK_SIZE - 1],
                                     (INT8U           ) DISPENSE_TASK_PRIO,
                                     (INT16U          ) DISPENSE_TASK_PRIO,  // reuse prio for ID
                                     (OS_STK        * )&Dispensing_Task_Stack[0],
                                     (INT32U          ) CONTROLLER_STACK_SIZE,
                                     (void          * )0,
                                     (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

            if (os_err != OS_ERR_NONE) {
                ; /* Handle error. */
            }
}


void DispensingTask (void *p_arg)
{
	uint8_t os_err;
	UART_print("Start dispensing task\r\n");
    //Dereference controller
    command_controller * ctrl = (command_controller *)p_arg;
    OSSemPend(controller_semaphore, 0, &os_err);
    recipe * my_recipe = ctrl->current_recipe;
    ctrl->state = DISPENSING;
    UART_print("Setting back to dispensing\r\n");
    leds_set(8, 1);
    OSSemPost(controller_semaphore);

    //Dispense liquid
	if(my_recipe->ordered)
	{
		// If they're ordered, the task will dispense each item in turn
		OrderedDispenseTaskInit(my_recipe);
	}
	else
	{
		// Otherwise start all the pumps at once
		SimultaneousDispenseTaskInit(my_recipe);
	}
    //Update liquid levels

    //Unbusy
	OSSemPend(pouring_semaphore, 0, &os_err);
	OSSemPend(controller_semaphore, 0, &os_err);
    ctrl->state = ACCEPTING;
    UART_print("Setting back to accepting\r\n");
    leds_set(8, 0);
    OSSemPost(controller_semaphore);
    OSTaskDel(OS_PRIO_SELF);
}

command_controller * initialize_cmd_ctrl()
{
	uint8_t os_err;
	controller_semaphore = OSSemCreate(1);
	pouring_semaphore = OSSemCreate(0);
	OSSemPend(controller_semaphore, 0, &os_err);
    cmd_controller.state = ACCEPTING;
    cmd_controller.dispense = &dispense;
    cmd_controller.command_handler = &command_handler;
    cmd_controller.current_recipe = NULL;
    cmd_queue = OSQCreate(cmd_msg_queue, CMD_QUEUE_SIZE);
    init_I2C2(&(cmd_controller.command_i2c));

    os_err = OSTaskCreateExt((void (*)(void *)) CommandProcessingTask,   /* Create the start task.                               */
							 (void          * ) &cmd_controller,
							 (OS_STK        * )&Controller_Task_Stack[CONTROLLER_STACK_SIZE - 1],
							 (INT8U           ) CMD_TASK_PRIO,
							 (INT16U          ) CMD_TASK_PRIO,  // reuse prio for ID
							 (OS_STK        * )&Controller_Task_Stack[0],
							 (INT32U          ) CONTROLLER_STACK_SIZE,
							 (void          * )0,
							 (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

	if (os_err != OS_ERR_NONE)
	{
		; /* Handle error. */
	}
	OSSemPost(controller_semaphore);
    return &cmd_controller;
}
