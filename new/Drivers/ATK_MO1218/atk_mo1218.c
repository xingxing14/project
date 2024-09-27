/**
 ****************************************************************************************************
 * @file        atk_mo1218.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MO1218模块驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./BSP/ATK_MO1218/atk_mo1218.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include <math.h>

/**
 * @brief       ATK-MO1218初始化
 * @param       baudrate: ATK-MO1218 UART通讯波特率
 * @retval      ATK_MO1218_EOK  : ATK-MO1218初始化成功
 *              ATK_MO1218_ERROR: ATK-MO1218初始化失败
 */
uint8_t atk_mo1218_init(uint32_t baudrate)
{
    uint8_t ret;
    atk_mo1218_sw_version_t version;
   
    atk_mo1218_uart_init(baudrate);
    ret = atk_mo1218_get_sw_version(&version);
    if (ret != ATK_MO1218_EOK)
    {
        return ATK_MO1218_ERROR;
    }
    
    return ATK_MO1218_EOK;
}

/**
 * @brief       获取并更新ATK-MO1218模块数据
 * @param       utc                  : UTC时间
 *              position             : 位置信息（经纬度扩大100000倍）
 *              altitude             : 海拔高度（扩大10倍），单位：米
 *              speed                : 地面速度（扩大10倍），单位：千米/时
 *              fix_info             : 定位信息
 *              gps_satellite_info   : 可见GPS卫星信息
 *              beidou_satellite_info: 可见北斗卫星信息
 *              timeout              : 等待超时时间，单位：1毫秒
 * @retval      ATK_MO1218_EOK     : 获取并更新ATK-MO1218模块数据成功
 *              ATK_MO1218_EINVAL  : 函数参数错误
 *              ATK_MO1218_ETIMEOUT: 等待超时
 */
