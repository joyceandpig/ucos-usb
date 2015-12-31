#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//按键输入 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/06
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//按键初始化函数 
//PA0.15和PC5 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下 
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// 无按键按下
}
#define KEY_NONE 0
#define HAS_NO_KEY 0
#define HAS_KEY_DOWN 1
#define HAS_KEY_SURE 2
#define HAS_KEY_WAITUP 3
#define REENTER 1
#define NO_REENTER 2

u8 Keydowncallback(u16 key, u16 time);
void Keyupcallback(u16 key);
static _KEY_INFO key0 = {0,0,0,0,0,0,Keydowncallback,Keyupcallback};
static _KEY_INFO key1 = {0,0,0,0,0,0,Keydowncallback,Keyupcallback};
static _KEY_INFO key2 = {0,0,0,0,0,0,Keydowncallback,Keyupcallback};

void DitherlessKey(_KEY_INFO *p_info)
{
	switch(p_info->KeyState)
	{
		case HAS_NO_KEY:
			p_info->SameKeyCntr = 0;
		p_info->DoubleClickSure = 0;
			if(p_info->CurKey == 0){
				p_info->KeyState = HAS_KEY_DOWN;
			}
			if(p_info->SameKeyCntr){
						if(p_info->CurKey != p_info->PreDownKey){
				++p_info->DoubleClickSpaceTime;
			}}
			break;
		case HAS_KEY_DOWN:
			if(p_info->PreDownKey == p_info->CurKey){
				p_info->KeyState = HAS_KEY_SURE;
			}else{
				p_info->KeyState = HAS_NO_KEY;
			}
			break;
		case HAS_KEY_SURE:
			if(p_info->CurKey == p_info->PreDownKey){
				if(p_info->DoubleClickSpaceTime < 20 && p_info->DoubleClickSpaceTime > 0){
					p_info->DoubleClickSure = 1;	
				}p_info->DoubleClickSpaceTime = 0;
				p_info->KeyState = HAS_KEY_WAITUP;
				if(p_info->KeyDownCallBack){//判定函数指针是否配置函数
					if(REENTER == p_info->KeyDownCallBack(p_info->CurKey,p_info->SameKeyCntr)){
						++p_info->SameKeyCntr;
						p_info->KeyState = HAS_KEY_SURE;
					}
				}
			}else{
				p_info->KeyState = HAS_NO_KEY;
			}
			break;
		case HAS_KEY_WAITUP:
			if(p_info->CurKey != p_info->PreDownKey){
				p_info->KeyState = HAS_NO_KEY;
				if(p_info->KeyUpCallBack){
					p_info->KeyUpCallBack(p_info->PreDownKey);
				}
				++p_info->DoubleClickSpaceTime;
			}
			break;
		default:
			break;
	}
	if(p_info->DoubleClickSpaceTime)
	{
		++p_info->DoubleClickSpaceTime;
	}
	if(p_info->DoubleClickSpaceTime > 20)p_info->DoubleClickSpaceTime = 0;
	p_info->PreDownKey = p_info->CurKey; //将本次的按键值更新至前一次按键的变量中
}
u8 Keydowncallback(u16 key, u16 time)
{
//	switch(key)
//	{
//		case 0:
//			if(time < 200)//在一定时间内允许长按
//			{
				return REENTER;//返回1. 开始计数长按时间
//			}
//			break;
//		case 1:
//			if(time < 1000)
//			{
//				return REENTER;
//			}
//			break;
//		default:break;
//		return NO_REENTER;
//	}
}
void Keyupcallback(u16 key)
{

}

u8 KEY_Scan1(u8 mode)
{
	u8 key_sfr = 0;
	
	key0.CurKey = KEY0;
	DitherlessKey(&key0);
	key1.CurKey = KEY1;
	DitherlessKey(&key1);

	if(key0.CurKey == 0)
	{
		if(key0.SameKeyCntr > 20)
		{
			key_sfr |= 0x02;
		}
		else
		{
			key_sfr |= 0x01;
		}
		if(key0.DoubleClickSure)
		{
			key_sfr |=0x03;
		}
	}
	
		if(key1.CurKey == 0)
	{
		if(key1.SameKeyCntr > 20)
		{
			key_sfr |= (0x02 << 2);
		}
		else
		{
			key_sfr |= (0x01 << 2);
		}
		if(key1.DoubleClickSure)
		{
			key_sfr |=(0x03<<2);
		}
	}
return key_sfr;
}

