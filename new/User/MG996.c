#include "MG996.h"
//#include "main.h"
#include "tim.h"


//0״̬����

//void test0()
//{
////1�Ŷ��90��״̬
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,500-1);
//	HAL_Delay(1000);
//	//2�Ŷ��90��
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,500-1);
//	HAL_Delay(1000);
//	
//	//3�Ŷ��90��һֱ���֣��ṩ����
//  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,500-1);
//	
//	//4�Ŷ��90��
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,500-1);
//	HAL_Delay(1000);
//	
//	//5�Ŷ��90��һֱ���֣��ṩ����
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,500-1);
//	
//	
//	//���Ӻ�£|6�Ŷ��0��
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,500-1);
//	HAL_Delay(1000);
//}


//��ʼ��״̬
void inital_mg()
{
	//1�Ŷ��90��״̬
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,333);
	HAL_Delay(1000);
	//2�Ŷ��90��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,800);
	HAL_Delay(1000);
	
	//3�Ŷ��90��һֱ���֣��ṩ����
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,888);
	
	//4�Ŷ��90��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1500-1);
	HAL_Delay(1000);
	
	//5�Ŷ��90��һֱ���֣��ṩ����
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	
	
	//���Ӻ�£|6�Ŷ��0��
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,2500-1);
	HAL_Delay(1000);

	
}
//��е�۶�����

void main_program()
{
	
	//��ȡǰ
	
	//1�Ŷ��
	//ֻ��ͣ����ǰ��������ת90��|��180��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1332);
	HAL_Delay(3000);

	//2�Ŷ��
	//��ת30��|��120��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,1132);
	HAL_Delay(500);
	
	//3/4�����ƣ���2�Ŵ�����
	//3�Ŷ��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,1500-1);
	HAL_Delay(500);

	//4�Ŷ��
	//����ƽ������|��150��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2000);
	HAL_Delay(500);

	
	//5�Ŷ��
	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	

	//6�Ŷ��
	//�����ſ�|��90��
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,500-1);
	HAL_Delay(2000);
	
	
	
	// HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
// HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_SET);
	//��ȡ��
	
	//1�Ŷ��90��״̬
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,333);
	HAL_Delay(3000);
	//2�Ŷ��90��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,1132);
	HAL_Delay(500);
	
	//3�Ŷ��90��һֱ���֣��ṩ����
  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,1200);
    HAL_Delay(500);
	
	//4�Ŷ��90��
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1500-1);
	HAL_Delay(500);
	
	//5�Ŷ��90��һֱ���֣��ṩ����
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1500-1);
	
	
	//���Ӻ�£|6�Ŷ��0��
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,2500-1);
	HAL_Delay(500);

	HAL_Delay(2000);
	
}
