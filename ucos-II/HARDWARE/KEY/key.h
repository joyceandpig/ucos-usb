#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)


typedef struct key
{
	u16 PreDownKey;//上次检测到的按键
	u8 KeyState;//按键状态
	u16 SameKeyCntr;//同一个按键检测到按下的次数
	u16 CurKey;//当前检测到的按键，用于处理长按键情况
	u8 DoubleClickSpaceTime;
	u8 DoubleClickSure;
	
	u8 (*KeyDownCallBack)(u16,u16);//按键确认按下时的回调函数
	void (*KeyUpCallBack)(u16);//按键松开的回调函数
}_KEY_INFO;
void DitherlessKey(_KEY_INFO* p_info);//消抖的处理函数
 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数	
u8 KEY_Scan1(u8 mode);
#endif
