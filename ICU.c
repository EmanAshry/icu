/*
 * ICU.c
 *
 * Created: 1/30/2020 4:58:25 PM
 *  Author: Ema
 */ 

#include <avr/interrupt.h>
#include "SwICU.h"
#include "HwPWM.h"
#include "dcMotor.h"

volatile uint8_t triger_Flag=0;

ISR(INT2_vect)
{
	if(MCUCSR&(1<<6))     					//check if interrupt from rising edge
	{
		SwICU_Start();					//Start counting
		SwICU_SetCfgEdge(SwICU_EdgeFalling);		//change icu interrupt trigger to falling edge
	}
	else
	{
		SwICU_Read(&pu8_capt);				//read timer0 counter value
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);		// change icu interrupt trigger to rising edge
		SwICU_Stop();					//stop timer0
		triger_Flag =1;					// set sensor trigger flag to start distance calculation
	}
}

int main()
{
	/* intialaize LEDS*/
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);	

	volatile uint8_t Distance=0;
	
	SwICU_Init(SwICU_EdgeRisiging);			//intialaize SwICU with rising edge
	
	MotorDC_Init(MOT_1);				//intialaize Motors
	MotorDC_Init(MOT_2);
	
	HwPWMInit();					//intialaize HwPWM
	
	MotorDC_Speed_HwPWM(4);				// move the car with speed 80%
	
	while(1)
	{	
		if(triger_Flag) 			//check if two ISR for rising and falling edged happened  
		{
			Distance = (pu8_capt*0.544);          //Distance in cm
			
			gpioPinWrite(GPIOB,BIT1,HIGH);	      //trigger the sensor
			timer2DelayMs(1);
			gpioPinWrite(GPIOB,BIT1,0);
			
			triger_Flag=0;
		}
		
		gpioPortWrite(GPIOB,(Distance<<4));	      //show the Distance on the leds
		
	}
}
