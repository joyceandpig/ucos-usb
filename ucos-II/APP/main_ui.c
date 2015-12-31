#include "includes.h" 
#include "gui.h"
#include "touch.h"
#include "guix.h"
#include "main_ui.h"


m_mui_dev muidev;

//icos的路径表
const u8 * mui_icos_path_tbl[9]=
{ 
//	"1:/SYSTEM/SYSICO/ebook.bmp",
//	"1:/SYSTEM/SYSICO/picture.bmp",	    
//	"1:/SYSTEM/SYSICO/usb.bmp",	    
//	"1:/SYSTEM/SYSICO/appstore.bmp",	    
//	"1:/SYSTEM/SYSICO/time.bmp",	    
//	"1:/SYSTEM/SYSICO/set.bmp",	    
//	"1:/SYSTEM/SYSICO/paint.bmp",	    
//	"1:/SYSTEM/SYSICO/wireless.bmp",	    
//	"1:/SYSTEM/SYSICO/notebook.bmp", 	 
	"1:/SYSTEM/MYOWN/1.bmp",
	"1:/SYSTEM/MYOWN/2.bmp",	    
	"1:/SYSTEM/MYOWN/3.bmp",	    
	"1:/SYSTEM/MYOWN/4.bmp",	    
	"1:/SYSTEM/MYOWN/5.bmp",	    
	"1:/SYSTEM/MYOWN/6.bmp",	    
	"1:/SYSTEM/MYOWN/7.bmp",	    
	"1:/SYSTEM/MYOWN/8.bmp",	    
	"1:/SYSTEM/MYOWN/9.bmp", 	
};  

//各个ICOS的对应功能名字
const u8* icos_name_tbl[GUI_LANGUAGE_NUM][9]=
{ 
	{
//		"电子图书","数码相框","USB连接",
//		"应用中心","时钟","系统设置",
//		"画板","无线传输","记事本",	   
		"图标1","图标2","图标3",
		"图标4","图标5","图标6",
		"图标7","图标8","图标9",
	}, 
	{
		"電子圖書","數碼相框","USB連接",
		"應用中心","時鐘","系統設置",
		"觸摸畫板","無線傳輸","記事本",	   
	}, 
	{
		"EBOOK","PHOTOS","USB",
		"APP","TIME","SETTINGS",
		"PAINT","WIRELESS","NOTEPAD",	   
	},  
};	

