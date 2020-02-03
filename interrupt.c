/*
 * interrupt.c
 *
 *  Author: Ema
 */ 

#include "interrupt.h"

void Enable_Interrupt(void)
{
	SREG |= (1<<7);
}


void Disable_Interrupt(void)
{
	SREG &= ~(1<<7);
}