#include "common.h"
#include "main_ui.h"

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



const u8* APP_OK_PIC="1:/SYSTEM/APP/COMMON/ok.bmp";				//ȷ��ͼ��
const u8* APP_CANCEL_PIC="1:/SYSTEM/APP/COMMON/cancel.bmp";		//ȡ��ͼ��



//ALIENTEK logo ͼ��
const u8 APP_ALIENTEK_ICO[72]=
{
0x01,0xF0,0x00,0x07,0xFC,0x00,0x1F,0xFE,0x00,0x1F,0xFF,0x00,0x3F,0xFF,0x80,0x3F,
0xFF,0x80,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,
0xC0,0x7F,0xFF,0xC0,0x67,0xFC,0xC0,0x63,0xF8,0xC0,0x21,0xF0,0x80,0x31,0xF1,0x80,
0x18,0xE3,0x00,0x1C,0xE7,0x00,0x0F,0xFE,0x00,0x07,0xFC,0x00,0x03,0xF8,0x00,0x01,
0xF0,0x00,0x00,0xE0,0x00,0x00,0x40,0x00,
};
////////////////////////////////α����������취////////////////////////////////
u32 random_seed=1;
void app_srand(u32 seed)
{
	random_seed=seed;
}
//��ȡα�����
//���Բ���0~RANDOM_MAX-1�������
//seed:����
//max:���ֵ	  		  
//����ֵ:0~(max-1)�е�һ��ֵ 		
u32 app_get_rand(u32 max)
{			    	    
	random_seed=random_seed*22695477+1;
	return (random_seed)%max; 
}  

//��ȡ����ɫ
//x,y,width,height:����ɫ��ȡ��Χ
//ctbl:����ɫ���ָ��
void app_read_bkcolor(u16 x,u16 y,u16 width,u16 height,u16 *ctbl)
{
	u16 x0,y0,ccnt;
	ccnt=0;
	for(y0=y;y0<y+height;y0++)
	{
		for(x0=x;x0<x+width;x0++)
		{
			ctbl[ccnt]=gui_phy.read_point(x0,y0);//��ȡ��ɫ
			ccnt++;
		}
	}
}  
//�ָ�����ɫ
//x,y,width,height:����ɫ��ԭ��Χ
//ctbl:����ɫ���ָ��
void app_recover_bkcolor(u16 x,u16 y,u16 width,u16 height,u16 *ctbl)
{
	u16 x0,y0,ccnt;
	ccnt=0;
	for(y0=y;y0<y+height;y0++)
	{
		for(x0=x;x0<x+width;x0++)
		{
			gui_phy.draw_point(x0,y0,ctbl[ccnt]);//��ȡ��ɫ
			ccnt++;
		}
	}
}
//2ɫ��
//x,y,width,height:���꼰�ߴ�.
//mode:	���÷ֽ���
//	    [3]:�ұ߷ֽ���
//		[2]:��߷ֽ���
//		[1]:�±߷ֽ���
//		[0]:�ϱ߷ֽ���
void app_gui_tcbar(u16 x,u16 y,u16 width,u16 height,u8 mode)
{
 	u16 halfheight=height/2;
 	gui_fill_rectangle(x,y,width,halfheight,LIGHTBLUE);  			//���ײ���ɫ(ǳ��ɫ)	
 	gui_fill_rectangle(x,y+halfheight,width,halfheight,GRAYBLUE); 	//���ײ���ɫ(����ɫ)
	if(mode&0x01)gui_draw_hline(x,y,width,DARKBLUE);
	if(mode&0x02)gui_draw_hline(x,y+height-1,width,DARKBLUE);
	if(mode&0x04)gui_draw_vline(x,y,height,DARKBLUE);
	if(mode&0x08)gui_draw_vline(x+width-1,y,width,DARKBLUE);
} 


