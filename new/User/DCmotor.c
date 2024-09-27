#include "DCmotor.h"
#include "pwm.h"


void dc_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;            
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15|GPIO_Pin_0|GPIO_Pin_1;			
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
 
 //GPIO_ResetBits(GPIOB,GPIO_Pin_4);				
 //GPIO_SetBits(GPIOB,GPIO_Pin_2);				
 
}


//status =0 停止
//status =1 正转
//status =2 反转
//status =3 制动

void MOTOR_A_RUN(u8 status, u16 speed)
{ 
	if(status==0)//status =0 停止
	{
		AIN2_L;
		AIN1_L;
		STBY_H;
		TIM_SetCompare1(TIM4,899);
		
	}
	else if(status==1)//status =1 正转
	{
		AIN2_L;
		AIN1_H;
		STBY_H;
		if(speed>899)speed=899;
		TIM_SetCompare1(TIM4,speed);
	}
	else if(status==2)//status =2 反转
	{
		AIN2_H;
		AIN1_L;
		STBY_H;
		if(speed>899)speed=899;
		TIM_SetCompare1(TIM4,speed);
	}
	else
	{
		AIN2_H;
		AIN1_H;
		STBY_H;
		TIM_SetCompare1(TIM4,899);
	}
}


void MOTOR_B_RUN(u8 status, u16 speed)
{ 
	if(status==0)//status =0 停止
	{
		BIN2_L;
		BIN1_L;
		STBY_H;
		TIM_SetCompare2(TIM4,899);
		
	}
	else if(status==1)//status =1 正转
	{
		BIN2_L;
		BIN1_H;
		STBY_H;
		if(speed>899)speed=899;
		TIM_SetCompare2(TIM4,speed);
	}
	else if(status==2)//status =2 反转
	{
		BIN2_H;
		BIN1_L;
		STBY_H;
		if(speed>899)speed=899;
		TIM_SetCompare2(TIM4,speed);
	}
	else
	{
		BIN2_H;
		BIN1_H;
		STBY_H;
		TIM_SetCompare2(TIM4,899);
	}
}



