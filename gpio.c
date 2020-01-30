/*
 * GPIO.c
 */ 


#include "std_types.h"
#include "gpio.h"
#include "registers.h"

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	switch (u8_port)
	{
	case GPIOA:
		PORTA_DIR = u8_direction;
		break;
	case GPIOB:
		PORTB_DIR = u8_direction;
		break;
	case GPIOC:
		PORTC_DIR = u8_direction;
		break;
	case GPIOD:
		PORTD_DIR = u8_direction;
		break; 
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	switch (u8_port)
	{
	case GPIOA:
		PORTA_DATA = u8_value;
		break;
	case GPIOB:
		PORTB_DATA = u8_value;
		break;
	case GPIOC:
		PORTC_DATA = u8_value;
		break;
	case GPIOD:
		PORTD_DATA = u8_value;
		break;
	}
}

void gpioPortToggle(uint8_t u8_port)
{
	switch (u8_port)
	{
		case GPIOA:
			PORTA_DATA ^= HIGH;
			break;
		case GPIOB:
			PORTB_DATA ^= HIGH;
			break;
		case GPIOC:
			PORTC_DATA ^= HIGH;
			break;
		case GPIOD:
			PORTD_DATA ^= HIGH;
			break;
	}
}

uint8_t gpioPortRead(uint8_t u8_port)
{
	uint8_t Output =0;
	
	switch (u8_port)
	{
		case GPIOA:
			Output = PORTA_PIN;
			break;
		case GPIOB:
			Output = PORTB_PIN;
			break;
		case GPIOC:
			Output = PORTC_PIN;
			break;
		case GPIOD:
			Output = PORTD_PIN;
			break;
	}
	
	return Output;
}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	switch (u8_direction)
	{
	case INPUT:
		switch (u8_port)
		{
			case GPIOA:
			PORTA_DIR &= ~u8_direction;
			break;
			case GPIOB:
			PORTB_DIR &= ~u8_direction;
			break;
			case GPIOC:
			PORTC_DIR &= ~u8_direction;
			break;
			case GPIOD:
			PORTD_DIR &= ~u8_direction;
			break;
		}
		break;
	case OUTPUT:
		switch (u8_port)
		{
			case GPIOA:
				PORTA_DIR |= u8_direction;
				break;
			case GPIOB:
				PORTB_DIR |= u8_direction;
				break;
			case GPIOC:
				PORTC_DIR |= u8_direction;
				break;
			case GPIOD:
				PORTD_DIR |= u8_direction;
				break;
		}
		break;
	}
}

void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	switch (u8_value)
	{
		case LOW:
		switch (u8_port)
		{
			case GPIOA:
				PORTA_DATA &= ~u8_pins;
				break;
			case GPIOB:
				PORTB_DATA &= ~u8_pins;
				break;
			case GPIOC:
				PORTC_DATA &= ~u8_pins;
				break;
			case GPIOD:
				PORTD_DATA &= ~u8_pins;
				break;
		}
		break;
		default:
		switch (u8_port)
		{
			case GPIOA:
			{
				PORTA_DATA &= ~u8_pins;
				u8_pins &= u8_value;
				PORTA_DATA |= u8_pins;
			}
				break;
			case GPIOB:
			{
				PORTB_DATA &= ~u8_pins;
				u8_pins &= u8_value;
				PORTB_DATA |= u8_pins;
			}
				break;
			case GPIOC:
			{
				PORTC_DATA &= ~u8_pins;
				u8_pins &= u8_value;
				PORTC_DATA |= u8_pins;
			}
				break;
			case GPIOD:
			{
				PORTD_DATA &= ~u8_pins;
				u8_pins &= u8_value;
				PORTD_DATA |= u8_pins;
			}
				break;
		}
		break;
	}
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
	switch (u8_port)
	{
		case GPIOA:
			PORTA_DATA ^= u8_pins;
			break;
		case GPIOB:
			PORTB_DATA ^= u8_pins;
			break;
		case GPIOC:
			PORTC_DATA ^= u8_pins;
			break;
		case GPIOD:
			PORTD_DATA ^= u8_pins;
			break;
	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
	uint8_t Output =0;
	
	switch (u8_port)
	{
		case GPIOA:
			Output = (PORTA_PIN&u8_pin);
			break;
		case GPIOB:
			Output = (PORTB_PIN&u8_pin);
			break;
		case GPIOC:
			Output = (PORTC_PIN&u8_pin);
			break;
		case GPIOD:
			Output = (PORTD_PIN&u8_pin);
			break;
	}
	
	return Output;
}