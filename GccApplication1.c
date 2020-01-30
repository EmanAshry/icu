#include <stdio.h>
#include <stdlib.h>
#include "SwICU.h"

ISR(INT0_vect)
{
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
}

int main()
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	Led_Off(LED_0);
	Led_Off(LED_1);
	Led_Off(LED_2);
	Led_Off(LED_3);

	gpioPortDirection(GPIOB,OUTPUT);
	gpioPinDirection(GPIOB,BIT2,INPUT);

	uint8_t Distance=0;

	SwICU_Init(SwICU_EdgeRisiging);
	SwICU_Start();

	while(1)
	{
		gpioPinWrite(GPIOB,BIT1,1);
		timer0DelayMs(1);
		gpioPinWrite(GPIOB,BIT1,0);



		if(ISCLEAR(TIFR,0x01))
		{
			Distance = (pu8_capt*16)/58;          //DIstance in cm
		}
		else
		{
			Distance = 0;
		}

		gpioPortWrite(GPIOB,(Distance<<4));
	}
	return 0;
}
