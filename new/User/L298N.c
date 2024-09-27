#include "main.h"
#include "L298N.h"


//承接板
void IN1(void)
{
     HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_SET);

     HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin,GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin,GPIO_PIN_SET);
     HAL_Delay(2000);


}

////履带

//void IN2(void)
//{
//    HAL_GPIO_WritePin(IN2_1_GPIO_Port,IN2_1_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN2_2_GPIO_Port,IN2_2_Pin,GPIO_PIN_SET);

//    HAL_GPIO_WritePin(IN2_3_GPIO_Port,IN2_3_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN2_4_GPIO_Port,IN2_4_Pin,GPIO_PIN_SET);

//    HAL_Delay(2000);

//}

//振动

void IN3(void)
{
    HAL_GPIO_WritePin(IN3_1_GPIO_Port,IN3_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_2_GPIO_Port,IN3_2_Pin,GPIO_PIN_SET);

    HAL_Delay(2000);


}


