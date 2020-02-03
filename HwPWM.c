/*
 * HwPWM.c
 *
 * Created: 1/30/2020 5:59:25 PM
 *  Author: Ema
 */ 
#include "HwPWM.h"
#include "dcMotor.h"
#include "dcMotorConfig.h"

void HwPWMInit(void)
{
	gpioPinDirection(GPIOD,BIT4,OUTPUT);
	gpioPinDirection(GPIOD,BIT5,OUTPUT);
	timer1Init(T1_FASTPWM,T1_OC1A_CLEAR,T1_PRESCALER_64,0x0000,0x0000,0x0000,0x00FF,T1_POLLING);
	timer1Init(T1_FASTPWM,T1_OC1B_CLEAR,T1_PRESCALER_64,0x0000,0x0000,0x0000,0x00FF,T1_POLLING);
}

void HwPWMSetDuty(uint8_t a_u8_duty, uint32_t a_u32_frequency)
{
	uint8_t ICR_TOP_Value = 0;
	
	ICR_TOP_Value = (a_u8_duty*255)/100;
	
	SETBITS(OCR1A,ICR_TOP_Value);
	SETBITS(OCR1B,ICR_TOP_Value);
	
	
	gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
	gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,0);
	
	gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
	gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,0);
	
	timer1Start();
}