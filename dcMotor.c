/*
 * dcMotor.c
 *
 * Created: 1/30/2020 7:26:07 PM
 *  Author: Ema
 */ 

#include "dcMotor.h"


void MotorDC_Init(En_motorType_t en_motor_number){
	
	switch(en_motor_number){
		
		case MOT_1:
		 gpioPinDirection(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,OUTPUT);
		 gpioPinDirection(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,OUTPUT);
		 gpioPinDirection(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,OUTPUT);
				break;
	    case MOT_2:
		gpioPinDirection(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,OUTPUT);
	    gpioPinDirection(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,OUTPUT);
		gpioPinDirection(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,OUTPUT);
		break;
		
		default: break;
	}
	
	
}


void MotorDC_Dir(En_motorType_t en_motor_number, En_motorDir_t en_motor_dir){
	
	
	switch(en_motor_number){
		
		case MOT_1:
		 switch(en_motor_dir){
		   case STOP:														
		 gpioPinWrite(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,0);
		 gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,0);
		 gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,0);
		 break;
						 
	      case FORWARD:
	     gpioPinWrite(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,HIGH);
	     gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
	     gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,0);
		break;
						 
     	 case BACKWARD:
	     gpioPinWrite(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,1);
		 gpioPinWrite(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,0);
		 gpioPinWrite(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,1);
		break;		 
		default: break;
		 }
		 break;
		case MOT_2:
		switch(en_motor_dir){	
	    case STOP:														
		gpioPinWrite(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,0);
		gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,0);
		gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,0);
		break;
	    case FORWARD:
	    gpioPinWrite(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,HIGH);
		gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
		gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,0);
		break;
		case BACKWARD:
	    gpioPinWrite(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,1);
		gpioPinWrite(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,0);
		gpioPinWrite(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,1);
		break;	
		default: break;
		}
		break;
	 default: break;
}

}




void MotorDC_Speed_PollingWithT0(uint8_t u8_motor_speed){
 timer0Stop();
	switch(u8_motor_speed){
		case 1:
		timer0SwPWM(20,200);
		break;
		case 2:
		timer0SwPWM(40,200);
		break;
		case 3:
		timer0SwPWM(60,200);
		break;
		case 4:
		timer0SwPWM(80,200);
		break;
	}

}

void MotorDC_Speed_HwPWM(uint8_t u8_motor_speed)
{
	switch(u8_motor_speed){
		case 1:
		HwPWMSetDuty(20,200);
		break;
		case 2:
		HwPWMSetDuty(40,200);
		break;
		case 3:
		HwPWMSetDuty(60,200);
		break;
		case 4:
		HwPWMSetDuty(80,200);
		break;
	}
}