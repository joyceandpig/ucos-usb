/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Joystick Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t HID_Joystick_DeviceDescriptor[HID_JOYSTICK_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength ¸ÃÃèÊö·ûµÄ³¤¶È*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType ¸ÃÃèÊö·ûµÄÀàĞÍ Éè±¸ÃèÊö·ûÄØ»¹ÊÇÅäÖÃÃèÊö·ûµÈ*/
    0x00,                       /*bcdUSB 2×Ö½Ú  ±¾Éè±¸Ê¹ÓÃµÄusbĞ­Òé°æ±¾*/
    0x02,
    0x00,                       /*bDeviceClass    Àà´úÂë*/
    0x00,                       /*bDeviceSubClass   ×ÓÀà´úÂë*/
    0x00,                       /*bDeviceProtocol   Éè±¸ËùÊ¹ÓÃµÄĞ­Òé*/
    0x40,                       /*bMaxPacketSize 64    ¶Ëµã0×î´ó°ü³¤ È¡Öµ¿ÉÎª8 16 32 64*/
    0x88,                       /*idVendor (0x0483)  Ğ¡¶ËÄ£Ê½ BCDÂë µÍ×Ö½ÚÔÚÇ° 2×Ö½Ú ³§ÉÌID*/
    0x88,
    0x00,                       /*idProduct = 0x5710   2×Ö½Ú  ²úÆ·ID*/
    0x06,
    0x00,                       /*bcdDevice rel. 2.00   2×Ö½Ú  Éè±¸°æ±¾ºÅ*/
    0x02,
    1,                          /*Index of string descriptor describing   ×Ö·ûË÷Òı²»ÄÜÈ¡ÏàÍ¬µÄ
                                                  manufacturer   ÃèÊö³§ÉÌ×Ö·û´®Ë÷Òı*/
    2,                          /*Index of string descriptor describing
                                                 product         ÃèÊö²úÆ·×Ö·û´®Ë÷Òı*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number   ²úÆ·ĞòÁĞºÅ×Ö·û´®Ë÷Òı*/
    0x01                        /*bNumConfigurations   ¿ÉÄÜµÄÅäÖÃÊı*/
  }
  ; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t HID_Joystick_ConfigDescriptor[HID_JOYSTICK_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size ¸ÃÃèÊö·û³¤¶ÈÎª9¸ö×Ö½Ú*/
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration  ÅäÖÃÃèÊö·ûÎª0x02*/
    HID_JOYSTICK_SIZ_CONFIG_DESC,   //ÅäÖÃÃèÊö·û¼¯ºÏ³¤¶È  Ò»¹²34×Ö½Ú  2×Ö½Ú±íÊ¾
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface  ¸ÃÅäÖÃËùÖ§³ÖµÄ½Ó¿ÚÊı*/
    0x01,         /*bConfigurationValue: Configuration value    ¸ÃÅäÖÃµÄÖµ*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration      ÃèÊö¸ÃÅäÖÃµÄ×Ö·û´®µÄË÷ÒıÖµ ÈôÎª0±íÊ¾Ã»ÓĞ×Ö·û´®*/
    0xE0,         /*bmAttributes: Self powered               ¸ÃÉè±¸µÄÊôĞÔ£¬D7±£Áô£¬Ä¬ÈÏÎª1  
																															D6±íÊ¾Éè±¸¹©µç·½Ê½£¬1£º×Ô¹©µçµÄ   0£»ĞèÒª×ÜÏß¹©µç
																															D5±íÊ¾ÊÇ·ñÖ§³ÖÔ¶³Ì»½ĞÑ£¬ 1£ºÖ§³ÖÔ¶³Ì»½ĞÑ  0£º²»Ö§³Ö
																															D4-D0±£Áô£¬Ä¬ÈÏÎª0*/
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus   Éè±¸ËùĞèµÄµçÁ÷£¬µ¥Î»Îª2ma£¬Ò»¸ö¾Í±íÊ¾2ma£¬×î´ó500ma*/

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size ½Ó¿ÚÃèÊö·û³¤¶È 9 */
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type  ½Ó¿ÚÃèÊö·ûÀàĞÍ 0x04 */
    0x00,         /*bInterfaceNumber: Number of Interface     ¸Ã½Ó¿ÚµÄ±àºÅ£¬£¬´Ó0¿ªÊ¼µÄ*/
    0x00,         /*bAlternateSetting: Alternate setting    ¸Ã½Ó¿ÚµÄ±¸ÓÃ±àºÅ  */
    0x02,         /*bNumEndpoints                           ¸Ã½Ó¿ÚËùÊ¹ÓÃµÄ¶ËµãÊı  ²»°üÀ¨0¶Ëµã  ÈôÎª0±íÊ¾Ã»ÓĞ·Ç0¶Ëµã*/
    0x03,         /*bInterfaceClass: HID 										¸Ã½Ó¿ÚËùÊ¹ÓÃµÄÀà*/
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot  0x01¸Ã½Ó¿ÚËùÊ¹ÓÃµÄ×ÓÀà 1£ºÖ§³ÖÒıµ¼Æô¶¯*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse 0x02¸Ã½Ó¿ÚËùÊ¹ÓÃµÄĞ­Òé*/
    0,            /*iInterface: Index of string descriptor   ÃèÊö¸Ã½Ó¿ÚµÄ×Ö·û´®µÄË÷ÒıÖµ*/
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size          HIDÃèÊöµÄ³¤¶È*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID						HIDÃèÊöÀàĞÍ  0x21*/
    0x00,         /*0bcdHID: HID Class Spec release number	HIDÀàµÄĞ­Òé°æ±¾ 2×Ö½Ú±íÊ¾*/
    0x01,
    0x00,         /*bCountryCode: Hardware target country  Éè±¸ÊÊÓÃµÄ¹ú¼Ò´úÂë ÃÀ¹úµÄ»°Îª21*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow  ÏÂ¼¶ÃèÊö·ûµÄÊıÁ¿ ÖÁÉÙÎª1±¨¸æ/ÎïÀíÃèÊö·û*/
    0x22,         /*bDescriptorType																							ÏÂ¼¶ÃèÊö·ûµÄÀàĞÍ£¬22£º±¨¸æÃèÊö·û
																																																	 23£ºÎïÀíÃèÊö·û*/
    HID_JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor   ÏÂ¼¶±¨¸æÃèÊö·ûµÄ³¤¶È£¬2×Ö½Ú*/
    0x00,
    /******************** Descriptor of Joystick Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size    ¶ËµãÃèÊö·ûµÄ³¤¶È*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:			¶ËµãÃèÊö·ûµÄÀàĞÍ*/

    0x81,          /*bEndpointAddress: Endpoint Address (IN)  ¸Ã¶ËµãµØÖ·£¬D7±íÊ¾´«Êä·½Ïò£¬1£ºÊäÈë 0£ºÊä³ö
																															D6-D4±£Áô£¬Ä¬ÈÏÎª0
																															D3-D0Îª¶ËµãºÅ*/
    0x03,          /*bmAttributes: Interrupt endpoint         ¸Ã¶ËµãµÄÊôĞÔ£¬ D7-D2±£Áô£¬Ä¬ÈÏÎª0
																															D1-D0±íÊ¾¶Ëµã´«ÊäÀàĞÍ£¬0£º¿ØÖÆ´«Êä 1£ºµÈÊ±´«Êä
																																											2£ºÅúÁ¿´«Êä 3£ºÖĞ¶Ï´«Êä*/
    0x40,          /*wMaxPacketSize: 4 Byte max               0x04¸Ã¶ËµãÖ§³ÖµÄ×î´ó°ü³¤¶È 2×Ö½Ú±íÊ¾*/
    0x00,
    0x0A,          /*bInterval: Polling Interval (32 ms)			¶Ë¿Ú²éÑ¯Ê±¼ä£¬¶ÔÓÚÖĞ¶Ï´«Êä¾ÍÊÇ²éÑ¯Ö¡¼ä¸ôÊ±¼ä
																															¶ÔÓÚÆäËû´«ÊäÀàĞÍ£¬¸Ã×Ö¶ÎÃ»ÓĞÒâÒå*/
    /* 34 */
		
		0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
			/*	Endpoint descriptor type */
    0x01,	/* bEndpointAddress: */
			/*	Endpoint Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x40,	/* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x0A,	/* bInterval: Polling Interval (10 ms) */
  }
  ; /* MOUSE_ConfigDescriptor */
	//   					8 4 2 1         8  4        2  1
