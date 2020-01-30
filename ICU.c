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
{/*
	if(Current_Edge==SwICU_EdgeRisiging)
	{
		timer0Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		Current_Edge = SwICU_EdgeFalling;
	}
	else
	{
		timer0Stop();
		SwICU_Read(&pu8_capt);
	}
	*/
	
	if(MCUCSR&(1<<6))
	{
		SwICU_Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
	}
	else
	{
		SwICU_Read(&pu8_capt);
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		SwICU_Stop();
		triger_Flag =1;
	}
}

int main()
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	//gpioPortDirection(GPIOB,OUTPUT);
	

	volatile uint8_t Distance=0;
	/*
	Led_On(LED_0);
	SwICU_Init(SwICU_EdgeRisiging);
	SwICU_Start();
	
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	
	//MotorDC_Dir(MOT_1,FORWARD);
	//MotorDC_Dir(MOT_2,FORWARD);
	HwPWMInit();
	
	Led_On(LED_1);
	
	MotorDC_Speed_HwPWM(4);
	
	timer0DelayMs(5000);
	
	MotorDC_Dir(MOT_1,STOP);
	MotorDC_Dir(MOT_2,STOP);
	
	Led_On(LED_2);
*/
	
	SwICU_Init(SwICU_EdgeRisiging);
	SwICU_Start();
	
	while(1)
	{	
		if(triger_Flag)
		{
			Distance = (pu8_capt*0.544);          //Distance in cm
			
			gpioPinWrite(GPIOB,BIT1,HIGH);
			timer2DelayMs(1);
			gpioPinWrite(GPIOB,BIT1,0);
			
			triger_Flag=0;
		}
		
		gpioPortWrite(GPIOB,(Distance<<4));
		
		Led_On(LED_1);
		
		//PORTB_DATA = (PORTB_DATA & 0x0F) | (Distance << 4);
		/*
		if(ISCLEAR(TIFR,0x01))
		{
			Distance = (pu8_capt*16)/58;          //Distance in cm
		}
		else
		{
			Distance = 15;
			SETBITS(TIFR,0x01);
		}
		
		if(Distance <= 5)
		{
			MotorDC_Dir(MOT_1,STOP);
			MotorDC_Dir(MOT_2,STOP);
		}
		
		gpioPortWrite(GPIOB,(Distance<<4));
		
		Led_On(LED_3);
		timer0DelayMs(5000);
		Led_Off(LED_3);
		*/
	}
	
	return 0;
}
