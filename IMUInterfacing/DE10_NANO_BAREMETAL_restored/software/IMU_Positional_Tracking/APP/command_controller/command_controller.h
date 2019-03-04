#ifndef CMD_CONTROL_H
#define CMD_CONTROL_H
#include "../models/models.h"
#include "../HWLIBS/alt_i2c.h"
#include <stdbool.h>


typedef enum dispensing_status
{
    DISPENSING,
    ACCEPTING
} dispensing_status;

typedef enum command_t
{
    READ_LEVELS,
    DISPENSE_REQUEST,
    DISPENSE
} command_t;

typedef struct command_controller command_controller;
struct command_controller
{
    dispensing_status state; //Status of the controller
    void (*dispense)(command_controller *, recipe *);
    void (*command_handler)(command_controller *, command_t);
    recipe * current_recipe;
    ALT_I2C_DEV_t command_i2c;
};

command_controller * initialize_cmd_ctrl(void);

//Task prototype for dispensing
//Takes a command_controller pointer
void  DispensingTask (void *p_arg);

void dispense(command_controller * controller, recipe * my_recipe);

void command_handler(command_controller * controller, command_t command);

void read_levels(void);

void get_recipe(recipe * my_recipe);

#endif //__CMD_CONTROL_H
