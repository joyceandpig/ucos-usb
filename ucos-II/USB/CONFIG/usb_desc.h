/**
  ******************************************************************************
  * @file    usb_desc.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptor Header for Joystick Mouse Demo
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define JOYSTICK_SIZ_HID_DESC                   0x09
#define JOYSTICK_OFF_HID_DESC                   0x12

#define HID_JOYSTICK_SIZ_DEVICE_DESC                18
#define HID_JOYSTICK_SIZ_CONFIG_DESC                41//34
#define HID_JOYSTICK_SIZ_REPORT_DESC                33//74
#define HID_JOYSTICK_SIZ_STRING_LANGID              4
#define HID_JOYSTICK_SIZ_STRING_VENDOR              26
#define HID_JOYSTICK_SIZ_STRING_PRODUCT             34
#define HID_JOYSTICK_SIZ_STRING_SERIAL              26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09
#define ENDP1_SIZE                              0x40

#define MassStorage_JOYSTICK_SIZ_DEVICE_DESC              18
#define MassStorage_JOYSTICK_SIZ_CONFIG_DESC              32

#define MassStorage_JOYSTICK_SIZ_STRING_LANGID            4
#define MassStorage_JOYSTICK_SIZ_STRING_VENDOR            26
#define MassStorage_JOYSTICK_SIZ_STRING_PRODUCT           32
#define MassStorage_JOYSTICK_SIZ_STRING_SERIAL            26
#define MassStorage_JOYSTICK_MASS_SIZ_STRING_INTERFACE         16

typedef enum {
  Audio,//音频类
  CDC,  //通信类-虚拟串口类
  DFU,  //设备固件升级类
  HID,  //人机接口类
  MassStorage,//大容量存储设备类
  CCID,//智能卡接口设备
  Image,//图像类
  IrdaBridge,//Irda桥接设备类
  Monitor,//监视设备类
  PersonalHealthCare,//个人保健设备类
  PowerDevice,//电源设备类
  PhysicalInterface,//物理接口设备类
  Printer,//打印机类
  Video,//视频类
  TestMeasurement//测试测量类
}USBClass;

/* Exported functions ------------------------------------------------------- */
extern const uint8_t HID_Joystick_DeviceDescriptor[HID_JOYSTICK_SIZ_DEVICE_DESC];
extern const uint8_t HID_Joystick_ConfigDescriptor[HID_JOYSTICK_SIZ_CONFIG_DESC];
extern const uint8_t HID_Joystick_ReportDescriptor[HID_JOYSTICK_SIZ_REPORT_DESC];
extern const uint8_t HID_Joystick_StringLangID[HID_JOYSTICK_SIZ_STRING_LANGID];
extern const uint8_t HID_Joystick_StringVendor[HID_JOYSTICK_SIZ_STRING_VENDOR];
extern const uint8_t HID_Joystick_StringProduct[HID_JOYSTICK_SIZ_STRING_PRODUCT];
extern uint8_t HID_Joystick_StringSerial[HID_JOYSTICK_SIZ_STRING_SERIAL];


extern const uint8_t MassStorage_Joystick_DeviceDescriptor[MassStorage_JOYSTICK_SIZ_DEVICE_DESC];
extern const uint8_t MassStorage_Joystick_ConfigDescriptor[MassStorage_JOYSTICK_SIZ_CONFIG_DESC];
extern const uint8_t MassStorage_Joystick_StringLangID[MassStorage_JOYSTICK_SIZ_STRING_LANGID];
extern const u8 MassStorage_Joystick_StringVendor[MassStorage_JOYSTICK_SIZ_STRING_VENDOR];
extern const u8 MassStorage_Joystick_StringProduct[MassStorage_JOYSTICK_SIZ_STRING_PRODUCT];
extern u8 MassStorage_Joystick_StringSerial[MassStorage_JOYSTICK_SIZ_STRING_SERIAL];
extern const u8 MassStorage_Joystick_StringInterface[MassStorage_JOYSTICK_MASS_SIZ_STRING_INTERFACE];


#endif /* __USB_DESC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