uint8_t atk_mo1218_update(atk_mo1218_time_t *utc, atk_mo1218_position_t *position, int16_t *altitude, uint16_t *speed, atk_mo1218_fix_info_t *fix_info, atk_mo1218_visible_satellite_info_t *gps_satellite_info, atk_mo1218_visible_satellite_info_t *beidou_satellite_info, uint32_t timeout)
{
    uint8_t ret;
    uint8_t *buf;
    uint8_t *nmea;
    struct
    {
        atk_mo1218_nmea_gga_msg_t msg;
        uint8_t done;
    } gngga;
    struct
    {
        atk_mo1218_nmea_gsa_msg_t msg;
        uint8_t done;
    } gngsa;
    struct
    {
        atk_mo1218_nmea_gsv_msg_t msg;
        uint8_t done;
    } gpgsv;
    struct
    {
        atk_mo1218_nmea_gsv_msg_t msg;
        uint8_t done;
    } bdgsv;
    struct
    {
        atk_mo1218_nmea_rmc_msg_t msg;
        uint8_t done;
    } gnrmc;
    struct
    {
        atk_mo1218_nmea_vtg_msg_t msg;
        uint8_t done;
    } gnvtg;
    uint8_t satellite_index;
    
    if ((utc == NULL) && (position == NULL) && (altitude == NULL) && (speed == NULL) && (fix_info == NULL) && (gps_satellite_info == NULL) && (beidou_satellite_info == NULL))
    {
        return ATK_MO1218_EINVAL;
    }
    
    gngga.done = 0;
    gngsa.done = 0;
    gpgsv.done = 0;
    bdgsv.done = 0;
    gnrmc.done = 0;
    gnvtg.done = 0;
    
    atk_mo1218_uart_rx_restart();
    while (timeout > 0)
    {
        buf = atk_mo1218_uart_rx_get_frame();
        if (buf != NULL)
        {
            /* GNGGA */
            if (((altitude != NULL) || (fix_info != NULL)) && (gngga.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_GNGGA, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    ret = atk_mo1218_decode_nmea_xxgga(nmea, &gngga.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        gngga.done = ~0;
                        if (altitude != NULL)
                        {
                            *altitude = gngga.msg.altitude;
                        }
                        if (fix_info != NULL)
                        {
                            fix_info->quality = gngga.msg.gps_quality;
                            fix_info->satellite_num = gngga.msg.satellite_num;
                        }
                    }
                }
            }
            else
            {
                gngga.done = ~0;
            }
            
            /* GNGSA */
            if ((fix_info != NULL) && (gngsa.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_GNGSA, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    ret = atk_mo1218_decode_nmea_xxgsa(nmea, &gngsa.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        gngsa.done = ~0;
                        fix_info->type = gngsa.msg.type;
                        for (satellite_index=0; satellite_index<12; satellite_index++)
                        {
                            fix_info->satellite_id[satellite_index] = gngsa.msg.satellite_id[satellite_index];
                        }
                        fix_info->pdop = gngsa.msg.pdop;
                        fix_info->hdop = gngsa.msg.hdop;
                        fix_info->vdop = gngsa.msg.vdop;
                    }
                }
            }
            else
            {
                gngsa.done = ~0;
            }
            
            /* GPGSV */
            if ((gps_satellite_info != NULL) && (gpgsv.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_GPGSV, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    ret = atk_mo1218_decode_nmea_xxgsv(nmea, &gpgsv.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        gpgsv.done = ~0;
                        gps_satellite_info->satellite_num = gpgsv.msg.satellite_view;
                        for (satellite_index=0; satellite_index<gpgsv.msg.satellite_view; satellite_index++)
                        {
                            gps_satellite_info->satellite_info[satellite_index].satellite_id = gpgsv.msg.satellite_info[satellite_index].satellite_id;
                            gps_satellite_info->satellite_info[satellite_index].elevation = gpgsv.msg.satellite_info[satellite_index].elevation;
                            gps_satellite_info->satellite_info[satellite_index].azimuth = gpgsv.msg.satellite_info[satellite_index].azimuth;
                            gps_satellite_info->satellite_info[satellite_index].snr = gpgsv.msg.satellite_info[satellite_index].snr;
                        }
                    }
                }
            }
            else
            {
                gpgsv.done = ~0;
            }
            
            /* BDGSV */
            if ((beidou_satellite_info != NULL) && (bdgsv.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_BDGSV, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    ret = atk_mo1218_decode_nmea_xxgsv(nmea, &bdgsv.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        bdgsv.done = ~0;
                        beidou_satellite_info->satellite_num = bdgsv.msg.satellite_view;
                        for (satellite_index=0; satellite_index<bdgsv.msg.satellite_view; satellite_index++)
                        {
                            beidou_satellite_info->satellite_info[satellite_index].satellite_id = bdgsv.msg.satellite_info[satellite_index].satellite_id;
                            beidou_satellite_info->satellite_info[satellite_index].elevation = bdgsv.msg.satellite_info[satellite_index].elevation;
                            beidou_satellite_info->satellite_info[satellite_index].azimuth = bdgsv.msg.satellite_info[satellite_index].azimuth;
                            beidou_satellite_info->satellite_info[satellite_index].snr = bdgsv.msg.satellite_info[satellite_index].snr;
                        }
                    }
                }
            }
            else
            {
                bdgsv.done = ~0;
            }
            
            /* GNRMC */
            if (((utc != NULL) || (position != NULL)) && (gnrmc.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_GNRMC, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    ret = atk_mo1218_decode_nmea_xxrmc(nmea, &gnrmc.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        gnrmc.done = ~0;
                        if (utc != NULL)
                        {
                            utc->year = gnrmc.msg.utc_date.year;
                            utc->month = gnrmc.msg.utc_date.month;
                            utc->day = gnrmc.msg.utc_date.day;
                            utc->hour = gnrmc.msg.utc_time.hour;
                            utc->minute = gnrmc.msg.utc_time.minute;
                            utc->second = gnrmc.msg.utc_time.second;
                            utc->millisecond = gnrmc.msg.utc_time.millisecond;
                        }
                        if (position != NULL)
                        {
                            position->latitude.degree = gnrmc.msg.latitude.degree;
                            position->latitude.indicator = gnrmc.msg.latitude.indicator;
                            position->longitude.degree = gnrmc.msg.longitude.degree;
                            position->longitude.indicator = gnrmc.msg.longitude.indicator;
                        }
                    }
                }
            }
            else
            {
                gnrmc.done = ~0;
            }
            
            /* GNVTG */
            if ((speed != NULL) && (gnvtg.done == 0))
            {
                ret = atk_mo1218_get_nmea_msg_from_buf(buf, ATK_MO1218_NMEA_MSG_GNVTG, 0, &nmea);
                if (ret == ATK_MO1218_EOK)
                {
                    gnvtg.done = ~0;
                    ret = atk_mo1218_decode_nmea_xxvtg(nmea, &gnvtg.msg);
                    if (ret == ATK_MO1218_EOK)
                    {
                        *speed = gnvtg.msg.speed_kph;
                    }
                }
            }
            else
            {
                gnvtg.done = ~0;
            }
        }
        
        if ((gngga.done != 0) && (gngsa.done != 0) && (gpgsv.done != 0) && (bdgsv.done != 0) && (gnrmc.done != 0) && (gnvtg.done != 0))
        {
            return ATK_MO1218_EOK;
        }
        
        timeout--;
        delay_ms(1);
    }
    
    return ATK_MO1218_ETIMEOUT;
}


