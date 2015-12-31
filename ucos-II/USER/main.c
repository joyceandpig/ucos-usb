#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "touch.h"
#include "includes.h" // 启动ucosii
#include "gui.h"
#include "malloc.h"
#include "main_ui.h"
#include "common.h"
#include "text.h"
#include "ff.h"
#include "exfuns.h"
#include "fontupd.h"
#include "spi_flash.h"
#include "mmc_sd.h"
#include "usmart.h"
#include "piclib.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_hid_printf.h"
#include "usb_desc.h"
#include "mass_mal.h"
#include "memory.h"

OS_EVENT * sem;
OS_EVENT * msg;
extern __IO uint8_t ReciveDataFromUsbHost;
__IO uint8_t USB_Receive[0x40];
extern USBClass USB_Type;
/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
#define START_TASK_PRIO      		20        //开始任务的优先级设置为最低
#define START_STK_SIZE  				64        //设置任务堆栈大小
OS_STK START_TASK_STK[START_STK_SIZE];    //任务堆栈	
void start_task(void *pdata);	            //任务函数

#define MAIN_TASK_PRIO      		8        //开始任务的优先级设置为最低
#define MAIN_STK_SIZE  				64        //设置任务堆栈大小
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];    //任务堆栈	
void main_task(void *pdata);	            //任务函数

#define WATCH_TASK_PRIO      		9        //开始任务的优先级设置为最低
#define WATCH_STK_SIZE  				64        //设置任务堆栈大小
OS_STK WATCH_TASK_STK[WATCH_STK_SIZE];    //任务堆栈	
void watch_task(void *pdata);	            //任务函数

#define LED_TASK_PRIO      		10        //开始任务的优先级设置为最低
#define LED_STK_SIZE  				64        //设置任务堆栈大小
OS_STK LED_TASK_STK[LED_STK_SIZE];    //任务堆栈	
void led_task(void *pdata);	            //任务函数

#define USB_TASK_PRIO      		7        //开始任务的优先级设置为最低
#define USB_STK_SIZE  				64        //设置任务堆栈大小
OS_STK USB_TASK_STK[USB_STK_SIZE];    //任务堆栈	
void usb_task(void *pdata);	            //任务函数


void Bsp_init(void)
{
	NVIC_Configuration();	 
	LED_Init();
	delay_init();
	uart_init(9600);
//	usmart_dev.init(72);
	KEY_Init();
	LCD_Init();
	tp_dev.init();
	gui_init();
	mem_init();				//内存池初始化
	SPI_Flash_Init();		//W25Qxx初始化  外置内存			
	SD_Initialize();
	exfuns_init();//为exfuns申请内存 fatfa
	f_mount(fs[0],"0:",1);//sd card
	f_mount(fs[1],"1:",1);//spi flash
	font_init();//汉字显示字库调用初始化
	piclib_init();//picture init
	
}
void load_main_ui(void)
{
	u8 lcd_id[12];			//存放LCD ID字符串	
	u8 *s1 = "my lcd test",
		 *s2 = "my led test",
	   *s3 = "my ucosii test";
	
	LCD_Clear(WHITE);	//以白色颜色清屏
 	POINT_COLOR=RED;	//设置字体为红色 
	BACK_COLOR = WHITE;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	LCD_ShowString(0,0,200,16,16,lcd_id);//显示LCD编号
	
	LCD_ShowChar(0,20,'C',24,0);
	
	LCD_Fill(100,100,120,120,CYAN);
  LCD_ShowNum(140,140,7,1,12);
	LCD_ShowxNum(150,150,123,3,16,0);
	
	LCD_ShowString(30,20,200,16,16,s1);	//字体有12 16 24 三种
	LCD_ShowString(30,40,200,16,16,s2);	
	LCD_ShowString(30,60,200,16,16,s3);
	
	LCD_DrawLine(0,140,lcddev.width,140);//得到屏幕的宽度
	LCD_DrawLine(0,80,lcddev.width,80);
	LCD_DrawLine(150,0,150,80);
	
 	POINT_COLOR=BLUE;//设置字体为蓝色 
  LCD_ShowString(160,30,200,16,16,"CPU:   %");	
}

