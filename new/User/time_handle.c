#include "time_handle.h"
#include "main.h"
#include "tim.h"
#include <stdio.h>

/*
*************************************
宏定义
*************************************
*/
/*
*************************************
宏定义
*************************************
*/
/*
*************************************
变量声明
*************************************
*/
/*
*************************************
变量定义
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
  * @brief          定时器2中断服务函数,10ms一次中断
  * @param[in]      htim:定时器
  * @retval         none
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	
{
    if (htim->Instance == htim3.Instance)
    {
        //采用的定时器2是10ms
        index_10ms++;  
			//0.1s    
			if(index_10ms%10==0)
			{
				index_motor=1;
			}
			//判断有没有到1s（100ms）
			if(index_10ms%100==0)
			{
				index_Latitude=1;
				index_Longitude=1;//等于1时执行相关代码
				index_rocker=1;
				
				index_k210=1;
			}
			
			
			//每5s发送一次信息到阿里云
			if(index_10ms>=500)
			{
				index_send_msg=1;
				index_10ms=0;
					
			}
    }
}
/**
  * @brief          任务轮询时间片,开启定时器2
  * @param[in]      none
  * @retval         none
  */
void time_slot_start(void)
{
  HAL_TIM_Base_Start_IT(&htim3);	//打开定时器2中断
}

	


