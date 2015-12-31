#ifndef _USB_HID_PRINTF_
#define _USB_HID_PRINTF_

#ifdef _cplusplus
	extern "C"{
#endif
#include "stm32f10x.h"
#include "stdarg.h"	
#include "string.h"	
		
		
static char *itoa(int value, char *string, int radix);
static uint8_t backslash(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr);
static uint8_t packbagsend(uint8_t *char_addr, uint8_t *send_buffer, uint8_t buffer_addr);
extern void Hid_printf(uint8_t *Data, ...);
		
#ifdef _cplusplus
}
#endif	
#endif