//初始化spb各个参数, 并加载主界面		  
void mui_init(void)
{
	u16 i,j;
	u16 offx=0,offy=0;
	if(lcddev.width<240||lcddev.height<320)return ;//屏幕尺寸不能小于320*240;
	offx=(lcddev.width-240)/2;
	offy=(lcddev.height-320)/2;
	muidev.status=0x0F;//没有选择任何图标
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			muidev.icos[i*3+j].x=5+j*80+offx;
			muidev.icos[i*3+j].y=10+i*105+offy;
			muidev.icos[i*3+j].width=70;
			muidev.icos[i*3+j].height=90;
			muidev.icos[i*3+j].path=(u8*)mui_icos_path_tbl[i*3+j];
			muidev.icos[i*3+j].name=(u8*)icos_name_tbl[gui_phy.language][i*3+j]; 
		}
	} 

	mui_load_icos();
	//指向lcd
	gui_phy.read_point=LCD_ReadPoint;
	gui_phy.draw_point=LCD_Fast_DrawPoint;
	gui_phy.lcdwidth=lcddev.width;
	gui_phy.lcdheight=lcddev.height; 
	
	gui_phy.fill=LCD_Fill;		 
	gui_phy.colorfill=LCD_Color_Fill;		 
	gui_phy.back_color=BACK_COLOR;		 

}
void mui_load_icos(void)
{
	u8 i,j; 

	LCD_Fill(5,5,lcddev.width,16,BLACK);
	LCD_Fill(0,0,8,lcddev.height,BLACK);
	LCD_Fill(0,lcddev.height-8,lcddev.width,lcddev.height,BLACK);
	LCD_Fill(lcddev.width-8,0,lcddev.width,lcddev.height,BLACK);  
	gui_draw_arcrectangle(0,0,lcddev.width-4,lcddev.height-4,6,1,MUI_IN_BACKCOLOR,MUI_IN_BACKCOLOR);
	
	gui_show_strmid(0,0,96,16,RED,16,"Ht is a test");//一个字符占8个数据位，width
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			minibmp_decode(muidev.icos[i*3+j].path,muidev.icos[i*3+j].x+5,muidev.icos[i*3+j].y,muidev.icos[i*3+j].width,muidev.icos[i*3+j].height,0,0);//显示图片
 			gui_show_strmid(muidev.icos[i*3+j].x,muidev.icos[i*3+j].y+67,muidev.icos[i*3+j].width,16,MUI_FONT_COLOR,16,muidev.icos[i*3+j].name);//显示名字 		}
		}  	
	} 
}
//设置选中哪个图标
//sel:0~8代表当前页的选中ico
void mui_set_sel(u8 sel)
{
	u8 oldsel=muidev.status&0X0F;
	if(oldsel<9)
	{
		LCD_Fill(muidev.icos[oldsel].x,muidev.icos[oldsel].y,muidev.icos[oldsel].x+muidev.icos[oldsel].width,muidev.icos[oldsel].y+muidev.icos[oldsel].height,MUI_IN_BACKCOLOR);
		minibmp_decode(muidev.icos[oldsel].path,muidev.icos[oldsel].x+5,muidev.icos[oldsel].y,muidev.icos[oldsel].width,muidev.icos[oldsel].height,0,0);		
		gui_show_strmid(muidev.icos[oldsel].x,muidev.icos[oldsel].y+67,muidev.icos[oldsel].width,16,MUI_FONT_COLOR,16,muidev.icos[oldsel].name);//显示名字
	}
	muidev.status=(muidev.status&0XF0)+sel;  

	LCD_Fill(muidev.icos[sel].x,muidev.icos[sel].y,muidev.icos[sel].x+muidev.icos[sel].width,muidev.icos[sel].y+muidev.icos[sel].height,MUI_BACK_COLOR);
	minibmp_decode(muidev.icos[sel].path,muidev.icos[sel].x+5,muidev.icos[sel].y,muidev.icos[sel].width,muidev.icos[sel].height,0,0);		

  gui_show_strmid(muidev.icos[sel].x,muidev.icos[sel].y+67,muidev.icos[sel].width,16,MUI_FONT_COLOR,16,muidev.icos[sel].name);//显示名字
} 
//屏幕触摸检测
//返回值:0~8,被双击的图标编号.		    
//       0xff,没有任何图标被双击或者按下
u8 mui_touch_chk(void)
{		 
	u8 i=0xff;
	tp_dev.scan(0);//扫描																		 
	if(tp_dev.sta&TP_PRES_DOWN)//有按键被按下
	{
		muidev.status|=0X80;	//标记有有效触摸
		muidev.tpx=tp_dev.x[0];
		muidev.tpy=tp_dev.y[0];
	}else if(muidev.status&0X80)//按键松开了,并且有有效触摸
	{
		
		for(i=0;i<9;i++)
		{
			if((muidev.tpx>muidev.icos[i].x)&&(muidev.tpx<muidev.icos[i].x+muidev.icos[i].width)&&(muidev.tpx>muidev.icos[i].x)&&
			   (muidev.tpy<muidev.icos[i].y+muidev.icos[i].height))
			{
				break;//得到选中的编号	
			}
		}

		if(i<9)
		{
			if(i!=(muidev.status&0X0F))	//选中了不同的图标,切换图标
			{
				mui_set_sel(i);
				i=0xff;
			}else 
			{ 
				muidev.status|=0X0F;//清零选中的图标
			}
		}else i=0xff;//无效的点按.
		muidev.status&=0X7F;//清除按键有效标志
	} 	 
	return i; 
}