/*	Ç°×º1byte bTag£¨7-4£© bType£¨3 2£© bSize£¨1 0£©
							¸ÃÌõÄ¿¹¦ÄÜ  ÌõÄ¿ÀàĞÍ     Ç°×ººó¸ú×Ö½ÚÊı 0 1 2 4
													0Ö÷ÌõÄ¿£ºÊäÈë¡¢Êä³ö¡¢ÌØĞÔ¡¢¼¯ºÏ¡¢¹Ø¼¯ºÏ
													1È«¾Ö:Ñ¡ÔñÓÃÍ¾Ò³usage£¬¶¨ÒåÊı¾İ³¤¶È¡¢ÊıÁ¿¡¢±¨¸æID
													2¾Ö²¿  
													3±£Áô  	*/
const uint8_t HID_Joystick_ReportDescriptor[HID_JOYSTICK_SIZ_REPORT_DESC] =
  {										
//		//Ö÷ÏîÄ¿»á¶ÔÃ¿¸ö²Ù×÷²úÉúÒ»¸ö±¨¸æ×Ö¶Î£¬×Ö¶Î´óĞ¡ÓÉreport_size¾ö¶¨£¬¶øreport_countÓÃÀ´Éè¶¨Ö÷ÏîÄ¿±¨¸æ×Ö¶Î
//		//µÄÊıÄ¿£¬ÆäµÈÓÚ²Ù×÷µÄÊıÄ¿¡£
////http://www.cnblogs.com/wzh206/archive/2010/06/13/1757694.html		
//		// Êó±êÊÇÈı¸ö°´¼ü£¬Ã¿¸ö°´¼üÕ¼ÓÃÒ»¸öÎ»µÄ×Ö¶Î£¬Ôòreport size = 1£¬report count = 3£¬±íÊ¾ÓĞ3¸ö²Ù×÷µÄÏîÄ¿£¬
//		//Ã¿¸öÏîÄ¿±ä»¯Õ¼ÓÃÒ»¸öÎ».ÄÇÃ´Êó±ê±¨¸æ·û¾ÍÓĞÈı¸öÎ»
//    0x05,          /*Usage Page(Generic Desktop) ÕâÊÇÒ»¸öÈ«¾ÖÌõÄ¿£¨bTypeÎª1£©£¬Ñ¡ÔñÓÃÍ¾Ò³Îª ÆÕÍ¨×ÀÃæ£¬
//										ºóÃæ¸úÒ»¸öÊı¾İ£¨bsizeÎª1£©*/
//    0x01,
//    0x09,          /*Usage(Mouse)ÕâÊÇÒ»¸ö¾Ö²¿ÌõÄ¿£¨bTypeÎª2£©£¬ËµÃ÷½ÓÏÂÀ´µÄÓ¦ÓÃ¼¯ºÏÓÃÍ¾ÓÃÓÚÊó±ê*/
//    0x02,
//    0xA1,          /*Collection(Logical)  ÕâÊÇÒ»¸öÖ÷ÌõÄ¿btypeÎª0£¬¿ª¼¯ºÏ£¬ºóÃæ¸úµÄ0x01±íÊ¾¸Ã¼¯ºÏ
//									ÊÇÒ»¸öÓ¦ÓÃ¼¯ºÏ£¬ËûµÄĞÔÖÊÔÚÇ°ÃæÓÃÍ¾Ò³ºÍÓÃÍ¾¶¨ÒåÎªÆÕÍ¨×ÀÃæÊó±ê*/
//    0x01,
//				0x09,          /*Usage(Pointer) ÕâÊÇÒ»¸ö¾Ö²¿ÌõÄ¿£¬ËµÃ÷ÓÃÍ¾ÎªÖ¸Õë¼¯ºÏ Ö¸ÕëÉè±¸*/
//				0x01,
//				/* 8 */
//				0xA1,          /*Collection(Linked) ÕâÊÇÖ÷ÌõÄ¿¿ª¼¯ºÏ£¬ºóÃæ¸ú0x00±íÊ¾¸Ã¼¯ºÏÊÊºÏÒ»¸öÎïÀí¼¯ºÏ£¬ÓÃÍ¾ÓÉ
//												Ç°ÃæµÄ¾Ö²¿ÌõÄ¿¶¨ÒåÎªÖ¸Õë¼¯ºÏ*/
//				0x00,
//						0x05,          /*Usage Page(Buttons) È«¾ÖÌõÄ¿£¬Ñ¡ÔñÓÃÍ¾Ò³Îª°´¼ü£¨button page0x09£©*/
//						0x09,
//						0x19,          /*Usage Minimum(1) ¾Ö²¿ÌõÄ¿£¬ÓÃÍ¾×îĞ¡ÖµÎª1£¬Êµ¼ÊÉÏÊÇÊó±ê×ó¼ü*/
//						0x01,
//						0x29,          /*Usage Maximum(3) ¾Ö²¿ÌõÄ¿£¬ÓÃÍ¾×îĞ¡ÖµÎª3£¬Êµ¼ÊÉÏÊÇÊó±êÖĞ¼ä 1±íÊ¾×ó¼ü£¬2±íÊ¾ÓÒ¼ü£¬3ÖĞ¼ü*/
//						0x03,
//						/* 16 */
//						//logic numÊÇËµÃ÷Ã¿¸ö±¨¸æ×Ö¶ÎµÄÊıÖµ·¶Î§£¬mini£¨-1£©max£¨1£©ËµÃ÷Ö»»á³öÏÖ-1 0 1ÈıÖÖÊıÖµ£¬ËùÒÔĞèÒªÓÃÁ½¸öÎ»À´±íÊ¾
//						//0b11±íÊ¾-1 0b00±íÊ¾0 0b01±íÊ¾1 ÄÇÃ´report_size¾ÍÓ¦¸ÃÎª2£¬ÔÚÒÔÏÂÀı×ÓÖĞÖ»ÓĞ0 1Á½ÖÖÊı×Ö£¬ËùÒÔÖ»ĞèÒªreport_sizeÎª0¾Í¿ÉÒÔ±íÊ¾
//						//report_count±íÊ¾ÓĞ¶àÉÙ¸ö²Ù×÷Ïî
//						0x15,          /*Logical Minimum(0)È«¾ÖÌõÄ¿£¬ËµÃ÷·µ»ØµÄÊı¾İÂß¼­Öµ£¨¾ÍÊÇÎÒÃÇ·µ»ØµÄÊı¾İÓòµÄÖµ£©×îĞ¡Îª0
//														ÒòÎªÕâÀïÓÃ¡°Î»¡±À´±íÊ¾Ò»¸öÊı¾İÓò£¬Òò´Ë×îĞ¡Îª0£¬×î´óÎª1*/
//						0x00,
//						0x25,          /*Logical Maximum(1) È«¾ÖÌõÄ¿£¬ËµÃ÷Âß¼­Öµ×î´óÎª1*/
//						0x01,
//						0x95,          /*Report Count(3) È«¾ÖÌõÄ¿£¬ËµÃ÷Êı¾İÓòµÄÊıÁ¿Îª3¸ö 3bits*/
//						0x03,
//						0x75,          /*Report Size(1) È«¾ÖÌõÄ£¬¿ ËµÃ÷Ã¿¸öÊı¾İÓòµÄ³¤¶ÈÎª1¸öÎ»*/
//						0x01,
//						/* 24 */
//						0x81,          /*Input(Variable) Ö÷ÌõÄ¿£¬ËµÃ÷ÓĞ3¸ö³¤¶ÈÎª1µÄÊı¾İÓò£¨ÊıÁ¿ºÍ³¤¶ÈÓÉÇ°ÃæÁ½¸öÈ«¾ÖÌõÄ¿Ëù¶¨Òå£
//														ÓÃÀ´×÷ÎªÊäÈë£¬ÊôĞÔÎªdata,var,bas.data±íÊ¾ÕâĞ©Êı¾İÊÇ¿ÉÒÔ±ä¶¯£¬var±íÊ¾ÕâĞ©Êı¾İÊÇ¶ÀÁ¢µÄ±äÁ¿
//														¼´ÊÇÃ¿¸öÓë±íÊ¾Ò»¸öÒâË¼£¬bas±íÊ¾¾ø¶ÔÖµ£¬×îÖÕ½á¹û¾ÍÊÇµÚÒ»¸öÊı¾İÓòÎ»bit0±íÊ¾°´¼ü£¨×ó¼ü£©ÊÇ·ñ°´ÏÂ
//														µÚ¶ş¸öÊı¾İÓòÎªbit1±íÊ¾°´¼ü2£¨ÓÒ¼ü£©ÊÇ·ñ°´ÏÂ£¬µÚÈı¸öÊı¾İÓòÎ»bit2±íÊ¾°´¼ü3£¨ÖĞ¼ü£©ÊÇ·ñ°´ÏÂ
//														*/
//						0x02,
//						//Ìî³ä5¸öbit£¬²¹×ãÒ»¸ö×Ö½Ú
//						0x95,          /*Report Count(1) È«¾ÖÌõÄ¿£¬Êı¾İÓòÊıÁ¿Îª1¸ö*/
//						0x01,
//						0x75,          /*Report Size(5) È«¾ÖÌõÄ¿£¬Ã¿¸öÊı¾İÓò³¤¶ÈÎª5Î»*/
//						0x05,
//						0x81,          /*Input(Constant,Array) Ö÷ÌõÄ¿£¬ÊäÈëÓÃ£¬ÓÉÇ°ÃæÁ½¸öÈ«¾ÖÌõÄ¿¿ÉÖª³¤¶ÈÎª5ÊıÁ¿Îª1¸ö
//														ËûµÄÊôĞÔÎª³£Á¿£¨·µ»ØµÄÊı¾İÒ»Ö±ÊÇ0£©£¬Õâ¸öÖ»ÊÇÎªÁË´ÕÆë1×Ö½Ú£¨Ç°ÃæÓÃÁËÈı¸öÎ»£©¶øÌî³äµÄÒ»Ğ©Êı¾İ£¬Ã»ÓĞÊµ¼ÊÓÃÍ¾*/
//						0x01,
//						/* 32 */
//						0x05,          /*Usage Page(Generic Desktop) È«¾ÖÌõÄ¿£¬ÓÃÍ¾Ò³ÎªÆÕÍ¨×ÀÃæ*/
//						0x01,
//						0x09,          /*Usage(X axis) ¾Ö²¿ÌõÄ¿£¬ÓÃÍ¾ÎªxÖá*/
//						0x30,
//						0x09,          /*Usage(Y axis) ¾Ö²¿ÌõÄ¿£¬ÓÃÍ¾ÎªyÖá*/
//						0x31,
//						0x09,          /*Usage(Wheel) ¾Ö²¿ÌõÄ¿£¬ÓÃÍ¾Îª¹öÂÖ*/
//						0x38,
//						/* 40 */
//						0x15,          /*Logical Minimum(-127) ÏÂÃæÁ½¸öÈ«¾ÖÌõÄ¿£¬ËµÃ÷·µ»ØµÄÂß¼­×îĞ¡ºÍ×î´óÖµ£¬ÒòÎªÊó±êÖ¸ÕëÒÆ¶¯Í¨³£ÓÃÏà¶ÔÖµ±íÊ¾£¬
//													Ö¸ÕëÒÆ¶¯Ê±£¬Ö»·¢ËÍÒÆ¶¯Á¿¡£ÍùÓÒÒÆ¶¯£¬xÖµÎªÕı£¬ÍùÏÂÒÆ¶¯yÎªÕı£¬¹öÂÖÍùÉÏÊ±ÖµÎªÕı*/
//						0x81,
//						0x25,          /*Logical Maximum(127)*/
//						0x7F,
//						0x75,          /*Report Size(8) È«¾ÖÌõÄ¿£¬Êı¾İÓò³¤¶ÈÎª8Î»*/
//						0x08,
//						0x95,          /*Report Count(3)È«¾ÖÌõÄ¿£¬Êı¾İÓòµÄ¸öÊıÎª3¸ö*/
//						0x03,
//						/* 48 */
//						0x81,          /*Input(Variable, Relative) Ö÷ÌõÄ¿£¬Èı¸ö8Î»Êı¾İÊÇÊäÈëÓÃµÄ£¬ÊôĞÔÎªdata£¬var£¬rel
//														µÚÒ»¸ö8Î»±íÊ¾xÖá£¬µÚ¶ş¸ö8Î»±íÊ¾yÖá£¬µÚÈı¸ö8Î»±íÊ¾¹öÂÖ£¬rel±íÊ¾ÕâĞ©Öµ¶¼ÊÇÏà¶ÔÖµ*/
//						0x06,
//				0xC0,          /*End Collection  ¹Ø±ÕÎïÀí¼¯ºÏ*/
//				
//				0x09,   //¾Ö²¿ÌõÄ¿ÓÃÍ¾ ÔË¶¯»½ĞÑ£¬È«¾ÖÌõÄ¿ĞÔÖÊÈÔÈ»ÊÇ0x05 0x01 (desktop)
//				0x3c,
//				0x05, //ÕâÊÇÒ»¸öÈ«¾ÖÌõÄ¿ÓÃÍ¾Ò³£¬ÓÃÓÚÓÃ»§×Ô¶¨Òå
//				0xff,
//				0x09, //Ö÷ÌõÄ¿
//				/* 56 */
//				0x01,
//				0x15,//È«¾ÖÌõÄ¿£¬logic_minnum 0
//				0x00,
//				0x25,//È«¾ÖÌõÄ¿£¬logic_maxnum 1 ÓÉ0ºÍ1Âß¼­ÖµµÃ³öÊı¾İÓòÖ»ÓĞ1Î»
//				0x01,
//				0x75,//report_size 1
//				0x01,
//				0x95,//report_count 2
//				/* 64 */
//				0x02,
//				0xb1,//Ö÷ÌõÄ¿£¬feature £¬±äÁ¿¡¢Êı×é¡¢·ÇÓÅÑ¡×´Ì¬
//				0x22,
//				0x75,//È«¾ÖÌõÄ¿£¬report_size 6
//				0x06,
//				0x95,  //È«¾ÖÌõÄ¿£¬report_count 1
//				0x01,
//				0xb1, //Ö÷ÌõÄ¿£¬feature ³£Á¿
//				/* 72 */
//				0x01,
//    0xc0  //¹Ø±ÕÊó±êÓ¦ÓÃ¼¯ºÏ
		
		  	0x05, 0x8c, /* USAGE_PAGE (ST Page) */ 
  	0x09, 0x01, /* USAGE (Demo Kit) */ 
  	0xa1, 0x01, /* COLLECTION (Application) */ 
  	
  	// The Input report 
  	0x09,0x03, // USAGE ID - Vendor defined 
  	0x15,0x00, // LOGICAL_MINIMUM (0) 
  	0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
  	0x75,0x08, // REPORT_SIZE (8bit) 
  	0x95,0x40, // REPORT_COUNT (64Byte) 
  	0x81,0x02, // INPUT (Data,Var,Abs) 
  
  	// The Output report 
  	0x09,0x04, // USAGE ID - Vendor defined 
  	0x15,0x00, // LOGICAL_MINIMUM (0) 
  	0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255) 
  	0x75,0x08, // REPORT_SIZE (8bit) 
  	0x95,0x40, // REPORT_COUNT (64Byte) 
  	0x91,0x02, // OUTPUT (Data,Var,Abs) 
  
  	0xc0 /* END_COLLECTION */ 
 
  }
  ; /* Joystick_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t HID_Joystick_StringLangID[HID_JOYSTICK_SIZ_STRING_LANGID] =
  {
    HID_JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English  ÃÀÊ½Ó¢Óï Ò»°ãÖ»ÓÃÕâ¸ö*/