void GeodeticToCartesian(double longitude,double latitude,double temp[])
{

	double b;//纬度度数
	double L;//经度度数
	double L0;//中央经线度数
	double L1;//L - L0
	double t;//tanB
	double m;//ltanB
	double N;//卯酉圈曲率半径
	double q2;
	double X;// 高斯平面纵坐标
	double Y;// 高斯平面横坐标
	double s;// 赤道至纬度B的经线弧长
	double f; // 参考椭球体扁率
	double e2;// 椭球第一偏心率
	double a; // 参考椭球体长半轴
	//
	double a1;
	double a2;
	double a3;
	double a4;
	double 	 b1;
	double	 b2;
	double	 b3;
	double	 b4;
	double	c0;
	double	c1;
	double	c2;
	double	c3;
	//
	int Datum, prjno, zonewide;
	double IPI;
	//
	Datum = 84;// 投影基准面类型：北京54基准面为54，西安80基准面为80，WGS84基准面为84
	prjno = 0;// 投影带号
	zonewide = 3;
	IPI = 0.0174532925199433333333; // 3.1415926535898/180.0
	b = latitude; //纬度
	L = longitude;//经度
			
	if (zonewide == 6)
	{
		prjno = trunc(L / zonewide) + 1;
		L0 = prjno * zonewide - 3;
	}
	else
	{
		prjno = trunc((L - 1.5) / 3) + 1;
		L0 = prjno * 3;
	}
	

	if (Datum == 54)
	{
		a = 6378245;
		f = 1 / 298.3;
	}
	else if (Datum == 84)
	{
		a = 6378137;
		f = 1 / 298.257223563;
	}
	//
	L0 = L0 * IPI;
	L = L * IPI;
	b = b * IPI;
 
	e2 = 2 * f - f * f; // (a*a-b*b)/(a*a);
	L1 = L - L0;
	t = tan(b);
	m = L1 * cos(b);
	N = a / sqrt(1 - e2 * sin(b) * sin(b));
	q2 = e2 / (1 - e2) * cos(b) * cos(b);
	a1 = 1 + 3 / 4 * e2 + 45 / 64 * e2 * e2 + 175 / 256 * e2 * e2 * e2 + 11025 /
		16384 * e2 * e2 * e2 * e2 + 43659 / 65536 * e2 * e2 * e2 * e2 * e2;
	a2 = 3 / 4 * e2 + 15 / 16 * e2 * e2 + 525 / 512 * e2 * e2 * e2 + 2205 /
		2048 * e2 * e2 * e2 * e2 + 72765 / 65536 * e2 * e2 * e2 * e2 * e2;
	a3 = 15 / 64 * e2 * e2 + 105 / 256 * e2 * e2 * e2 + 2205 / 4096 * e2 * e2 *
		e2 * e2 + 10359 / 16384 * e2 * e2 * e2 * e2 * e2;
	a4 = 35 / 512 * e2 * e2 * e2 + 315 / 2048 * e2 * e2 * e2 * e2 + 31185 /
		13072 * e2 * e2 * e2 * e2 * e2;
	b1 = a1 * a * (1 - e2);
	b2 = -1 / 2 * a2 * a * (1 - e2);
	b3 = 1 / 4 * a3 * a * (1 - e2);
	b4 = -1 / 6 * a4 * a * (1 - e2);
	c0 = b1;
	c1 = 2 * b2 + 4 * b3 + 6 * b4;
	c2 = -(8 * b3 + 32 * b4);
	c3 = 32 * b4;
	s = c0 * b + cos(b) * (c1 * sin(b) + c2 * sin(b) * sin(b) * sin(b) + c3 * sin
		(b) * sin(b) * sin(b) * sin(b) * sin(b));
	X = s + 1 / 2 * N * t * m * m + 1 / 24 * (5 - t * t + 9 * q2 + 4 * q2 * q2)
		* N * t * m * m * m * m + 1 / 720 * (61 - 58 * t * t + t * t * t * t)
		* N * t * m * m * m * m * m * m;
	Y = N * m + 1 / 6 * (1 - t * t + q2) * N * m * m * m + 1 / 120 *
		(5 - 18 * t * t + t * t * t * t - 14 * q2 - 58 * q2 * t * t)
		* N * m * m * m * m * m;
	Y = Y + 1000000 * prjno + 500000;
	temp[0] = X;
	temp[1] = Y;
	
	
}

double home_x,home_y;
double my_x,my_y;

gps_info_struct  gps_tau1201;
uint8_t    gps_tau1201_flag;

void GET_POSI(double longitude,double latitude,POSI_ST* posi){
	double temp[2];
//	printf("lo=%lf\r\n",gps_tau1201.longitude);
//	printf("lo=%lf\r\n",gps_tau1201.latitude);
	GeodeticToCartesian(longitude,latitude,temp);
//			printf("12123\r\n");
//			printf("tmp=%lf\r\n",temp[1]);
//			printf("home=%lf\r\n",home_lo);
	posi->x = temp[1] - home_lo;
	posi->y = temp[0] - home_la;
	
//		printf("12344555\r\n");

}
void GET_MY_POSI(POSI_ST* posi){

	GET_POSI(gps_tau1201.longitude,gps_tau1201.latitude,posi);
}
