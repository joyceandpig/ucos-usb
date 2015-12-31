#include "usb_hid_printf.h"
#include "hw_config.h" 
#include "delay.h"
/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';		   
	    value *= -1; /* Make the value positive. */
	}
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	*ptr = 0;	    /* Null terminate the string. */
	return string;
}
/*
 * 函数名：backslash
 * 描述  ：判断反斜杠后面的命令字类型，并根据不同的类型 发送不同的命令
 * 输入  ：-char_addr 传入或者需要打印的字符串起始地址
 *         -send_buffer 实际发送数据的存储空间
 *         -buffer_addr 本次判别的地址在传入字符串的什么位置
 *         
 * 输出  ：无
 * 返回  ：判定后的字符串，指针指向的位置
 * 调用  ：被_printf()调用
 */
static uint8_t backslash(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr)
{
	switch ( *++char_addr )           //判断反斜杠后面的命令字是什么
	{			
		case 'r':	*(send_buffer + buffer_addr++) = 0x0d;char_addr++;break;			//回车符								
		case 'n':	*(send_buffer + buffer_addr++) = 0x0a;char_addr++;break;			//换行符				
		default: char_addr++;break;
	}
	return buffer_addr;
}
/*
 * 函数名：packbagsend
 * 描述  ：数据包的拆分与发送，如果字符串数据小于64字节，则放入发送buffer内，如果已经填满64字节则先发送buffer内的64字节
 * 输入  ：-char_addr 传入或者需要打印的字符串起始地址
 *         -send_buffer 实际发送数据的存储空间
 *         -buffer_addr 本次判别的地址在传入字符串的什么位置
 *         
 * 输出  ：无
 * 返回  ：判定后的字符串，指针指向的位置
 * 调用  ：被_printf()调用
 */
static uint8_t packbagsend(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr)
{
	if (buffer_addr++ < 64)          //如果数据小于64字节则存入一个发送buffer
	{
		*(send_buffer+ (buffer_addr)-1) = *char_addr;
	}
	else                            //如果数据多余64字节，则先发送前64字节数据，然后清空发送buffer以接收剩余字符
	{
		USB_SendData(send_buffer,64);
		memset(send_buffer,'\0',64);    //清空buffer
		buffer_addr = 0;              //清零计数
	}
	return buffer_addr;
}
/*
 * 函数名：Hid_printf
 * 描述  ：通过HID打印字符串，类printf函数
 * 输入  ：-Data 输入的字符串
 *        
 *              
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被_printf()调用
 */
void Hid_printf(uint8_t *Data, ...)
{	
//	uint8_t stop_flag=0;
	static const char *s;
	static int d;  
	uint8_t send_count = 0;	
	static uint8_t send_buf[64] = {0};
	va_list ap;
	va_start(ap, Data);
	
//	while ( *Data != '\n')     // 判断是否到达字符串结束符
	while ( *Data != '\0')
	{				                          
		if ( *Data == 0x5c )  //反斜杠符号'\' 
		{									  
				send_count =backslash(Data,send_buf,send_count);		 
		}
	  else if ( *Data == '%')    //判断%后面的命令字是什么
		{									  //
			switch ( *++Data )
			{			
			case 's':										 //字符串
				s = va_arg(ap, const char *);
				for ( ; *s!= 0; s++) 
					send_buf[send_count++] = *s;	
					Data++;			
				break;	
			case 'd':										//十进制
				d = va_arg(ap, int);
				itoa(d, (char *)send_buf, 10);
				Data++;
				break;
			default:
				Data++;
				break;
			}		 
		} /* end of else if */
		else                          //若非命令符，则表示普通字符串消息
		{
			send_count = packbagsend(Data,send_buf,send_count);
		  Data++;                          //将整个字符串地址指针向后移动一位
		}
	}
	USB_SendData(send_buf,64); //整个字符串数值查询完毕，就发送得到的字符（包括小于64字节或者多余64字节的拆分后剩下的）
	send_count = 0;
	memset(send_buf,'\0',64);
	//delay_ms(10);
}