//��ָ��λ����ʾһ�����ַ�
//�ַ�ȡģ����:����ʽ,˳��(��λ��ǰ),����.C51��ʽ.
//fontbase:�ֿ��ַ
//x,y:����
//chr:��Χ�����ֿ����
//size:�ߴ�.ʹ�õ���60/28 
//color:������ɫ
//bkcolor:����ɫ
void app_showbigchar(u8 *fontbase,u16 x,u16 y,u8 chr,u8 size,u16 color,u16 bkcolor)
{
    u8 n,t;
	u8 temp;
	u16 offset;
	u16 colortemp=POINT_COLOR; 
	u16 x0=x;     
	if(size==60)//60����
	{
		if(chr>='0'&&chr<=':')offset=chr-'0';
		else if(chr=='.')offset=11;
		else if(chr=='C')offset=12;
		else if(chr==' ')offset=13;
		else return;		//������ʾ���ַ�
		offset*=240;		//ƫ��(ÿ���ַ�����ռ��240�ֽ�)
 		for(n=0;n<240;n++)
		{
			temp=fontbase[offset+n];
			for(t=0;t<8;t++)
			{
		        if(temp&0x80)gui_phy.draw_point(x,y,color);  
				else gui_phy.draw_point(x,y,bkcolor);  	 
				temp<<=1;
				x++;
				if(((n%4)==3)&&t==5)
				{
					x=x0;
					y++;  
					break;
				}
			}
		}
	}else 		//28����
	{		
		if(chr>='0'&&chr<='9')offset=chr-'0';
		else if(chr=='.')offset=10;
		else if(chr=='-')offset=11;
		else if(chr>='A'&&chr<='F')offset=12+chr-'A';
		else if(chr==' ')offset=18;
		else return;		//������ʾ���ַ�
		offset*=56;			//ƫ��(ÿ���ַ�����ռ��56�ֽ�)
 		for(n=0;n<56;n++)
		{
			temp=fontbase[offset+n];
			for(t=0;t<8;t++)
			{
		        if(temp&0x80)gui_phy.draw_point(x,y,color);  
				else gui_phy.draw_point(x,y,bkcolor);  	 
				temp<<=1;
				x++;
				if(((n%2)==1)&&t==5)
				{
					x=x0;
					y++;  
					break;
				}
			}
		}
	}	     
	POINT_COLOR=colortemp;	    	   	 	  
} 


//��һ�������м���ʾ����
//x,y,width,height:����
//num:Ҫ��ʾ������
//len:λ��
//size:����ߴ�
//ptcolor,bkcolor:������ɫ�Լ�����ɫ   
void app_show_nummid(u16 x,u16 y,u16 width,u16 height,u32 num,u8 len,u8 size,u16 ptcolor,u16 bkcolor)
{
	u16 numlen;
	u8 xoff,yoff;
	numlen=(size/2)*len;//���ֳ���
	if(numlen>width||size>height)return;
	xoff=(width-numlen)/2;
	yoff=(height-size)/2;
	POINT_COLOR=ptcolor;
	BACK_COLOR=bkcolor;
	LCD_ShowxNum(x+xoff,y+yoff,num,len,size,0X80);//��ʾ�������
}
//��һ��ƽ�����ɵĲ�ɫ��(�����)
//���м�Ϊ���,����չ��
//x,y,width,height:����������ߴ�
//sergb,mrgb:��ֹ��ɫ���м���ɫ
void app_draw_smooth_line(u16 x,u16 y,u16 width,u16 height,u32 sergb,u32 mrgb)
{	  
	gui_draw_smooth_rectangle(x,y,width/2,height,sergb,mrgb);	   		//ǰ��ν���
	gui_draw_smooth_rectangle(x+width/2,y,width/2,height,mrgb,sergb);   //���ν���
}      

//�жϴ�������ǰֵ�ǲ�����ĳ��������
//tp:������
//x,y,width,height:����ͳߴ� 
//����ֵ:0,����������;1,��������.
u8 app_tp_is_in_area(_m_tp_dev *tp,u16 x,u16 y,u16 width,u16 height)
{						 	 
	if(tp->x[0]<=(x+width)&&tp->x[0]>=x&&tp->y[0]<=(y+height)&&tp->y[0]>=y)return 1;
	else return 0;							 	
}
//��ʾ��Ŀ
//x,y,itemwidth,itemheight:��Ŀ���꼰�ߴ�
//name:��Ŀ����
//icopath:ͼ��·��
void app_show_items(u16 x,u16 y,u16 itemwidth,u16 itemheight,u8*name,u8*icopath,u16 color,u16 bkcolor)
{
  	gui_fill_rectangle(x,y,itemwidth,itemheight,bkcolor);	//��䱳��ɫ
	gui_show_ptstr(x+5,y+(itemheight-16)/2,x+itemwidth-10-APP_ITEM_ICO_SIZE-5,y+itemheight,0,color,16,name,1);	//��ʾ��Ŀ����
}		 

