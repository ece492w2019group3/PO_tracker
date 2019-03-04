#ifndef MODELS_H
#define MODELS_H
#include <stdint.h>
typedef struct dispensing_ingredient
{
    int16_t amount;
    uint8_t order;
} dispensing_ingredient;

typedef struct recipe
{
	dispensing_ingredient ingredients[3];
    uint8_t ordered;
} recipe;

#endif //MODELS_H