//³§ÉÌ×Ö·û´®
const u8 HID_Joystick_StringVendor[HID_JOYSTICK_SIZ_STRING_VENDOR] =	    
{
	HID_JOYSTICK_SIZ_STRING_VENDOR, /* Size of manufaturer string */
	USB_STRING_DESCRIPTOR_TYPE,           /* bDescriptorType = String descriptor */
	/* Manufacturer: "¹ãÖİĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾"  UNICODE ±àÂëµÄ×Ö·û´® 2×Ö½Ú±íÊ¾Ò»¸ö×Ö·û ÈôÊÇÓ¢ÎÄ£¬ÔÚasciiÇ°
			\u6210\u90fd\u6dde\u5e78\u79d1\u6280\u6709\u9650\u8d23\u4efb\u516c\u53f8	
																				²¹1×Ö½ÚµÄ0Ìî³äÎª2×Ö½Ú*/
	0x10,0x62,//³É
	0xfd,0x90,//¶¼
	0xde,0x6d,//äÁ
	0x78,0x5e,//ĞÒ
	0xd1,0x79,//¿Æ
	0x80,0x62,//¼¼
	0x09,0x67,//ÓĞ
	0x50,0x96,//ÏŞ
	0x23,0x8d,//Ôğ
	0xfb,0x4e,//ÈÎ
	0x6c,0x51,//¹«
	0xf8,0x53,//Ë¾
//	0X7F,0X5E,//¹ã
//	0XDE,0X5D,//Öİ
//	0X1F,0X66,//ĞÇ
//	0XFC,0X7F,//Òí
//	0X35,0X75,//µç
//	0X50,0X5B,//×Ó
//	0XD1,0X79,//¿Æ
//	0X62,0X80,//¼¼
//	0X09,0X67,//ÓĞ
//	0X50,0X96,//ÏŞ
//	0X6C,0X51,//¹«
//	0XF8,0X53,//Ë¾	  
};
//Ê¹ÓÃUNICODE±àÂë ²úÆ·×Ö·û´®
const u8 HID_Joystick_StringProduct[HID_JOYSTICK_SIZ_STRING_PRODUCT] =
{
	HID_JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	'S', 0, 
	'U', 0, 
	'N', 0, 
	'S', 0, 
	'H', 0, 
	'E', 0, 
	'E', 0, 
	'N', 0,//ALIENTEK  Ğ¡¶ËÄ£Ê½  µÍÎ»ÔÚÇ°
	' ', 0, 
	'U', 0,
	'S', 0, 
	'B', 0,//\u6570\u636e\u4f20\u8f93
	0X70,0X65,//Êı
	0X6e,0X63,//¾İ
  0x20,0x4f,//´«
	0x93,0x8f,//Êä
};
//²úÆ·ĞòÁĞºÅ×Ö·û´®
uint8_t HID_Joystick_StringSerial[HID_JOYSTICK_SIZ_STRING_SERIAL] =
  {
    HID_JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 
		'T', 0, 
		'M', 0, 
		'3', 0, 
		'2', 0
  };
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
const uint8_t MassStorage_Joystick_DeviceDescriptor[MassStorage_JOYSTICK_SIZ_DEVICE_DESC] =
{
	0x12,   /* bLength  */
	0x01,   /* bDescriptorType */
	0x00,   /* bcdUSB, version 2.00 */
	0x02,
	0x00,   /* bDeviceClass : each interface define the device class */
	0x00,   /* bDeviceSubClass */
	0x00,   /* bDeviceProtocol */
	0x40,   /* bMaxPacketSize0 0x40 = 64 */
	0x83,   /* idVendor     (0483) */
	0x04,
	0x20,   /* idProduct */
	0x57,
	0x00,   /* bcdDevice 2.00*/
	0x02,
	1,              /* index of string Manufacturer  */
	/**/
	2,              /* index of string descriptor of product*/
	/* */
	3,              /* */
	/* */
	/* */
	0x01    /*bNumConfigurations */
};
const uint8_t MassStorage_Joystick_ConfigDescriptor[MassStorage_JOYSTICK_SIZ_CONFIG_DESC] =
  {

    0x09,   /* bLength: Configuration Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    MassStorage_JOYSTICK_SIZ_CONFIG_DESC,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    /*      Configuration value */
    0x00,   /* iConfiguration: */
    /*      Index of string descriptor */
    /*      describing the configuration */
    0xC0,   /* bmAttributes: */
    /*      Self powered */
    0x32,   /* MaxPower 100 mA */

    /******************** Descriptor of Mass Storage interface ********************/
    /* 09 */
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MASS STORAGE Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent*/
    0x50,   /* nInterfaceProtocol */
    4,          /* iInterface: */
    /* 18 */
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    0x81,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00,   /*Polling interval in milliseconds */
    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x02,   /*Endpoint address (OUT, address 2) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00     /*Polling interval in milliseconds*/
    /*32*/
  };
