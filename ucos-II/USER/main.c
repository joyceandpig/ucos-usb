#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "touch.h"
#include "includes.h" // ����ucosii
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
/////////////////////////UCOSII��������///////////////////////////////////
//START ����
#define START_TASK_PRIO      		20        //��ʼ��������ȼ�����Ϊ���
#define START_STK_SIZE  				64        //���������ջ��С
OS_STK START_TASK_STK[START_STK_SIZE];    //�����ջ	
void start_task(void *pdata);	            //������

#define MAIN_TASK_PRIO      		8        //��ʼ��������ȼ�����Ϊ���
#define MAIN_STK_SIZE  				64        //���������ջ��С
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];    //�����ջ	
void main_task(void *pdata);	            //������

#define WATCH_TASK_PRIO      		9        //��ʼ��������ȼ�����Ϊ���
#define WATCH_STK_SIZE  				64        //���������ջ��С
OS_STK WATCH_TASK_STK[WATCH_STK_SIZE];    //�����ջ	
void watch_task(void *pdata);	            //������

#define LED_TASK_PRIO      		10        //��ʼ��������ȼ�����Ϊ���
#define LED_STK_SIZE  				64        //���������ջ��С
OS_STK LED_TASK_STK[LED_STK_SIZE];    //�����ջ	
void led_task(void *pdata);	            //������

#define USB_TASK_PRIO      		7        //��ʼ��������ȼ�����Ϊ���
#define USB_STK_SIZE  				64        //���������ջ��С
OS_STK USB_TASK_STK[USB_STK_SIZE];    //�����ջ	
void usb_task(void *pdata);	            //������


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
	mem_init();				//�ڴ�س�ʼ��
	SPI_Flash_Init();		//W25Qxx��ʼ��  �����ڴ�			
	SD_Initialize();
	exfuns_init();//Ϊexfuns�����ڴ� fatfa
	f_mount(fs[0],"0:",1);//sd card
	f_mount(fs[1],"1:",1);//spi flash
	font_init();//������ʾ�ֿ���ó�ʼ��
	piclib_init();//picture init
	
}
void load_main_ui(void)
{
	u8 lcd_id[12];			//���LCD ID�ַ���	
	u8 *s1 = "my lcd test",
		 *s2 = "my led test",
	   *s3 = "my ucosii test";
	
	LCD_Clear(WHITE);	//�԰�ɫ��ɫ����
 	POINT_COLOR=RED;	//��������Ϊ��ɫ 
	BACK_COLOR = WHITE;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
	LCD_ShowString(0,0,200,16,16,lcd_id);//��ʾLCD���
	
	LCD_ShowChar(0,20,'C',24,0);
	
	LCD_Fill(100,100,120,120,CYAN);
  LCD_ShowNum(140,140,7,1,12);
	LCD_ShowxNum(150,150,123,3,16,0);
	
	LCD_ShowString(30,20,200,16,16,s1);	//������12 16 24 ����
	LCD_ShowString(30,40,200,16,16,s2);	
	LCD_ShowString(30,60,200,16,16,s3);
	
	LCD_DrawLine(0,140,lcddev.width,140);//�õ���Ļ�Ŀ��
	LCD_DrawLine(0,80,lcddev.width,80);
	LCD_DrawLine(150,0,150,80);
	
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
  LCD_ShowString(160,30,200,16,16,"CPU:   %");	
}

int main(void)
{	
	
	Bsp_init();//Ӳ���ӿڳ�ʼ��
	load_main_ui();//��������
	printf("ready to start\n");
	
	OSInit();
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();
}


