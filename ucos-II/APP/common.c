#include "common.h"
#include "main_ui.h"

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



const u8* APP_OK_PIC="1:/SYSTEM/APP/COMMON/ok.bmp";				//确认图标
const u8* APP_CANCEL_PIC="1:/SYSTEM/APP/COMMON/cancel.bmp";		//取消图标



//ALIENTEK logo 图标
const u8 APP_ALIENTEK_ICO[72]=
{
0x01,0xF0,0x00,0x07,0xFC,0x00,0x1F,0xFE,0x00,0x1F,0xFF,0x00,0x3F,0xFF,0x80,0x3F,
0xFF,0x80,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0xFF,
0xC0,0x7F,0xFF,0xC0,0x67,0xFC,0xC0,0x63,0xF8,0xC0,0x21,0xF0,0x80,0x31,0xF1,0x80,
0x18,0xE3,0x00,0x1C,0xE7,0x00,0x0F,0xFE,0x00,0x07,0xFC,0x00,0x03,0xF8,0x00,0x01,
0xF0,0x00,0x00,0xE0,0x00,0x00,0x40,0x00,
};
////////////////////////////////伪随机数产生办法////////////////////////////////
u32 random_seed=1;
void app_srand(u32 seed)
{
	random_seed=seed;
}
//获取伪随机数
//可以产生0~RANDOM_MAX-1的随机数
//seed:种子
//max:最大值	  		  
//返回值:0~(max-1)中的一个值 		
u32 app_get_rand(u32 max)
{			    	    
	random_seed=random_seed*22695477+1;
	return (random_seed)%max; 
}  

//读取背景色
//x,y,width,height:背景色读取范围
//ctbl:背景色存放指针
void app_read_bkcolor(u16 x,u16 y,u16 width,u16 height,u16 *ctbl)
{
	u16 x0,y0,ccnt;
	ccnt=0;
	for(y0=y;y0<y+height;y0++)
	{
		for(x0=x;x0<x+width;x0++)
		{
			ctbl[ccnt]=gui_phy.read_point(x0,y0);//读取颜色
			ccnt++;
		}
	}
}  
//恢复背景色
//x,y,width,height:背景色还原范围
//ctbl:背景色存放指针
void app_recover_bkcolor(u16 x,u16 y,u16 width,u16 height,u16 *ctbl)
{
	u16 x0,y0,ccnt;
	ccnt=0;
	for(y0=y;y0<y+height;y0++)
	{
		for(x0=x;x0<x+width;x0++)
		{
			gui_phy.draw_point(x0,y0,ctbl[ccnt]);//读取颜色
			ccnt++;
		}
	}
}
//2色条
//x,y,width,height:坐标及尺寸.
//mode:	设置分界线
//	    [3]:右边分界线
//		[2]:左边分界线
//		[1]:下边分界线
//		[0]:上边分界线
void app_gui_tcbar(u16 x,u16 y,u16 width,u16 height,u8 mode)
{
 	u16 halfheight=height/2;
 	gui_fill_rectangle(x,y,width,halfheight,LIGHTBLUE);  			//填充底部颜色(浅蓝色)	
 	gui_fill_rectangle(x,y+halfheight,width,halfheight,GRAYBLUE); 	//填充底部颜色(灰蓝色)
	if(mode&0x01)gui_draw_hline(x,y,width,DARKBLUE);
	if(mode&0x02)gui_draw_hline(x,y+height-1,width,DARKBLUE);
	if(mode&0x04)gui_draw_vline(x,y,height,DARKBLUE);
	if(mode&0x08)gui_draw_vline(x+width-1,y,width,DARKBLUE);
} 