//��Ŀѡ��
//x,y,width,height:����ߴ�(width��СΪ150,height��СΪ72)
//items[]:��Ŀ���ּ�
//itemsize:����Ŀ��(��󲻳���8��)
//selx:���.��ѡģʽʱ,��Ӧ�����ѡ�����.��ѡģʽʱ,��Ӧѡ�����Ŀ.
//mode:
//[7]:0,��OK��ť;1,��OK��ť
//[6]:0,����ȡ����ɫ;1,��ȡ����ɫ
//[5]:0,��ѡģʽ;1,��ѡģʽ
//[4]:0,������ͼ��;1,����ͼ��
//[3:0]:����
//caption:��������	  
//����ֵ:0,ok;����,ȡ�����ߴ���.
extern u8 app_items_sel(u16 x,u16 y,u16 width,u16 height,u8 mode,u8*caption) 
{
	u8 rval=0,res;
	u8 selsta=0;	//ѡ��״̬Ϊ0,
					//[7]:����Ƿ��Ѿ���¼��һ�ΰ��µ���Ŀ;
					//[6:4]:����
	                //[3:0]:��һ�ΰ��µ���Ŀ
	u16 i;

	u8 temp;
	u16 itemheight=0;		//ÿ����Ŀ�ĸ߶�
	u16 itemwidth=0;		//ÿ����Ŀ�Ŀ��
	u8* unselpath=0;		//δѡ�е�ͼ���·��
	u8* selpath=0;			//ѡ��ͼ���·��


 	_btn_obj * okbtn=0;		//ȷ����ť
 	_btn_obj * cancelbtn=0; //ȡ����ť

	

  if(mode&(1<<7))
	{
   	temp=(width-APP_ITEM_BTN1_WIDTH*2)/3;
		okbtn=btn_creat(x+temp,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN1_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);							//����OK��ť
		cancelbtn=btn_creat(x+APP_ITEM_BTN1_WIDTH+temp*2,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN1_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);//����CANCEL��ť
		if(okbtn==NULL||cancelbtn==NULL)rval=1;
		else
		{
	 		okbtn->caption="ON";//ȷ��
//			okbtn->bkctbl[3]=ARC_BTN_UPHC;//�ϰ벿����ɫ
		}
	}else 
	{
   	temp=(width-APP_ITEM_BTN2_WIDTH)/2;
		cancelbtn=btn_creat(x+temp,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN2_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);	//����CANCEL��ť
		if(cancelbtn==NULL)rval=1;
	}
 	if(rval==0)//֮ǰ�Ĳ�������  �����ɹ�
	{
 		cancelbtn->caption="OFF";//ȡ��
//		cancelbtn->bkctbl[3]=ARC_BTN_UPHC;//�ϰ벿����ɫ
		btn_draw(cancelbtn);			//����ť
	  if(mode&(1<<7))
			btn_draw(okbtn);	//����ť
		gui_draw_rectangle(200,280,40,40,RED);
		while(rval==0)//rval=0��ʾ���������ɹ�
		{
			tp_dev.scan(0);    
	if((tp_dev.x[0]>200)&&(tp_dev.x[0]<240)&&(tp_dev.y[0]>280)&&
			   (tp_dev.y[0]<320))
		{
			system_task_return = 1;
		}
		if(system_task_return){rval=1;break;};	//��Ҫ����
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ   
			delay_ms(1000/OS_TICKS_PER_SEC);		//��ʱһ��ʱ�ӽ���
//			OSTimeDlyHMSM(0,0,0,5);
			if(mode&(1<<7))
			{
				res=btn_check(okbtn,&in_obj);		//ȷ�ϰ�ť���
				if(res)
				{
					if((okbtn->sta&0X80)==0)//����Ч����  �ɿ������������γ�һ����Ч����
					{
						rval=0XFF;
						LED0_ON;
						break;//ȷ�ϰ�ť
					}
				}
			}   
			res=btn_check(cancelbtn,&in_obj);		//ȡ����ť���
			if(res)
			{
				if((cancelbtn->sta&0X80)==0)//����Ч����
				{
					rval=1;
					LED0_OFF;
					break;//ȡ����ť	 
				}
			}
//			temp=0XFF;//�����,���Ϊ0XFF,���ɿ���ʱ��,˵���ǲ�����Ч�����ڵ�.�����0XFF,���ʾTP�ɿ���ʱ��,������Ч������.
//			for(i=0;i<height;i++)
//			{
//				if(tp_dev.sta&TP_PRES_DOWN)//������������
//				{
//				 	if(app_tp_is_in_area(&tp_dev,x+5,y+32+i*(itemheight+1),itemwidth,itemheight))//�ж�ĳ��ʱ��,��������ֵ�ǲ�����ĳ��������
//					{ 
//						if((selsta&0X80)==0)//��û�а��¹�
//						{
////							app_show_items(x+5,y+32+i*(itemheight+1),itemwidth,itemheight,items[i],icopath,BLACK,APP_ITEM_SEL_BKCOLOR);//��ѡ��Ŀ
//							selsta=i;		//��¼��һ�ΰ��µ���Ŀ
//							selsta|=0X80;	//����Ѿ����¹���
//						}
//						break;		
//					}
//				}else //���������ɿ���
//				{
//				 	if(app_tp_is_in_area(&tp_dev,x+5,y+32+i*(itemheight+1),itemwidth,itemheight))//�ж�ĳ��ʱ��,��������ֵ�ǲ�����ĳ��������
//					{ 
//						temp=i;	   
//						break;
//					}
//				}
//			}
 		}
 	}
	btn_delete(okbtn);
	btn_delete(cancelbtn);

	if(rval==0XFF)return 0;
	return rval;
} 

