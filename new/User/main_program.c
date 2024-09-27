#include "main_program.h"
#include <stdio.h>
#include "time_handle.h"

#include "esp8266.h"
#include "core_json.h"

#include "usart.h"



#include "stm32f10x.h"
#include "key.h"
#include "led.h"
#include "timer.h"
#include "DCmotor.h"
#include "pwm.h"
#include "24l01.h"
#include "spi.h"
#include "usart.h"
#include "mpu6050.h"
#include "delay.h"	
#include "sys.h"
#include <stdio.h>

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
void CarForward(u16 SpeedA,u16 SpeedB,u16 SpeedC,u16 SpeedD);
void CarBack(u16 speed);
void CarLeft(u16 speed);
void CarRight(u16 speed);
void CarStop();
u16 PID(float kp,float ki,s16 traget , s16 previous);
	
u8 flag_scan,flag_flash,flag_work;
u16 timer_scan;
u16 speed[4];
s16 previous_yaw;
s16 present_yaw;
s16 Difference_yaw;
float pitch,roll,yaw; 		//欧拉角


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
extern uint16_t index_led;
extern uint16_t index_dht11;
extern uint16_t index_send_msg;
extern uint16_t index_aodo;
extern uint16_t index_light;
extern uint16_t index_k210;
//extern uint8_t Rx_Data[5];
extern uint8_t Rx_Data;
extern uint8_t index_motor;

/*
*************************************
函数声明
*************************************
*/

/*
*************************************
变量定义
*************************************
*/
uint8_t led_status =0;
//初始化温湿度
uint8_t temp_value=0;
uint8_t humi_value=0;
uint16_t aodo_value=0;
uint16_t light_value=0;
uint8_t k210_value=0;
uint8_t motor_value=0;

/*
*************************************
函数定义
*************************************
*/

/**
  * @brief          初始化函数,相当于Arduino的setup()函数,只在初始的时候执行一次
  * @param[in]      none
  * @retval         none
  */
void user_init_program(void)
{
    esp8266_init();
    
    time_slot_start();
	u8 tx_buf[33];
	u8 flag_1;
	u8 command[18];
	u16 len;
	u16 pwm_val;
	u8 i;
	u16 count=0;


	//TIM1_PWM_Init(899,0);
	TIM4_PWM_Init(899,0);	
	dc_Init();

	//////////////////////////////////////////////
//	LED_Init();//PD2
	KEY_Init();//PC5 PA0|15
	TIM3_Init(999,7199);//100ms Interrupt
	USART2_Init(115200);//PA2|3
	delay_init();	
  //	
	LED1_ON;
  NRF24L01_Init();	
	while(NRF24L01_Check());		
	
	//NRF24L01_RX_Mode();	
	NRF24L01_TX_Mode();
	
	MPU_Init();	
	while(mpu_dmp_init());
	LED1_OFF;
	
//	
//	speed[0]=750;
//	speed[1]=750;
//	speed[2]=750;
//	speed[3]=750;
  
}
/**
  * @brief          初始化函数,相当于Arduino的loop()函数,一直执行该函数
  * @param[in]      none
  * @retval         none
  */
