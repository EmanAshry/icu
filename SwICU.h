/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

#include <avr/interrupt.h>
#include "timers.h"
#include "gpio.h"
#include "registers.h"
#include "led.h"

#define SETBITS(REG,MASK) REG|=(MASK)
#define CLEARBITS(REG,MASK) REG &= ~(MASK)

typedef enum EN_SwICU_Edge_t{
	SwICU_EdgeFalling = 2,
	SwICU_EdgeRisiging = 3
}EN_SwICU_Edge_t;

//volatile uint8_t  pu8_capt;
EN_SwICU_Edge_t Current_Edge;

extern EN_SwICU_Edge_t Current_Edge;
//extern volatile uint8_t  pu8_capt;

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge);
EN_SwICU_Edge_t SwICU_GetCfgEdge(void);
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge);
void SwICU_Read(volatile uint8_t * a_pu8_capt);
void SwICU_Stop(void);
void SwICU_Start(void);
void SwICU_Enable(void);
void SwICU_Disable(void);

#endif /* SWICU_H_ */
