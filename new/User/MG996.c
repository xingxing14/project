#include "MG996.h"
//#include "main.h"
#include "tim.h"


//0状态测试

//void test0()
//{
////1号舵机90度状态
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,500-1);
//	HAL_Delay(1000);
//	//2号舵机90度
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,500-1);
//	HAL_Delay(1000);
//	
//	//3号舵机90度一直保持（提供力）
//  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,500-1);
//	
//	//4号舵机90度
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,500-1);
//	HAL_Delay(1000);
//	
//	//5号舵机90度一直保持（提供力）
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,500-1);
//	
//	
//	//夹子合拢|6号舵机0度
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,500-1);
//	HAL_Delay(1000);
//}


//初始化状态
void inital_mg()
{
	//1号舵机90度状态
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,333);
	HAL_Delay(1000);
	//2号舵机90度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,800);
	HAL_Delay(1000);
	
	//3号舵机90度一直保持（提供力）
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,888);
	
	//4号舵机90度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1500-1);
	HAL_Delay(1000);
	
	//5号舵机90度一直保持（提供力）
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	
	
	//夹子合拢|6号舵机0度
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,2500-1);
	HAL_Delay(1000);

	
}
//机械臂动作组

void main_program()
{
	
	//夹取前
	
	//1号舵机
	//只在停到树前，向右旋转90度|总180度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1332);
	HAL_Delay(3000);

	//2号舵机
	//旋转30度|总120度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,1132);
	HAL_Delay(500);
	
	//3/4不控制？被2号带动？
	//3号舵机
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,1500-1);
	HAL_Delay(500);

	//4号舵机
	//夹子平行树干|总150度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2000);
	HAL_Delay(500);

	
	//5号舵机
	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	

	//6号舵机
	//夹子张开|总90度
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,500-1);
	HAL_Delay(2000);
	
	
	
	// HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
// HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_SET);
	//夹取后
	
	//1号舵机90度状态
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,333);
	HAL_Delay(3000);
	//2号舵机90度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,1132);
	HAL_Delay(500);
	
	//3号舵机90度一直保持（提供力）
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,1200);
    HAL_Delay(500);
	
	//4号舵机90度
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1500-1);
	HAL_Delay(500);
	
	//5号舵机90度一直保持（提供力）
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	
	
	//夹子合拢|6号舵机0度
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,2500-1);
	HAL_Delay(500);

	HAL_Delay(2000);
	
}
