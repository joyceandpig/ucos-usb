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
    0x12,                       /*bLength ���������ĳ���*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType �������������� �豸�������ػ���������������*/
    0x00,                       /*bcdUSB 2�ֽ�  ���豸ʹ�õ�usbЭ��汾*/
    0x02,
    0x00,                       /*bDeviceClass    �����*/
    0x00,                       /*bDeviceSubClass   �������*/
    0x00,                       /*bDeviceProtocol   �豸��ʹ�õ�Э��*/
    0x40,                       /*bMaxPacketSize 64    �˵�0������ ȡֵ��Ϊ8 16 32 64*/
    0x88,                       /*idVendor (0x0483)  С��ģʽ BCD�� ���ֽ���ǰ 2�ֽ� ����ID*/
    0x88,
    0x00,                       /*idProduct = 0x5710   2�ֽ�  ��ƷID*/
    0x06,
    0x00,                       /*bcdDevice rel. 2.00   2�ֽ�  �豸�汾��*/
    0x02,
    1,                          /*Index of string descriptor describing   �ַ���������ȡ��ͬ��
                                                  manufacturer   ���������ַ�������*/
    2,                          /*Index of string descriptor describing
                                                 product         ������Ʒ�ַ�������*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number   ��Ʒ���к��ַ�������*/
    0x01                        /*bNumConfigurations   ���ܵ�������*/
  }
  ; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t HID_Joystick_ConfigDescriptor[HID_JOYSTICK_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size ������������Ϊ9���ֽ�*/
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration  ����������Ϊ0x02*/
    HID_JOYSTICK_SIZ_CONFIG_DESC,   //�������������ϳ���  һ��34�ֽ�  2�ֽڱ�ʾ
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface  ��������֧�ֵĽӿ���*/
    0x01,         /*bConfigurationValue: Configuration value    �����õ�ֵ*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration      ���������õ��ַ���������ֵ ��Ϊ0��ʾû���ַ���*/
    0xE0,         /*bmAttributes: Self powered               ���豸�����ԣ�D7������Ĭ��Ϊ1  
																															D6��ʾ�豸���緽ʽ��1���Թ����   0����Ҫ���߹���
																															D5��ʾ�Ƿ�֧��Զ�̻��ѣ� 1��֧��Զ�̻���  0����֧��
																															D4-D0������Ĭ��Ϊ0*/
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus   �豸����ĵ�������λΪ2ma��һ���ͱ�ʾ2ma�����500ma*/

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size �ӿ����������� 9 */
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type  �ӿ����������� 0x04 */
    0x00,         /*bInterfaceNumber: Number of Interface     �ýӿڵı�ţ�����0��ʼ��*/
    0x00,         /*bAlternateSetting: Alternate setting    �ýӿڵı��ñ��  */
    0x02,         /*bNumEndpoints                           �ýӿ���ʹ�õĶ˵���  ������0�˵�  ��Ϊ0��ʾû�з�0�˵�*/
    0x03,         /*bInterfaceClass: HID 										�ýӿ���ʹ�õ���*/
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot  0x01�ýӿ���ʹ�õ����� 1��֧����������*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse 0x02�ýӿ���ʹ�õ�Э��*/
    0,            /*iInterface: Index of string descriptor   �����ýӿڵ��ַ���������ֵ*/
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size          HID�����ĳ���*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID						HID��������  0x21*/
    0x00,         /*0bcdHID: HID Class Spec release number	HID���Э��汾 2�ֽڱ�ʾ*/
    0x01,
    0x00,         /*bCountryCode: Hardware target country  �豸���õĹ��Ҵ��� �����Ļ�Ϊ21*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow  �¼������������� ����Ϊ1����/����������*/
    0x22,         /*bDescriptorType																							�¼������������ͣ�22������������
																																																	 23������������*/
    HID_JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor   �¼������������ĳ��ȣ�2�ֽ�*/
    0x00,
    /******************** Descriptor of Joystick Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size    �˵��������ĳ���*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:			�˵�������������*/

    0x81,          /*bEndpointAddress: Endpoint Address (IN)  �ö˵��ַ��D7��ʾ���䷽��1������ 0�����
																															D6-D4������Ĭ��Ϊ0
																															D3-D0Ϊ�˵��*/
    0x03,          /*bmAttributes: Interrupt endpoint         �ö˵�����ԣ� D7-D2������Ĭ��Ϊ0
																															D1-D0��ʾ�˵㴫�����ͣ�0�����ƴ��� 1����ʱ����
																																											2���������� 3���жϴ���*/
    0x40,          /*wMaxPacketSize: 4 Byte max               0x04�ö˵�֧�ֵ��������� 2�ֽڱ�ʾ*/
    0x00,
    0x0A,          /*bInterval: Polling Interval (32 ms)			�˿ڲ�ѯʱ�䣬�����жϴ�����ǲ�ѯ֡���ʱ��
																															���������������ͣ����ֶ�û������*/
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
/*	ǰ׺1byte bTag��7-4�� bType��3 2�� bSize��1 0��
							����Ŀ����  ��Ŀ����     ǰ׺����ֽ��� 0 1 2 4
													0����Ŀ�����롢��������ԡ����ϡ��ؼ���
													1ȫ��:ѡ����;ҳusage���������ݳ��ȡ�����������ID
													2�ֲ�  
													3����  	*/
const uint8_t HID_Joystick_ReportDescriptor[HID_JOYSTICK_SIZ_REPORT_DESC] =
  {										
//		//����Ŀ���ÿ����������һ�������ֶΣ��ֶδ�С��report_size��������report_count�����趨����Ŀ�����ֶ�
//		//����Ŀ������ڲ�������Ŀ��
////http://www.cnblogs.com/wzh206/archive/2010/06/13/1757694.html		
//		// ���������������ÿ������ռ��һ��λ���ֶΣ���report size = 1��report count = 3����ʾ��3����������Ŀ��
//		//ÿ����Ŀ�仯ռ��һ��λ.��ô��걨�����������λ
//    0x05,          /*Usage Page(Generic Desktop) ����һ��ȫ����Ŀ��bTypeΪ1����ѡ����;ҳΪ ��ͨ���棬
//										�����һ�����ݣ�bsizeΪ1��*/
//    0x01,
//    0x09,          /*Usage(Mouse)����һ���ֲ���Ŀ��bTypeΪ2����˵����������Ӧ�ü�����;�������*/
//    0x02,
//    0xA1,          /*Collection(Logical)  ����һ������ĿbtypeΪ0�������ϣ��������0x01��ʾ�ü���
//									��һ��Ӧ�ü��ϣ�����������ǰ����;ҳ����;����Ϊ��ͨ�������*/
//    0x01,
//				0x09,          /*Usage(Pointer) ����һ���ֲ���Ŀ��˵����;Ϊָ�뼯�� ָ���豸*/
//				0x01,
//				/* 8 */
//				0xA1,          /*Collection(Linked) ��������Ŀ�����ϣ������0x00��ʾ�ü����ʺ�һ�������ϣ���;��
//												ǰ��ľֲ���Ŀ����Ϊָ�뼯��*/
//				0x00,
//						0x05,          /*Usage Page(Buttons) ȫ����Ŀ��ѡ����;ҳΪ������button page0x09��*/
//						0x09,
//						0x19,          /*Usage Minimum(1) �ֲ���Ŀ����;��СֵΪ1��ʵ������������*/
//						0x01,
//						0x29,          /*Usage Maximum(3) �ֲ���Ŀ����;��СֵΪ3��ʵ����������м� 1��ʾ�����2��ʾ�Ҽ���3�м�*/
//						0x03,
//						/* 16 */
//						//logic num��˵��ÿ�������ֶε���ֵ��Χ��mini��-1��max��1��˵��ֻ�����-1 0 1������ֵ��������Ҫ������λ����ʾ
//						//0b11��ʾ-1 0b00��ʾ0 0b01��ʾ1 ��ôreport_size��Ӧ��Ϊ2��������������ֻ��0 1�������֣�����ֻ��Ҫreport_sizeΪ0�Ϳ��Ա�ʾ
//						//report_count��ʾ�ж��ٸ�������
//						0x15,          /*Logical Minimum(0)ȫ����Ŀ��˵�����ص������߼�ֵ���������Ƿ��ص��������ֵ����СΪ0
//														��Ϊ�����á�λ������ʾһ�������������СΪ0�����Ϊ1*/
//						0x00,
//						0x25,          /*Logical Maximum(1) ȫ����Ŀ��˵���߼�ֵ���Ϊ1*/
//						0x01,
//						0x95,          /*Report Count(3) ȫ����Ŀ��˵�������������Ϊ3�� 3bits*/
//						0x03,
//						0x75,          /*Report Size(1) ȫ����ģ�� ˵��ÿ��������ĳ���Ϊ1��λ*/
//						0x01,
//						/* 24 */
//						0x81,          /*Input(Variable) ����Ŀ��˵����3������Ϊ1�������������ͳ�����ǰ������ȫ����Ŀ������
//														������Ϊ���룬����Ϊdata,var,bas.data��ʾ��Щ�����ǿ��Ա䶯��var��ʾ��Щ�����Ƕ����ı���
//														����ÿ�����ʾһ����˼��bas��ʾ����ֵ�����ս�����ǵ�һ��������λbit0��ʾ������������Ƿ���
//														�ڶ���������Ϊbit1��ʾ����2���Ҽ����Ƿ��£�������������λbit2��ʾ����3���м����Ƿ���
//														*/
//						0x02,
//						//���5��bit������һ���ֽ�
//						0x95,          /*Report Count(1) ȫ����Ŀ������������Ϊ1��*/
//						0x01,
//						0x75,          /*Report Size(5) ȫ����Ŀ��ÿ�������򳤶�Ϊ5λ*/
//						0x05,
//						0x81,          /*Input(Constant,Array) ����Ŀ�������ã���ǰ������ȫ����Ŀ��֪����Ϊ5����Ϊ1��
//														��������Ϊ���������ص�����һֱ��0�������ֻ��Ϊ�˴���1�ֽڣ�ǰ����������λ��������һЩ���ݣ�û��ʵ����;*/
//						0x01,
//						/* 32 */
//						0x05,          /*Usage Page(Generic Desktop) ȫ����Ŀ����;ҳΪ��ͨ����*/
//						0x01,
//						0x09,          /*Usage(X axis) �ֲ���Ŀ����;Ϊx��*/
//						0x30,
//						0x09,          /*Usage(Y axis) �ֲ���Ŀ����;Ϊy��*/
//						0x31,
//						0x09,          /*Usage(Wheel) �ֲ���Ŀ����;Ϊ����*/
//						0x38,
//						/* 40 */
//						0x15,          /*Logical Minimum(-127) ��������ȫ����Ŀ��˵�����ص��߼���С�����ֵ����Ϊ���ָ���ƶ�ͨ�������ֵ��ʾ��
//													ָ���ƶ�ʱ��ֻ�����ƶ����������ƶ���xֵΪ���������ƶ�yΪ������������ʱֵΪ��*/
//						0x81,
//						0x25,          /*Logical Maximum(127)*/
//						0x7F,
//						0x75,          /*Report Size(8) ȫ����Ŀ�������򳤶�Ϊ8λ*/
//						0x08,
//						0x95,          /*Report Count(3)ȫ����Ŀ��������ĸ���Ϊ3��*/
//						0x03,
//						/* 48 */
//						0x81,          /*Input(Variable, Relative) ����Ŀ������8λ�����������õģ�����Ϊdata��var��rel
//														��һ��8λ��ʾx�ᣬ�ڶ���8λ��ʾy�ᣬ������8λ��ʾ���֣�rel��ʾ��Щֵ�������ֵ*/
//						0x06,
//				0xC0,          /*End Collection  �ر�������*/
//				
//				0x09,   //�ֲ���Ŀ��; �˶����ѣ�ȫ����Ŀ������Ȼ��0x05 0x01 (desktop)
//				0x3c,
//				0x05, //����һ��ȫ����Ŀ��;ҳ�������û��Զ���
//				0xff,
//				0x09, //����Ŀ
//				/* 56 */
//				0x01,
//				0x15,//ȫ����Ŀ��logic_minnum 0
//				0x00,
//				0x25,//ȫ����Ŀ��logic_maxnum 1 ��0��1�߼�ֵ�ó�������ֻ��1λ
//				0x01,
//				0x75,//report_size 1
//				0x01,
//				0x95,//report_count 2
//				/* 64 */
//				0x02,
//				0xb1,//����Ŀ��feature �����������顢����ѡ״̬
//				0x22,
//				0x75,//ȫ����Ŀ��report_size 6
//				0x06,
//				0x95,  //ȫ����Ŀ��report_count 1
//				0x01,
//				0xb1, //����Ŀ��feature ����
//				/* 72 */
//				0x01,
//    0xc0  //�ر����Ӧ�ü���
		
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
  ; /* LangID = 0x0409: U.S. English  ��ʽӢ�� һ��ֻ�����*/
//�����ַ���
const u8 HID_Joystick_StringVendor[HID_JOYSTICK_SIZ_STRING_VENDOR] =	    
{
	HID_JOYSTICK_SIZ_STRING_VENDOR, /* Size of manufaturer string */
	USB_STRING_DESCRIPTOR_TYPE,           /* bDescriptorType = String descriptor */
	/* Manufacturer: "����������ӿƼ����޹�˾"  UNICODE ������ַ��� 2�ֽڱ�ʾһ���ַ� ����Ӣ�ģ���asciiǰ
			\u6210\u90fd\u6dde\u5e78\u79d1\u6280\u6709\u9650\u8d23\u4efb\u516c\u53f8	
																				��1�ֽڵ�0���Ϊ2�ֽ�*/
	0x10,0x62,//��
	0xfd,0x90,//��
	0xde,0x6d,//��
	0x78,0x5e,//��
	0xd1,0x79,//��
	0x80,0x62,//��
	0x09,0x67,//��
	0x50,0x96,//��
	0x23,0x8d,//��
	0xfb,0x4e,//��
	0x6c,0x51,//��
	0xf8,0x53,//˾
//	0X7F,0X5E,//��
//	0XDE,0X5D,//��
//	0X1F,0X66,//��
//	0XFC,0X7F,//��
//	0X35,0X75,//��
//	0X50,0X5B,//��
//	0XD1,0X79,//��
//	0X62,0X80,//��
//	0X09,0X67,//��
//	0X50,0X96,//��
//	0X6C,0X51,//��
//	0XF8,0X53,//˾	  
};
//ʹ��UNICODE���� ��Ʒ�ַ���
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
	'N', 0,//ALIENTEK  С��ģʽ  ��λ��ǰ
	' ', 0, 
	'U', 0,
	'S', 0, 
	'B', 0,//\u6570\u636e\u4f20\u8f93
	0X70,0X65,//��
	0X6e,0X63,//��
  0x20,0x4f,//��
	0x93,0x8f,//��
};
//��Ʒ���к��ַ���
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
	/* Manufacturer: "����������ӿƼ����޹�˾" */
		0x10,0x62,//��
	0xfd,0x90,//��
	0xde,0x6d,//��
	0x78,0x5e,//��
	0xd1,0x79,//��
	0x80,0x62,//��
	0x09,0x67,//��
	0x50,0x96,//��
	0x23,0x8d,//��
	0xfb,0x4e,//��
	0x6c,0x51,//��
	0xf8,0x53,//˾
//	0X7F,0X5E,//��
//	0XDE,0X5D,//��
//	0X1F,0X66,//��
//	0XFC,0X7F,//��
//	0X35,0X75,//��
//	0X50,0X5B,//��
//	0XD1,0X79,//��
//	0X62,0X80,//��
//	0X09,0X67,//��
//	0X50,0X96,//��
//	0X6C,0X51,//��
//	0XF8,0X53,//˾	  
};
const u8 MassStorage_Joystick_StringProduct[MassStorage_JOYSTICK_SIZ_STRING_PRODUCT] =
  {
    MassStorage_JOYSTICK_SIZ_STRING_PRODUCT,
    0x03,
//    /* Product name: "ALIENTEK SD��������" */
//    'A', 0, 'L', 0, 'I', 0, 'E', 0, 'N', 0, 'T', 0, 'E', 0, 'K', 0, ' ', 0, 'S', 0,
//	'D', 0,0X61,0X53,0XFB,0X8B,0X61,0X53,0X68,0X56
	'S', 0, 
	'U', 0, 
	'N', 0, 
	'S', 0, 
	'H', 0, 
	'E', 0, 
	'E', 0, 
	'N', 0,//ALIENTEK  С��ģʽ  ��λ��ǰ
	' ', 0, 
	0x27,0x59,//��
	0xb9,0x5b,//��
	0xcf,0x91,//��
	0x58,0x5b,//��
	0xa8,0x50,//��
	0x68,0x56,//��
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

