#include "time_handle.h"
#include "main.h"
#include "tim.h"
#include <stdio.h>

/*
*************************************
�궨��
*************************************
*/
/*
*************************************
�궨��
*************************************
*/
/*
*************************************
��������
*************************************
*/
/*
*************************************
��������
*************************************
*/
static uint16_t index_10ms = 0;
uint16_t index_Latitude = 0;
uint16_t index_Longitude = 0;
uint16_t index_send_msg=0;
uint16_t index_rocker = 0;

uint16_t index_k210 = 0;
uint16_t index_motor = 0;


/**
  * @brief          ��ʱ��2�жϷ�����,10msһ���ж�
  * @param[in]      htim:��ʱ��
  * @retval         none
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	
{
    if (htim->Instance == htim3.Instance)
    {
        //���õĶ�ʱ��2��10ms
        index_10ms++;  
			//0.1s    
			if(index_10ms%10==0)
			{
				index_motor=1;
			}
			//�ж���û�е�1s��100ms��
			if(index_10ms%100==0)
			{
				index_Latitude=1;
				index_Longitude=1;//����1ʱִ����ش���
				index_rocker=1;
				
				index_k210=1;
			}
			
			
			//ÿ5s����һ����Ϣ��������
			if(index_10ms>=500)
			{
				index_send_msg=1;
				index_10ms=0;
					
			}
    }
}
/**
  * @brief          ������ѯʱ��Ƭ,������ʱ��2
  * @param[in]      none
  * @retval         none
  */
void time_slot_start(void)
{
  HAL_TIM_Base_Start_IT(&htim3);	//�򿪶�ʱ��2�ж�
}

	