void user_main_program(void)
{
	
	if(esp8266_receive_msg()!=1)
  {
      
  }
  
  
   

	
	
//	if(index_k210==1)
//	{
//		index_k210=0;
//	 	k210_value=Rx_Data[5];
//		printf("data=%d\r\n",k210_value);
//		
//	}
  if(index_send_msg==1)
  {
			index_send_msg=0;
      if(esp8266_send_msg()==0)
      {
          //printf("Success!");
      }
   
      //发送失败给出提示
      else
      {
          printf("msg send error\r\n");
      }
          
     
  }
  
  if(flag_scan)//100ms中断标记
		{
			flag_scan=0;	
			/////////////////////////////////////////////////////////////////////////
			if(KEY0_Scan())//按键接受数据处理
			{
				
				LED1_ON;
				MOTOR_A_RUN(1, 300);
				MOTOR_B_RUN(2, 300);
				//CarForward(speed[0],speed[1],speed[2],speed[3]);
				flag_work=1;
			}
			else if(KEY1_Scan())
			{
				LED1_OFF;
				MOTOR_A_RUN(0, 200);
				MOTOR_B_RUN(0, 200);
			}
			/////////////////////////////////////////////////////////////////////////
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
			{				
				present_yaw=(int)yaw*100;
				present_yaw=present_yaw/100;
				//printf("%d,\r\n",present_yaw);			
				//Difference_yaw=present_yaw-previous_yaw;
			}	
			///////////////////////////////////////////////////////////////////////// 
			if(flag_work==1)
			{
				count++;
				if(count==2)
				{
					count=0;
					MOTOR_A_RUN(1, 200);
					MOTOR_B_RUN(2, 200);
					flag_work=2;
					previous_yaw=(int)(yaw);
				}
				
			}
			
			if(flag_work==2)
			{					
				count++;
				pwm_val=PID(5,0.1,previous_yaw , present_yaw);
				MOTOR_A_RUN(1, pwm_val);
			  sprintf(tx_buf, "%d,%d,%d,%d\r\n", count,previous_yaw,present_yaw,pwm_val);
				printf(tx_buf);

				
				
				if(NRF24L01_TxPacket(tx_buf)==TX_OK)
				{
				}		
				if(count==200)
				{
					count=0;
					flag_work=0;
					LED1_OFF;
					MOTOR_A_RUN(0, 200);
					MOTOR_B_RUN(0, 200);
				}
			}

			if(NRF24L01_RxPacket(tx_buf)==0)//无线模块 接受数据处理
			{
				flag_flash=10; 
				if((tx_buf[0]=='q')&&(tx_buf[1]=='i'))//turn ‘left’
				{
					LED1_ON;
					MOTOR_A_RUN(1, 400);
				  MOTOR_B_RUN(2, 400);
				}
				else if((tx_buf[0]=='h')&&(tx_buf[1]=='o'))//turn ‘right’
				{
					MOTOR_A_RUN(2, 400);
				  MOTOR_B_RUN(1, 400);
				}
				else if((tx_buf[0]=='s')&&(tx_buf[1]=='t'))//stop
				{
					LED1_OFF;
					MOTOR_A_RUN(0, 0);
				  MOTOR_B_RUN(0, 0);
				}
				else if((tx_buf[0]=='f')&&(tx_buf[1]=='o'))//forward
				{
					
				}
				else if((tx_buf[0]=='b')&&(tx_buf[1]=='a'))//back
				{
					
				}
			}
			
		}
  
 
}




u16 PID(float kp,float ki,s16 traget , s16 previous)
{
	
	u16 pwm_val1;
	s16 e;
	static s16 E;

	e=traget-previous;
	E=E+e;
	if(E>100)E=100;
	if(E<-100)E=-100;
	pwm_val1=kp*(e)+ki*(E+e)+200;
	if(pwm_val1>250)pwm_val1=250;
	if(pwm_val1<150)pwm_val1=150;
	  
	return pwm_val1;
}




void CarForward(u16 SpeedA,u16 SpeedB,u16 SpeedC,u16 SpeedD)
{
	MOTOR_A_RUN(0,SpeedA);
	MOTOR_B_RUN(0,SpeedB);

	
	MOTOR_A_RUN(1, SpeedA);
	MOTOR_B_RUN(1, SpeedB);

}

void CarBack(u16 speed)
{
	MOTOR_A_RUN(0,899);
	MOTOR_B_RUN(0,899);

	
	MOTOR_A_RUN(2, 899);
	MOTOR_B_RUN(2, 899);

}

void CarLeft(u16 speed)
{
	MOTOR_A_RUN(0,speed);
	MOTOR_B_RUN(0,speed);

	
	MOTOR_A_RUN(1, speed);
	MOTOR_B_RUN(2, speed);
	
}

void CarRight(u16 speed)
{
	MOTOR_A_RUN(0,speed);
	MOTOR_B_RUN(0,speed);

	
	MOTOR_A_RUN(2, speed);
	MOTOR_B_RUN(1, speed);

}

void CarStop()
{
	MOTOR_A_RUN(0,899);
	MOTOR_B_RUN(0,899);

}