//�ļ�������Ϣ��ʾ���� 
static u16 cpdmsg_x;
static u16 cpdmsg_y;


//ϵͳ������ʱ��,������ʾ���½���
//*pname:�����ļ�����
//pct:�ٷֱ�
//mode:ģʽ
//[0]:�����ļ���
//[1]:���°ٷֱ�pct
//[2]:�����ļ���
//[3~7]:����
//����ֵ:0,����;
//       1,��������
u8 app_boot_cpdmsg(u8*pname,u8 pct,u8 mode)
{													 
	if(mode&0X01)
	{
		LCD_Fill(cpdmsg_x+9*6,cpdmsg_y,cpdmsg_x+21*6,cpdmsg_y+12,BLACK);	//����ɫ
		LCD_ShowString(cpdmsg_x+9*6,cpdmsg_y,6*12,12,12,pname);			 	//��ʾ�ļ���
		printf("\r\nCopy File:%s\r\n",pname);  
	}
	if(mode&0X04)printf("Copy Folder:%s\r\n",pname);
	if(mode&0X02)//���°ٷֱ�
	{
		LCD_ShowString(cpdmsg_x+25*6,cpdmsg_y,240,320,12,"%");		
 		LCD_ShowNum(cpdmsg_x+22*6,cpdmsg_y,pct,3,12);//��ʾ��ֵ
		printf("File Copyed:%d\r\n",pct);
	}
	return 0;	
}

//�õ��汾��Ϣ
//buf:�汾������(������Ҫ6���ֽ�,�籣��:V1.00)
//ver:�汾�궨��
//len:�汾λ��.1,����ֻ��1��λ�İ汾,V1;2,����2��λ�汾,V1.0;3,����3��λ�汾,V1.00;
void app_get_version(u8*buf,u32 ver,u8 len)
{
	u8 i=0;
	buf[i++]='V';
	if(len==1)
	{
		buf[i++]=ver%10+'0';
	}else if(len==2)
	{ 	
		buf[i++]=(ver/10)%10+'0';
		buf[i++]='.';
		buf[i++]=ver%10+'0';
	}else
	{
		buf[i++]=(ver/100)%10+'0';
		buf[i++]='.';
		buf[i++]=(ver/10)%10+'0';
		buf[i++]=ver%10+'0';	 
	}
	buf[i]=0;//���������	 			   
}


