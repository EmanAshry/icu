#include "SwICU.h"

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
    timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_256,0x00,0x00,T0_POLLING);
	Current_Edge = SwICU_EdgeRisiging;

    switch(a_en_inputCaptureEdge)
    {
        case SwICU_EdgeRisiging:
            CLEARBITS(SREG,0x80);                              // Disable interrupts by clearing I-bit
            gpioPinDirection(GPIOD,BIT2,INPUT); // Configure INT0/PD2 as input pin
            SETBITS(MCUCR,0x03);                // Trigger INT0 with the raising edge
            SETBITS(SREG,0x80);                              // Enable interrupts by setting I-bit
            break;

        case SwICU_EdgeFalling:
            CLEARBITS(SREG,0x80);                              // Disable interrupts by clearing I-bit
            gpioPinDirection(GPIOD,BIT2,INPUT); // Configure INT0/PD2 as input pin
            SETBITS(MCUCR,0x02);                // Trigger INT0 with the falling edge
            SETBITS(SREG,0x80);                              // Enable interrupts by setting I-bit
            break;
    }
}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge)
{
    switch(a_en_inputCaptureEdgeedge)
    {
        case SwICU_EdgeRisiging:
            SETBITS(MCUCR,0x03);                // Trigger INT0 with the raising edge
            break;

    case SwICU_EdgeFalling:
            SETBITS(MCUCR,0x02);                // Trigger INT0 with the falling edge
            break;
    }
}
void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
    *a_pu8_capt = timer0Read();
}
void SwICU_Stop(void)
{
    CLEARBITS(GICR,0x40);                // Enable external interrupt pin INT0
}
void SwICU_Start(void)
{
    SETBITS(GICR,0x40);                 // Enable external interrupt pin INT0
}
