#ifndef __COMMON_H
#define __COMMON_H 	
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	 	 	  	 	 
#include "lcd.h"
#include "24cxx.h"	
#include "touch.h"	 
#include "malloc.h"
#include "string.h"
#include "includes.h"
#include "gui.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APPͨ�� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/2/16
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//�����Ը��ֱַ���LCD��֧��.
////////////////////////////////////////////////////////////////////////////////// 	  


//Ӳ��ƽ̨��Ӳ���汾����	   	
#define HARDWARE_VERSION	   		30		//Ӳ���汾,�Ŵ�10��,��1.0��ʾΪ10
#define SOFTWARE_VERSION	    	230		//����汾,�Ŵ�100��,��1.00,��ʾΪ100
//Ӳ��V3.0
//1������STM32F103RCT6��Ϊ����
//2������CH340G��ΪUSBת����оƬ
//3���޸�JTAG SWD������IO�ڱ�ռ��,�Ӷ�Ӱ����������.
//4������W25Q64��Ϊ�ⲿFLASH�洢��
//5�����Ĳ�����������ӷ�ʽ.
//6��ȥ��JF24C��Ԥ��λ��
 


//ϵͳ���ݱ����ַ			  
#define SYSTEM_PARA_SAVE_BASE 		100		//ϵͳ��Ϣ�����׵�ַ.��100��ʼ.
			    
extern volatile u8 system_task_return;

////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��/ͼƬ·��
extern const u8* APP_OK_PIC;			//ȷ��ͼ��
extern const u8* APP_CANCEL_PIC;		//ȡ��ͼ��
extern const u8* APP_UNSELECT_PIC;		//δѡ��ͼ��
extern const u8* APP_SELECT_PIC;		//ѡ��ͼ��
extern const u8* APP_ASCII_60;			//����������·��
extern const u8* APP_ASCII_28;			//����������·��
extern const u8* APP_VOL_PIC;			//����ͼƬ·��

extern const u8 APP_ALIENTEK_ICO[72];	//��������ͼ��,�����flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP���ܹ�����Ŀ
#define APP_FUNS_NUM	9

//app��Ҫ���ܽ������
extern const u8* APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern const u8* APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//ƽ���ߵ���ֹ��ɫ����
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//��ֹ��ɫ
#define WIN_SMOOTH_LINE_MC	0X1600B1	//�м���ɫ

//��������ѡ����Ŀ��������Ϣ
#define APP_ITEM_BTN1_WIDTH		60	  		//��2������ʱ�Ŀ��
#define APP_ITEM_BTN2_WIDTH		100			//ֻ��1������ʱ�Ŀ��
#define APP_ITEM_BTN_HEIGHT		40			//�����߶�
#define APP_ITEM_ICO_SIZE		32			//ICOͼ��ĳߴ�

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//ѡ��ʱ�ı���ɫ
#define APP_WIN_BACK_COLOR	 	0XC618		//���屳��ɫ


#define APP_FB_TOPBAR_HEIGHT	20			//�ļ��������,���������ĸ߶�
#define APP_FB_BTMBAR_HEIGHT	20			//�ļ��������/���Խ���,�ײ������ĸ߶�
#define APP_TEST_TOPBAR_HEIGHT	20			//���Խ���,���������߶�


/////////////////////////////////////////////////////////////////////////
																			    

#endif
