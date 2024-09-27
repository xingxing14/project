#include "Motor.h"
#include "main.h"
#include "tim.h"

//void Motor_Init()
//{
//	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);      //开启编码器定时器
//    __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
//	HAL_TIM_Base_Start_IT(&htim6);                       //开启10ms定时器中断
//	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);            //开启PWM
//	__HAL_TIM_SET_COUNTER(&htim1, 10000);                //编码器定时器初始值设定为10000
//	motor.loopNum = 0;                                   //溢出计数
//}


void IN2(void)
{
    HAL_GPIO_WritePin(IN2_1_GPIO_Port,IN2_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_2_GPIO_Port,IN2_2_Pin,GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,50);

    HAL_GPIO_WritePin(IN2_3_GPIO_Port,IN2_3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_4_GPIO_Port,IN2_4_Pin,GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,50);

    HAL_Delay(2000);

}