#include "SwICU.h"

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
    timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_256,0x00,0x00,T0_POLLING);    // intialize timer0
    gpioPinDirection(GPIOB,BIT1,OUTPUT);			 // Configure PB1 as outnput pin for trigger
    gpioPinDirection(GPIOB,BIT2,INPUT);		                 // Configure INT2/PB2 as input pin
    SETBITS(SREG,(1<<7));                               	 // Enable interrupts by setting I-bit

    switch(a_en_inputCaptureEdge)
    {
        case SwICU_EdgeRisiging:
	    SETBITS(GICR,(1<<5));				 // Enable external interrupt pin INT0		   
	    SETBITS(MCUCSR,(1<<6));			         // Trigger INT2 with the raising edge           
            break;

        case SwICU_EdgeFalling:
	    SETBITS(GICR,(1<<5));				 // Enable external interrupt pin INT0
	    CLEARBITS(MCUCSR,(1<<6));				 // Trigger INT0 with the falling edge
            break;
    }
}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge)
{
    switch(a_en_inputCaptureEdgeedge)
    {
        case SwICU_EdgeRisiging:
	SETBITS(MCUCSR,(1<<6));					// Trigger INT2 with the raising edge
            break;

    	case SwICU_EdgeFalling:
	CLEARBITS(MCUCSR,(1<<6));			       // Trigger INT2 with the falling edge              
            break;
    }
}

void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
    *a_pu8_capt = timer0Read();
}

void SwICU_Stop(void)
{
	timer0Stop();					      // Stop timer0
                    
}

void SwICU_Start(void)
{               
	timer0Start();				             // Start timer0
}
