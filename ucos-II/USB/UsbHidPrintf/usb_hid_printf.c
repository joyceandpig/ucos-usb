#include "usb_hid_printf.h"
#include "hw_config.h" 
#include "delay.h"
/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����_printf()����
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
 * ��������backslash
 * ����  ���жϷ�б�ܺ�������������ͣ������ݲ�ͬ������ ���Ͳ�ͬ������
 * ����  ��-char_addr ���������Ҫ��ӡ���ַ�����ʼ��ַ
 *         -send_buffer ʵ�ʷ������ݵĴ洢�ռ�
 *         -buffer_addr �����б�ĵ�ַ�ڴ����ַ�����ʲôλ��
 *         
 * ���  ����
 * ����  ���ж�����ַ�����ָ��ָ���λ��
 * ����  ����_printf()����
 */
static uint8_t backslash(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr)
{
	switch ( *++char_addr )           //�жϷ�б�ܺ������������ʲô
	{			
		case 'r':	*(send_buffer + buffer_addr++) = 0x0d;char_addr++;break;			//�س���								
		case 'n':	*(send_buffer + buffer_addr++) = 0x0a;char_addr++;break;			//���з�				
		default: char_addr++;break;
	}
	return buffer_addr;
}
/*
 * ��������packbagsend
 * ����  �����ݰ��Ĳ���뷢�ͣ�����ַ�������С��64�ֽڣ�����뷢��buffer�ڣ�����Ѿ�����64�ֽ����ȷ���buffer�ڵ�64�ֽ�
 * ����  ��-char_addr ���������Ҫ��ӡ���ַ�����ʼ��ַ
 *         -send_buffer ʵ�ʷ������ݵĴ洢�ռ�
 *         -buffer_addr �����б�ĵ�ַ�ڴ����ַ�����ʲôλ��
 *         
 * ���  ����
 * ����  ���ж�����ַ�����ָ��ָ���λ��
 * ����  ����_printf()����
 */
static uint8_t packbagsend(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr)
{
	if (buffer_addr++ < 64)          //�������С��64�ֽ������һ������buffer
	{
		*(send_buffer+ (buffer_addr)-1) = *char_addr;
	}
	else                            //������ݶ���64�ֽڣ����ȷ���ǰ64�ֽ����ݣ�Ȼ����շ���buffer�Խ���ʣ���ַ�
	{
		USB_SendData(send_buffer,64);
		memset(send_buffer,'\0',64);    //���buffer
		buffer_addr = 0;              //�������
	}
	return buffer_addr;
}
/*
 * ��������Hid_printf
 * ����  ��ͨ��HID��ӡ�ַ�������printf����
 * ����  ��-Data ������ַ���
 *        
 *              
 * ���  ����
 * ����  ����
 * ����  ����_printf()����
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
	
//	while ( *Data != '\n')     // �ж��Ƿ񵽴��ַ���������
	while ( *Data != '\0')
	{				                          
		if ( *Data == 0x5c )  //��б�ܷ���'\' 
		{									  
				send_count =backslash(Data,send_buf,send_count);		 
		}
	  else if ( *Data == '%')    //�ж�%�������������ʲô
		{									  //
			switch ( *++Data )
			{			
			case 's':										 //�ַ���
				s = va_arg(ap, const char *);
				for ( ; *s!= 0; s++) 
					send_buf[send_count++] = *s;	
					Data++;			
				break;	
			case 'd':										//ʮ����
				d = va_arg(ap, int);
				itoa(d, (char *)send_buf, 10);
				Data++;
				break;
			default:
				Data++;
				break;
			}		 
		} /* end of else if */
		else                          //��������������ʾ��ͨ�ַ�����Ϣ
		{
			send_count = packbagsend(Data,send_buf,send_count);
		  Data++;                          //�������ַ�����ַָ������ƶ�һλ
		}
	}
	USB_SendData(send_buf,64); //�����ַ�����ֵ��ѯ��ϣ��ͷ��͵õ����ַ�������С��64�ֽڻ��߶���64�ֽڵĲ�ֺ�ʣ�µģ�
	send_count = 0;
	memset(send_buf,'\0',64);
	//delay_ms(10);
}
