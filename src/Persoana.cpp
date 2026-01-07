#include "Persoana.h"

float operator+(const Client& c, float bonus)
{
    return c.getBuget() + bonus;
}