void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  
	
	sem = OSSemCreate(0); 
	msg = OSMboxCreate((void*)0);
	
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);	//7	
	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);
	OSTaskCreate(watch_task,(void *)0,(OS_STK*)&WATCH_TASK_STK[WATCH_STK_SIZE-1],WATCH_TASK_PRIO);	
	OSTaskCreate(usb_task,(void *)0,(OS_STK*)&USB_TASK_STK[USB_STK_SIZE-1],USB_TASK_PRIO);
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}
u8 CreateButton(void)
{
	return (app_items_sel((lcddev.width-180)/2,(lcddev.height-290)/2,180,72,0X80,""));
}
//ǿ��Ҫ�����񷵻�
volatile u8 system_task_return=0;
void main_task(void *pdata)
{
	u8 touch_choice;
	u8 oldsel;
	u8 res = 0xff;

	mui_init();
//	gui_draw_arcrectangle(20,20,100,24,0,1,BLACK,BLACK);
//	gui_show_strmid(20,20,100,24,YELLOW,24,"����һ������");
	

	while(1)
	{

TOUCH:
		if(tp_dev.scan(0)){//ʹ����Ļ����
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
				Hid_printf("ѡ���һ��ͼ��\n");
				res = CreateButton();
//			Joystick_Send(0,0,0,1);
//				delay_ms(500);
			Hid_printf("��/�رտ���\n");
			LCD_Fill(5,10,230,116,MUI_IN_BACKCOLOR);
			for(oldsel = 0; oldsel < 3; oldsel++){
		LCD_Fill(muidev.icos[oldsel].x,muidev.icos[oldsel].y,muidev.icos[oldsel].x+muidev.icos[oldsel].width,muidev.icos[oldsel].y+muidev.icos[oldsel].height,MUI_IN_BACKCOLOR);
		minibmp_decode(muidev.icos[oldsel].path,muidev.icos[oldsel].x+5,muidev.icos[oldsel].y,muidev.icos[oldsel].width,muidev.icos[oldsel].height,0,0);		
		gui_show_strmid(muidev.icos[oldsel].x,muidev.icos[oldsel].y+67,muidev.icos[oldsel].width,16,MUI_FONT_COLOR,16,muidev.icos[oldsel].name);//��ʾ����
			}
			if(res == 0x01){
		LCD_Fill(muidev.icos[8].x,muidev.icos[8].y,muidev.icos[8].x+muidev.icos[8].width,muidev.icos[8].y+muidev.icos[8].height,MUI_IN_BACKCOLOR);
		minibmp_decode(muidev.icos[8].path,muidev.icos[8].x+5,muidev.icos[8].y,muidev.icos[oldsel].width,muidev.icos[8].height,0,0);		
		gui_show_strmid(muidev.icos[8].x,muidev.icos[8].y+67,muidev.icos[8].width,16,MUI_FONT_COLOR,16,muidev.icos[8].name);//��ʾ����
			}
				break;
			case 1:
				if(USB_Type == HID){Hid_printf("ѡ��ڶ���ͼ��\n");}break;
			case 2:if(USB_Type == HID){Hid_printf("ѡ�������ͼ��\n");}break;
			case 3:if(USB_Type == HID){Hid_printf("ѡ����ĸ�ͼ��\n");}break;
			case 4:if(USB_Type == HID){Hid_printf("ѡ������ͼ��\n");}break;
			case 5:if(USB_Type == HID){Hid_printf("ѡ�������ͼ��\n");}break;
			case 6:if(USB_Type == HID){Hid_printf("ѡ����߸�ͼ��\n");}
				USB_Type = HID;
				break;
			case 7:if(USB_Type == HID){Hid_printf("ѡ��ڰ˸�ͼ��\n");}
				USB_Type = MassStorage;
				break;
			case 8:if(USB_Type == HID){Hid_printf("ѡ��ھŸ�ͼ��\n");}break;
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
		if(USB_STA != USB_Type){//˵����Ҫ������һ��usb���� 
			if(USB_Type == MassStorage){
				Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//�õ�SD���������ֽڣ�����SD����������4G��ʱ��,��Ҫ�õ�����u32����ʾ
				Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
				Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
				
				Mass_Memory_Size[1]=4916*1024;//ǰ4.8M�ֽ�
				Mass_Block_Size[1] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
				Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
				
				Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
				Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�
			}
			usb_connect_init();
			USB_STA = USB_Type;
			while(bDeviceState != CONFIGURED){//��USB���óɹ��ˣ�LED1����������
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
			LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);//0x80 ��ʾ����λ��0 ֻ��ʾ��Чλ
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

