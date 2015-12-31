/**
  ******************************************************************************
  * @file    usb_prop.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Joystick Mouse demo
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
#ifndef __USB_PROP_H
#define __USB_PROP_H

/* MASS Storage Requests*/
#define GET_MAX_LUN                0xFE
#define MASS_STORAGE_RESET         0xFF
#define LUN_DATA_LENGTH            1

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HID_Joystick_init(void);
void HID_Joystick_Reset(void);
void HID_Joystick_SetConfiguration(void);
void HID_Joystick_SetDeviceAddress (void);
void HID_Joystick_Status_In (void);
void HID_Joystick_Status_Out (void);
RESULT HID_Joystick_Data_Setup(uint8_t);
RESULT HID_Joystick_NoData_Setup(uint8_t);
RESULT HID_Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *HID_Joystick_GetDeviceDescriptor(uint16_t );
uint8_t *HID_Joystick_GetConfigDescriptor(uint16_t);
uint8_t *HID_Joystick_GetStringDescriptor(uint16_t);
RESULT HID_Joystick_SetProtocol(void);
uint8_t *HID_Joystick_GetProtocolValue(uint16_t Length);
RESULT HID_Joystick_SetProtocol(void);
uint8_t *HID_Joystick_GetReportDescriptor(uint16_t Length);
uint8_t *HID_Joystick_GetHIDDescriptor(uint16_t Length);


void MassStorage_Joystick_init(void);
void MassStorage_Joystick_Reset(void);
void MassStorage_Joystick_SetConfiguration(void);
void MassStorage_Joystick_ClearFeature(void);
void MassStorage_Joystick_SetDeviceAddress (void);
void MassStorage_Joystick_Status_In(void);
void MassStorage_Joystick_Status_Out (void);
RESULT MassStorage_Joystick_Data_Setup(uint8_t RequestNo);
RESULT MassStorage_Joystick_NoData_Setup(uint8_t RequestNo);
uint8_t *MassStorage_Joystick_GetDeviceDescriptor(uint16_t Length);
uint8_t *MassStorage_Joystick_GetConfigDescriptor(uint16_t Length);
uint8_t *MassStorage_Joystick_GetStringDescriptor(uint16_t Length);
RESULT MassStorage_Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Get_Max_Lun(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define HID_Joystick_GetConfiguration          NOP_Process
//#define Joystick_SetConfiguration          NOP_Process
#define HID_Joystick_GetInterface              NOP_Process
#define HID_Joystick_SetInterface              NOP_Process
#define HID_Joystick_GetStatus                 NOP_Process
#define HID_Joystick_ClearFeature              NOP_Process
#define HID_Joystick_SetEndPointFeature        NOP_Process
#define HID_Joystick_SetDeviceFeature          NOP_Process
//#define Joystick_SetDeviceAddress          NOP_Process

#define REPORT_DESCRIPTOR                  0x22



#define MassStorage_Joystick_GetConfiguration          NOP_Process
/* #define Mass_Storage_SetConfiguration          NOP_Process*/
#define MassStorage_Joystick_GetInterface              NOP_Process
#define MassStorage_Joystick_SetInterface              NOP_Process
#define MassStorage_Joystick_GetStatus                 NOP_Process
/* #define Mass_Storage_ClearFeature              NOP_Process*/
#define MassStorage_Joystick_SetEndPointFeature        NOP_Process
#define MassStorage_Joystick_SetDeviceFeature          NOP_Process
/*#define Mass_Storage_SetDeviceAddress          NOP_Process*/

#endif /* __USB_PROP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
