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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//APP通用 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/2/16
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//V1.1 20140216
//新增对各种分辨率LCD的支持.
////////////////////////////////////////////////////////////////////////////////// 	  


//硬件平台软硬件版本定义	   	
#define HARDWARE_VERSION	   		30		//硬件版本,放大10倍,如1.0表示为10
#define SOFTWARE_VERSION	    	230		//软件版本,放大100倍,如1.00,表示为100
//硬件V3.0
//1，采用STM32F103RCT6作为主控
//2，采用CH340G作为USB转串口芯片
//3，修改JTAG SWD的两个IO口被占用,从而影响仿真的问题.
//4，采用W25Q64作为外部FLASH存储器
//5，更改部分外设的连接方式.
//6，去掉JF24C的预留位置
 


//系统数据保存基址			  
#define SYSTEM_PARA_SAVE_BASE 		100		//系统信息保存首地址.从100开始.
			    
extern volatile u8 system_task_return;

////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern const u8* APP_OK_PIC;			//确认图标
extern const u8* APP_CANCEL_PIC;		//取消图标
extern const u8* APP_UNSELECT_PIC;		//未选中图标
extern const u8* APP_SELECT_PIC;		//选中图标
extern const u8* APP_ASCII_60;			//大数字字体路径
extern const u8* APP_ASCII_28;			//大数字字体路径
extern const u8* APP_VOL_PIC;			//音量图片路径

extern const u8 APP_ALIENTEK_ICO[72];	//启动界面图标,存放在flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP的总功能数目
#define APP_FUNS_NUM	9

//app主要功能界面标题
extern const u8* APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern const u8* APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8* APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//平滑线的起止颜色定义
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//起止颜色
#define WIN_SMOOTH_LINE_MC	0X1600B1	//中间颜色

//弹出窗口选择条目的设置信息
#define APP_ITEM_BTN1_WIDTH		60	  		//有2个按键时的宽度
#define APP_ITEM_BTN2_WIDTH		100			//只有1个按键时的宽度
#define APP_ITEM_BTN_HEIGHT		40			//按键高度
#define APP_ITEM_ICO_SIZE		32			//ICO图标的尺寸

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//选择时的背景色
#define APP_WIN_BACK_COLOR	 	0XC618		//窗体背景色


#define APP_FB_TOPBAR_HEIGHT	20			//文件浏览界面,顶部横条的高度
#define APP_FB_BTMBAR_HEIGHT	20			//文件浏览界面/测试界面,底部横条的高度
#define APP_TEST_TOPBAR_HEIGHT	20			//测试界面,顶部横条高度


/////////////////////////////////////////////////////////////////////////
																			    

#endif
