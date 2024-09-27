#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"


void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void led_adjust_light(u16 light);
void led_adjust_light2(u16 light1);
void led_adjust_light3(u16 light2);
void led_adjust_light4(u16 light3);
void led_adjust_light5(u16 light4);
void led_adjust_light6(u16 light5);
void led_adjust_light7(u16 light6);
void led_adjust_light8(u16 light7);
#endif
