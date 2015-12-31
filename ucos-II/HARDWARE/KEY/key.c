#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//�������� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/06
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//������ʼ������ 
//PA0.15��PC5 ���ó�����
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1���� 
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// �ް�������
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
				if(p_info->KeyDownCallBack){//�ж�����ָ���Ƿ����ú���
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
	p_info->PreDownKey = p_info->CurKey; //�����εİ���ֵ������ǰһ�ΰ����ı�����
}
u8 Keydowncallback(u16 key, u16 time)
{
//	switch(key)
//	{
//		case 0:
//			if(time < 200)//��һ��ʱ����������
//			{
				return REENTER;//����1. ��ʼ��������ʱ��
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

