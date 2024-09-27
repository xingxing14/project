#ifndef __ZHILIUDIANJI_H
#define __ZHILIUDIANJI_H

#include "stm32f10x.h"

void MOTOR_A_RUN(u8 status, u16 speed);
void MOTOR_B_RUN(u8 status, u16 speed);

void leftandright(u8 en,u8 dir, u8 speed);
void dc_Init(void);

#define AIN1_H  GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define AIN1_L	GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define AIN2_H	GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define AIN2_L	GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define STBY_H	GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define STBY_L	GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define BIN1_H  GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define BIN1_L	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define BIN2_H	GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define BIN2_L	GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#endif