int main(void)
{	
	
	Bsp_init();//硬件接口初始化
	load_main_ui();//启动界面
	printf("ready to start\n");
	
	OSInit();
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();
}


void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  
	
	sem = OSSemCreate(0); 
	msg = OSMboxCreate((void*)0);
	
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);	//7	
	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);
	OSTaskCreate(watch_task,(void *)0,(OS_STK*)&WATCH_TASK_STK[WATCH_STK_SIZE-1],WATCH_TASK_PRIO);	
	OSTaskCreate(usb_task,(void *)0,(OS_STK*)&USB_TASK_STK[USB_STK_SIZE-1],USB_TASK_PRIO);
 	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}
u8 CreateButton(void)
{
	return (app_items_sel((lcddev.width-180)/2,(lcddev.height-290)/2,180,72,0X80,""));
}
//强制要求任务返回
volatile u8 system_task_return=0;
void main_task(void *pdata)
{
	u8 touch_choice;
	u8 oldsel;
	u8 res = 0xff;

	mui_init();
//	gui_draw_arcrectangle(20,20,100,24,0,1,BLACK,BLACK);
//	gui_show_strmid(20,20,100,24,YELLOW,24,"这是一个测试");
	

	while(1)
	{

TOUCH:
		if(tp_dev.scan(0)){//使用屏幕坐标
			if((tp_dev.x[0]<lcddev.width && 80 < tp_dev.y[0] && tp_dev.y[0] < 140)){
					TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);
					OSTimeDlyHMSM(0,0,0,1);
					goto TOUCH;
				}
			}	
		touch_choice = mui_touch_chk();
		system_task_return = 0;
		switch(touch_choice)
		{
			case 0:
				Hid_printf("选择第一个图标\n");
				res = CreateButton();
//			Joystick_Send(0,0,0,1);
//				delay_ms(500);
			Hid_printf("打开/关闭开关\n");
			LCD_Fill(5,10,230,116,MUI_IN_BACKCOLOR);
			for(oldsel = 0; oldsel < 3; oldsel++){
		LCD_Fill(muidev.icos[oldsel].x,muidev.icos[oldsel].y,muidev.icos[oldsel].x+muidev.icos[oldsel].width,muidev.icos[oldsel].y+muidev.icos[oldsel].height,MUI_IN_BACKCOLOR);
		minibmp_decode(muidev.icos[oldsel].path,muidev.icos[oldsel].x+5,muidev.icos[oldsel].y,muidev.icos[oldsel].width,muidev.icos[oldsel].height,0,0);		
		gui_show_strmid(muidev.icos[oldsel].x,muidev.icos[oldsel].y+67,muidev.icos[oldsel].width,16,MUI_FONT_COLOR,16,muidev.icos[oldsel].name);//显示名字
			}
			if(res == 0x01){
		LCD_Fill(muidev.icos[8].x,muidev.icos[8].y,muidev.icos[8].x+muidev.icos[8].width,muidev.icos[8].y+muidev.icos[8].height,MUI_IN_BACKCOLOR);
		minibmp_decode(muidev.icos[8].path,muidev.icos[8].x+5,muidev.icos[8].y,muidev.icos[oldsel].width,muidev.icos[8].height,0,0);		
		gui_show_strmid(muidev.icos[8].x,muidev.icos[8].y+67,muidev.icos[8].width,16,MUI_FONT_COLOR,16,muidev.icos[8].name);//显示名字
			}
				break;
			case 1:
				if(USB_Type == HID){Hid_printf("选择第二个图标\n");}break;
			case 2:if(USB_Type == HID){Hid_printf("选择第三个图标\n");}break;
			case 3:if(USB_Type == HID){Hid_printf("选择第四个图标\n");}break;
			case 4:if(USB_Type == HID){Hid_printf("选择第五个图标\n");}break;
			case 5:if(USB_Type == HID){Hid_printf("选择第六个图标\n");}break;
			case 6:if(USB_Type == HID){Hid_printf("选择第七个图标\n");}
				USB_Type = HID;
				break;
			case 7:if(USB_Type == HID){Hid_printf("选择第八个图标\n");}
				USB_Type = MassStorage;
				break;
			case 8:if(USB_Type == HID){Hid_printf("选择第九个图标\n");}break;
			default:break;
		}
//		if(touch_choice == 0)mui_init();	
		OSTimeDlyHMSM(0,0,0,4);
	}
}
void usb_task(void *pdata)
{
	u8 USB_STA = 0x0F;
	printf("\nstart to init usb link\n");
	while(1)
	{
		if(USB_STA != USB_Type){//说明需要连接另一种usb类型 
			if(USB_Type == MassStorage){
				Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//得到SD卡容量（字节），当SD卡容量超过4G的时候,需要用到两个u32来表示
				Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
				Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
				
				Mass_Memory_Size[1]=4916*1024;//前4.8M字节
				Mass_Block_Size[1] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
				Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
				
				Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
				Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存
			}
			usb_connect_init();
			USB_STA = USB_Type;
			while(bDeviceState != CONFIGURED){//当USB配置成功了，LED1亮，否则，灭
				LED0_OFF;}
			LED0_ON;
		}
//		OSSemPend(sem,0,&err);
//		LED0 ^= 1;
//		USB_GetData(USB_Receive,0x40);
//		Hid_printf("had RecDataFromUsbHost\n");
//		for(i = 0;i < 64;i++){
////			LCD_ShowChar(x,y,USB_Receive[i],16,0);
//			y=(i-20*(x/8))*16;
//			if(y==320){
//				x+=8;
//				y=0;
//			}
//		}
		OSTimeDlyHMSM(0,0,0,300);
	}
}
void led_task(void *pdata)
{
	while(1)
	{
		LED1_ON;
		OSTimeDlyHMSM(0,0,0,500);
		LED1_OFF;
		OSTimeDlyHMSM(0,0,0,500);
	}
}
void watch_task(void *pdata)
{
	u8 key = 0;
	u32 cnt = 0;
	while(1)
	{
		if(ReciveDataFromUsbHost){
//			OSSemPost(sem);
//			OSSemPend(sem,0,&err);
			LED0 ^= 1;
			USB_GetData(USB_Receive,0x40);
			Hid_printf("had RecDataFromUsbHost\n");
			ReciveDataFromUsbHost = false;
		}
		cnt++;
		if(cnt%20 == 0){
			LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);//0x80 显示所有位，0 只显示有效位
			LCD_ShowxNum(0,200,OSTimeGet()/200,10,16,0);//0x80
			cnt = 0;
		}

		key = KEY_Scan1(1);
//		switch(key){
//			case KEY0_PRES-1:
//				system_task_return = 1;
//				break;
//			case KEY1_PRES-1:
//				LED0_ON;
//				break;
//			case WKUP_PRES-1:
//				LCD_Fill(0,81,lcddev.width,139,WHITE);
//				break;
//			default:break;
//		}
			if(key == 0x03){
				LCD_Fill(0,81,lcddev.width,139,YELLOW);
			}else if(key  == 0x01){
				system_task_return = 1;
			}else if(key  == 0x02){
				LED0_ON;LED1_ON;
			}
			if((key>>2) == 0x03){
				LCD_Fill(200,200,20,20,RED);
			}else if((key>>2) == 0x01){
				LED0_ON;LED1_OFF== 0x02;
			}else if(key>>2){
				LED0_ON;LED1_OFF;
			}
			
			OSTimeDlyHMSM(0,0,0,5);
	}
}

