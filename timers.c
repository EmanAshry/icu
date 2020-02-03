#include "timers.h"
#include "gpio.h"


/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{
    Timer_Config.Timer_Mode = en_mode;
    Timer_Config.Timer_OC = en_OC0;
    Timer_Config.Timer_Pre = en_prescal;
    Timer_Config.Timer_Init_Value = u8_initialValue;
    Timer_Config.Timer_Comp_Value = u8_outputCompare;
    Timer_Config.Timer_Interrupt = en_interruptMask;

    CLEARBITS(TCNT0,0xFF);
    CLEARBITS(OCR0,0xFF);
    SETBITS(TCNT0,u8_initialValue);
    SETBITS(TCCR0,(en_mode|en_OC0));
    SETBITS(OCR0,u8_outputCompare);
    SETBITS(TIMSK,en_interruptMask);

}

void timer0Set(uint8_t u8_value)
{
    CLEARBITS(TCNT0,0xFF);
    SETBITS(TCNT0,u8_value);
}

uint8_t timer0Read(void)
{
    return TCNT0;
}

void timer0Start(void)
{
    SETBITS(TCCR0,Timer_Config.Timer_Pre);
}

void timer0Stop(void)
{
    CLEARBITS(TCCR0,0x07);
}

void timer0DelayMs(uint16_t u16_delay_in_ms)
{
    uint16_t counter=0;

    timer0Init(T0_COMP_MODE,T0_OC0_CLEAR,T0_PRESCALER_64,0x00,0xFA,T0_POLLING);
    timer0Start();

    SETBITS(TIFR,0x02);

    while(counter!=u16_delay_in_ms)
    {

       while(ISCLEAR(TIFR,0x02))
        {}
		SETBITS(TIFR,0x02);
        counter++;
    }

}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{

}

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
{
    Timer_Config_16bit.Timer_Mode = en_mode;
    Timer_Config_16bit.Timer_OC = en_OC;
    Timer_Config_16bit.Timer_Pre = en_prescal;
    Timer_Config_16bit.Timer_Init_Value = u16_initialValue;
    Timer_Config_16bit.Timer_OComp_A = u16_outputCompareA;
    Timer_Config_16bit.Timer_OComp_B = u16_outputCompareB;
    Timer_Config_16bit.Timer_ICU = u16_inputCapture;
    Timer_Config_16bit.Timer_Interrupt = en_interruptMask;

    CLEARBITS(TCNT1,0xFFFF);
    CLEARBITS(ICR1,0xFFFF);
    CLEARBITS(OCR1A,0xFF);
    CLEARBITS(OCR1B,0xFF);
    SETBITS(TCNT1,u16_initialValue);
    SETBITS(TCCR1,(en_mode|en_OC));
    SETBITS(OCR1AH,(Timer_Config_16bit.Timer_OComp_A<<8));
    SETBITS(OCR1AL,Timer_Config_16bit.Timer_OComp_A);
    SETBITS(OCR1BH,(Timer_Config_16bit.Timer_OComp_B<<8));
    SETBITS(OCR1BL,Timer_Config_16bit.Timer_OComp_B);
    SETBITS(ICR1,Timer_Config_16bit.Timer_ICU);
    SETBITS(TIMSK,en_interruptMask);
}

void timer1Set(uint16_t u16_value)
{
    CLEARBITS(TCNT1,0xFFFF);
    SETBITS(TCNT1,u16_value);
}

uint16_t timer1Read(void)
{
    uint16_t TCNT1_Read = TCNT1L;

    TCNT1_Read |= (TCNT1H << 8);

    return TCNT1_Read;
}

void timer1Start(void)
{
    SETBITS(TCCR1,Timer_Config_16bit.Timer_Pre);
}

void timer1Stop(void)
{
    CLEARBITS(TCCR1B,0x07);
}

void timer1DelayMs(uint16_t u16_delay_in_ms)
{
    uint16_t counter=0;
    timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1A_CLEAR,T1_PRESCALER_64,0x0000,0x00FA,0x0000,0x0000,T1_POLLING);
    timer1Start();

    SETBITS(TIFR,0x10);

    while(counter!=u16_delay_in_ms)
    {
       while(ISCLEAR(TIFR,0x10))
        {}
	SETBITS(TIFR,0x10);
        counter++;
    }

    timer1Stop();
}

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask)
{
    Timer_Config.Timer_Mode = en_mode;
    Timer_Config.Timer_OC = en_OC;
    Timer_Config.Timer_Pre = en_prescal;
    Timer_Config.Timer_Init_Value = u8_initialValue;
    Timer_Config.Timer_Comp_Value = u8_outputCompare;
    Timer_Config.Timer_Assync = u8_assynchronous;  // enternal or external clock
    Timer_Config.Timer_Interrupt = en_interruptMask;

    CLEARBITS(TCNT2,0xFF);
    CLEARBITS(OCR2,0xFF);
    SETBITS(TCNT2,u8_initialValue);
    SETBITS(TCCR2,(en_mode|en_OC));
    SETBITS(OCR2,u8_outputCompare);
    SETBITS(TIMSK,en_interruptMask);
}

void timer2Set(uint8_t u8_a_value)
{
    CLEARBITS(TCNT2,0xFF);
    SETBITS(TCNT2,u8_a_value);
}

uint8_t timer2Read(void)
{
    return TCNT2;
}

void timer2Start(void)
{
    SETBITS(TCCR2,Timer_Config.Timer_Pre);
}

void timer2Stop(void)
{
    CLEARBITS(TCCR2,0x07);
}

void timer2DelayMs(uint16_t u16_delay_in_ms)
{
    uint16_t counter=0;

    timer2Init(T2_COMP_MODE,T2_OC2_CLEAR,T2_PRESCALER_64,0x00,0xFA,0x00,T2_POLLING);
    timer2Start();

    SETBITS(TIFR,0xFA);

    while(counter!=u16_delay_in_ms)
    {

       while(ISCLEAR(TIFR,0xFA))
        {}
        counter++;
    }

    SETBITS(TIFR,0xFA);
}
