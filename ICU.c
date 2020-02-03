/*
 * ICU.c
 *
 * Created: 1/30/2020 4:58:25 PM
 *  Author: Ema
 */ 

#include <avr/interrupt.h>
#include <avr/delay.h>
#include "SwICU.h"
#include "HwPWM.h"
#include "dcMotor.h"

volatile uint8_t triger_Flag=0;
volatile uint8_t  pu8_capt;

ISR(INT2_vect)
{
	if(MCUCSR&(1<<6))     							//check if interrupt from rising edge
	{
		TCNT0=0;									//reset timer0 counter
		SwICU_Start();								//Start counting
		SwICU_SetCfgEdge(SwICU_EdgeFalling);		//change icu interrupt trigger to falling edge
	}
	else
	{
		SwICU_Stop();								//stop timer0
		SwICU_Read(&pu8_capt);						//read timer0 counter value
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);		// change icu interrupt trigger to rising edge
		triger_Flag =1;								// set sensor trigger flag to start distance calculation
	}
}

int main()
{
	volatile uint8_t Distance=0;
	
	/* intialaize LEDS*/
	Led_Init(LED_0);	
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	SwICU_Init(SwICU_EdgeRisiging);					//intialaize SwICU with rising edge
	

	MotorDC_Init(MOT_1);							//intialaize Motors
	MotorDC_Init(MOT_2);
	
	HwPWMInit();									//intialaize HwPWM
	
	MotorDC_Speed_HwPWM(4);							// speed 4 moves the car with speed 80%
	
	while(1)
	{	

		gpioPinWrite(GPIOA,BIT1,HIGH);				//trigger the sensor
		_delay_us(500);
		
		gpioPinWrite(GPIOA,BIT1,0);
		_delay_us(500);
		
		if(triger_Flag) 							//check if two ISR for rising and falling edged happened
		{	
					
			Distance = (pu8_capt*16)/58;			//Distance in cm
			
			triger_Flag =0;
		}
			
		
		if ((TIFR & 0x01))
		{
			gpioPinWrite(GPIOB, 0xF0, HIGH)	;		// all LEDs On
			TIFR = TIFR |0x01;						//clear over flow flag
		}else
			{
			if(Distance <= 5)
			{
				MotorDC_Dir(MOT_1,STOP);			//stop motor when distance <=5
				MotorDC_Dir(MOT_2,STOP);						
			}
			else
				{
					MotorDC_Dir(MOT_1,FORWARD);		//keep moving the motors
					MotorDC_Dir(MOT_2,FORWARD);											
				}
						
			if (Distance <16)
				{
					gpioPortWrite(GPIOB,(Distance<<4));			// print distance on LEDS
			    }
			else
				{
					gpioPinWrite(GPIOB, 0xF0, HIGH)	;			// all LEDs On 
				}
			
						
				
			}		

		_delay_ms(300);											//enough delay so LEDS don't blink
		
		
	}
	
	return 0;
}