const uint8_t MassStorage_Joystick_StringLangID[MassStorage_JOYSTICK_SIZ_STRING_LANGID] =
  {
    MassStorage_JOYSTICK_SIZ_STRING_LANGID,
    0x03,
    0x09,
    0x04
  }
  ;    /* LangID = 0x0409: U.S. English */
const u8 MassStorage_Joystick_StringVendor[MassStorage_JOYSTICK_SIZ_STRING_VENDOR] =
{
	MassStorage_JOYSTICK_SIZ_STRING_VENDOR, /* Size of manufaturer string */
	0x03,           /* bDescriptorType = String descriptor */
	/* Manufacturer: "¹ãÖİĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾" */
		0x10,0x62,//³É
	0xfd,0x90,//¶¼
	0xde,0x6d,//äÁ
	0x78,0x5e,//ĞÒ
	0xd1,0x79,//¿Æ
	0x80,0x62,//¼¼
	0x09,0x67,//ÓĞ
	0x50,0x96,//ÏŞ
	0x23,0x8d,//Ôğ
	0xfb,0x4e,//ÈÎ
	0x6c,0x51,//¹«
	0xf8,0x53,//Ë¾
//	0X7F,0X5E,//¹ã
//	0XDE,0X5D,//Öİ
//	0X1F,0X66,//ĞÇ
//	0XFC,0X7F,//Òí
//	0X35,0X75,//µç
//	0X50,0X5B,//×Ó
//	0XD1,0X79,//¿Æ
//	0X62,0X80,//¼¼
//	0X09,0X67,//ÓĞ
//	0X50,0X96,//ÏŞ
//	0X6C,0X51,//¹«
//	0XF8,0X53,//Ë¾	  
};
const u8 MassStorage_Joystick_StringProduct[MassStorage_JOYSTICK_SIZ_STRING_PRODUCT] =
  {
    MassStorage_JOYSTICK_SIZ_STRING_PRODUCT,
    0x03,
//    /* Product name: "ALIENTEK SD¿¨¶Á¿¨Æ÷" */
//    'A', 0, 'L', 0, 'I', 0, 'E', 0, 'N', 0, 'T', 0, 'E', 0, 'K', 0, ' ', 0, 'S', 0,
//	'D', 0,0X61,0X53,0XFB,0X8B,0X61,0X53,0X68,0X56
	'S', 0, 
	'U', 0, 
	'N', 0, 
	'S', 0, 
	'H', 0, 
	'E', 0, 
	'E', 0, 
	'N', 0,//ALIENTEK  Ğ¡¶ËÄ£Ê½  µÍÎ»ÔÚÇ°
	' ', 0, 
	0x27,0x59,//´ó
	0xb9,0x5b,//Èİ
	0xcf,0x91,//Á¿
	0x58,0x5b,//´æ
	0xa8,0x50,//´¢
	0x68,0x56,//Æ÷
  };

u8 MassStorage_Joystick_StringSerial[MassStorage_JOYSTICK_SIZ_STRING_SERIAL] =
  {
    MassStorage_JOYSTICK_SIZ_STRING_SERIAL,
    0x03,
    /* Serial number*/
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
  };
const u8 MassStorage_Joystick_StringInterface[MassStorage_JOYSTICK_MASS_SIZ_STRING_INTERFACE] =
  {
    MassStorage_JOYSTICK_MASS_SIZ_STRING_INTERFACE,
    0x03,
    /* Interface 0: "ST Mass" */
    'S', 0, 'T', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
  };
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