//在指定位置显示一个大字符
//字符取模方法:逐行式,顺向(高位在前),阴码.C51格式.
//fontbase:字库地址
//x,y:坐标
//chr:范围根据字库而定
//size:尺寸.使用的有60/28 
//color:字体颜色
//bkcolor:背景色
void app_showbigchar(u8 *fontbase,u16 x,u16 y,u8 chr,u8 size,u16 color,u16 bkcolor)
{
    u8 n,t;
	u8 temp;
	u16 offset;
	u16 colortemp=POINT_COLOR; 
	u16 x0=x;     
	if(size==60)//60字体
	{
		if(chr>='0'&&chr<=':')offset=chr-'0';
		else if(chr=='.')offset=11;
		else if(chr=='C')offset=12;
		else if(chr==' ')offset=13;
		else return;		//不能显示的字符
		offset*=240;		//偏移(每个字符点阵占用240字节)
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
	}else 		//28字体
	{		
		if(chr>='0'&&chr<='9')offset=chr-'0';
		else if(chr=='.')offset=10;
		else if(chr=='-')offset=11;
		else if(chr>='A'&&chr<='F')offset=12+chr-'A';
		else if(chr==' ')offset=18;
		else return;		//不能显示的字符
		offset*=56;			//偏移(每个字符点阵占用56字节)
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


//在一个区域中间显示数字
//x,y,width,height:区域
//num:要显示的数字
//len:位数
//size:字体尺寸
//ptcolor,bkcolor:画笔颜色以及背景色   
void app_show_nummid(u16 x,u16 y,u16 width,u16 height,u32 num,u8 len,u8 size,u16 ptcolor,u16 bkcolor)
{
	u16 numlen;
	u8 xoff,yoff;
	numlen=(size/2)*len;//数字长度
	if(numlen>width||size>height)return;
	xoff=(width-numlen)/2;
	yoff=(height-size)/2;
	POINT_COLOR=ptcolor;
	BACK_COLOR=bkcolor;
	LCD_ShowxNum(x+xoff,y+yoff,num,len,size,0X80);//显示这个数字
}
//画一条平滑过渡的彩色线(或矩形)
//以中间为间隔,两边展开
//x,y,width,height:线条的坐标尺寸
//sergb,mrgb:起止颜色和中间颜色
void app_draw_smooth_line(u16 x,u16 y,u16 width,u16 height,u32 sergb,u32 mrgb)
{	  
	gui_draw_smooth_rectangle(x,y,width/2,height,sergb,mrgb);	   		//前半段渐变
	gui_draw_smooth_rectangle(x+width/2,y,width/2,height,mrgb,sergb);   //后半段渐变
}      

//判断触摸屏当前值是不是在某个区域内
//tp:触摸屏
//x,y,width,height:坐标和尺寸 
//返回值:0,不在区域内;1,在区域内.
u8 app_tp_is_in_area(_m_tp_dev *tp,u16 x,u16 y,u16 width,u16 height)
{						 	 
	if(tp->x[0]<=(x+width)&&tp->x[0]>=x&&tp->y[0]<=(y+height)&&tp->y[0]>=y)return 1;
	else return 0;							 	
}
//显示条目
//x,y,itemwidth,itemheight:条目坐标及尺寸
//name:条目名字
//icopath:图标路径
void app_show_items(u16 x,u16 y,u16 itemwidth,u16 itemheight,u8*name,u8*icopath,u16 color,u16 bkcolor)
{
  	gui_fill_rectangle(x,y,itemwidth,itemheight,bkcolor);	//填充背景色
	gui_show_ptstr(x+5,y+(itemheight-16)/2,x+itemwidth-10-APP_ITEM_ICO_SIZE-5,y+itemheight,0,color,16,name,1);	//显示条目名字
}		 

//条目选择
//x,y,width,height:坐标尺寸(width最小为150,height最小为72)
//items[]:条目名字集
//itemsize:总条目数(最大不超过8个)
//selx:结果.多选模式时,对应各项的选择情况.单选模式时,对应选择的条目.
//mode:
//[7]:0,无OK按钮;1,有OK按钮
//[6]:0,不读取背景色;1,读取背景色
//[5]:0,单选模式;1,多选模式
//[4]:0,不加载图表;1,加载图标
//[3:0]:保留
//caption:窗口名字	  
//返回值:0,ok;其他,取消或者错误.
extern u8 app_items_sel(u16 x,u16 y,u16 width,u16 height,u8 mode,u8*caption) 
{
	u8 rval=0,res;
	u8 selsta=0;	//选中状态为0,
					//[7]:标记是否已经记录第一次按下的条目;
					//[6:4]:保留
	                //[3:0]:第一次按下的条目
	u16 i;

	u8 temp;
	u16 itemheight=0;		//每个条目的高度
	u16 itemwidth=0;		//每个条目的宽度
	u8* unselpath=0;		//未选中的图标的路径
	u8* selpath=0;			//选中图标的路径


 	_btn_obj * okbtn=0;		//确定按钮
 	_btn_obj * cancelbtn=0; //取消按钮

	

  if(mode&(1<<7))
	{
   	temp=(width-APP_ITEM_BTN1_WIDTH*2)/3;
		okbtn=btn_creat(x+temp,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN1_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);							//创建OK按钮
		cancelbtn=btn_creat(x+APP_ITEM_BTN1_WIDTH+temp*2,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN1_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);//创建CANCEL按钮
		if(okbtn==NULL||cancelbtn==NULL)rval=1;
		else
		{
	 		okbtn->caption="ON";//确认
//			okbtn->bkctbl[3]=ARC_BTN_UPHC;//上半部分颜色
		}
	}else 
	{
   	temp=(width-APP_ITEM_BTN2_WIDTH)/2;
		cancelbtn=btn_creat(x+temp,y+height-APP_ITEM_BTN_HEIGHT-5,APP_ITEM_BTN2_WIDTH,APP_ITEM_BTN_HEIGHT,0,0x02);	//创建CANCEL按钮
		if(cancelbtn==NULL)rval=1;
	}
 	if(rval==0)//之前的操作正常  创建成功
	{
 		cancelbtn->caption="OFF";//取消
//		cancelbtn->bkctbl[3]=ARC_BTN_UPHC;//上半部分颜色
		btn_draw(cancelbtn);			//画按钮
	  if(mode&(1<<7))
			btn_draw(okbtn);	//画按钮
		gui_draw_rectangle(200,280,40,40,RED);
		while(rval==0)//rval=0表示创建按键成功
		{
			tp_dev.scan(0);    
	if((tp_dev.x[0]>200)&&(tp_dev.x[0]<240)&&(tp_dev.y[0]>280)&&
			   (tp_dev.y[0]<320))
		{
			system_task_return = 1;
		}
		if(system_task_return){rval=1;break;};	//需要返回
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//得到按键键值   
			delay_ms(1000/OS_TICKS_PER_SEC);		//延时一个时钟节拍
//			OSTimeDlyHMSM(0,0,0,5);
			if(mode&(1<<7))
			{
				res=btn_check(okbtn,&in_obj);		//确认按钮检测
				if(res)
				{
					if((okbtn->sta&0X80)==0)//有有效操作  松开触摸按键，形成一次有效触摸
					{
						rval=0XFF;
						LED0_ON;
						break;//确认按钮
					}
				}
			}   
			res=btn_check(cancelbtn,&in_obj);		//取消按钮检测
			if(res)
			{
				if((cancelbtn->sta&0X80)==0)//有有效操作
				{
					rval=1;
					LED0_OFF;
					break;//取消按钮	 
				}
			}
//			temp=0XFF;//标记量,如果为0XFF,在松开的时候,说明是不在有效区域内的.如果非0XFF,则表示TP松开的时候,是在有效区域内.
//			for(i=0;i<height;i++)
//			{
//				if(tp_dev.sta&TP_PRES_DOWN)//触摸屏被按下
//				{
//				 	if(app_tp_is_in_area(&tp_dev,x+5,y+32+i*(itemheight+1),itemwidth,itemheight))//判断某个时刻,触摸屏的值是不是在某个区域内
//					{ 
//						if((selsta&0X80)==0)//还没有按下过
//						{
////							app_show_items(x+5,y+32+i*(itemheight+1),itemwidth,itemheight,items[i],icopath,BLACK,APP_ITEM_SEL_BKCOLOR);//反选条目
//							selsta=i;		//记录第一次按下的条目
//							selsta|=0X80;	//标记已经按下过了
//						}
//						break;		
//					}
//				}else //触摸屏被松开了
//				{
//				 	if(app_tp_is_in_area(&tp_dev,x+5,y+32+i*(itemheight+1),itemwidth,itemheight))//判断某个时刻,触摸屏的值是不是在某个区域内
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

//文件复制信息提示坐标 
static u16 cpdmsg_x;
static u16 cpdmsg_y;


//系统启动的时候,用于显示更新进度
//*pname:更新文件名字
//pct:百分比
//mode:模式
//[0]:更新文件名
//[1]:更新百分比pct
//[2]:更新文件夹
//[3~7]:保留
//返回值:0,正常;
//       1,结束复制
u8 app_boot_cpdmsg(u8*pname,u8 pct,u8 mode)
{													 
	if(mode&0X01)
	{
		LCD_Fill(cpdmsg_x+9*6,cpdmsg_y,cpdmsg_x+21*6,cpdmsg_y+12,BLACK);	//填充底色
		LCD_ShowString(cpdmsg_x+9*6,cpdmsg_y,6*12,12,12,pname);			 	//显示文件名
		printf("\r\nCopy File:%s\r\n",pname);  
	}
	if(mode&0X04)printf("Copy Folder:%s\r\n",pname);
	if(mode&0X02)//更新百分比
	{
		LCD_ShowString(cpdmsg_x+25*6,cpdmsg_y,240,320,12,"%");		
 		LCD_ShowNum(cpdmsg_x+22*6,cpdmsg_y,pct,3,12);//显示数值
		printf("File Copyed:%d\r\n",pct);
	}
	return 0;	
}

//得到版本信息
//buf:版本缓存区(最少需要6个字节,如保存:V1.00)
//ver:版本宏定义
//len:版本位数.1,代表只有1个位的版本,V1;2,代表2个位版本,V1.0;3,代表3个位版本,V1.00;
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
	buf[i]=0;//加入结束符	 			   
}


