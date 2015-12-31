/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Joystick Mouse Demo
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
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "mass_mal.h"
#include "usb_bot.h"

uint32_t Max_Lun =MAX_LUN; //定义USB设备的数量,1代表2个.0代表一个  

USBClass USB_Type = HID;
extern unsigned char Bot_State;
extern Bulk_Only_CBW CBW;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;


DEVICE Device_Table;
DEVICE_PROP Device_Property;
USER_STANDARD_REQUESTS User_Standard_Requests;
ONE_DESCRIPTOR Device_Descriptor;
ONE_DESCRIPTOR Config_Descriptor;
/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE HID_Device_Table =
  {
    HID_EP_NUM,
    1
  };

DEVICE_PROP HID_Device_Property =
  {
    HID_Joystick_init,
    HID_Joystick_Reset,
    HID_Joystick_Status_In,
    HID_Joystick_Status_Out,
    HID_Joystick_Data_Setup,
    HID_Joystick_NoData_Setup,
    HID_Joystick_Get_Interface_Setting,
    HID_Joystick_GetDeviceDescriptor,
    HID_Joystick_GetConfigDescriptor,
    HID_Joystick_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS HID_User_Standard_Requests =
  {
    HID_Joystick_GetConfiguration,
    HID_Joystick_SetConfiguration,
    HID_Joystick_GetInterface,
    HID_Joystick_SetInterface,
    HID_Joystick_GetStatus,
    HID_Joystick_ClearFeature,
    HID_Joystick_SetEndPointFeature,
    HID_Joystick_SetDeviceFeature,
    HID_Joystick_SetDeviceAddress
  };

ONE_DESCRIPTOR HID_Device_Descriptor =
  {
    (uint8_t*)HID_Joystick_DeviceDescriptor,
    HID_JOYSTICK_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR HID_Config_Descriptor =
  {
    (uint8_t*)HID_Joystick_ConfigDescriptor,
    HID_JOYSTICK_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR Joystick_Report_Descriptor =
  {
    (uint8_t *)HID_Joystick_ReportDescriptor,
    HID_JOYSTICK_SIZ_REPORT_DESC
  };

ONE_DESCRIPTOR Mouse_Hid_Descriptor =
  {
    (uint8_t*)HID_Joystick_ConfigDescriptor + JOYSTICK_OFF_HID_DESC,
    JOYSTICK_SIZ_HID_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)HID_Joystick_StringLangID, HID_JOYSTICK_SIZ_STRING_LANGID},
    {(uint8_t*)HID_Joystick_StringVendor, HID_JOYSTICK_SIZ_STRING_VENDOR},
    {(uint8_t*)HID_Joystick_StringProduct, HID_JOYSTICK_SIZ_STRING_PRODUCT},
    {(uint8_t*)HID_Joystick_StringSerial, HID_JOYSTICK_SIZ_STRING_SERIAL}
  };
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
/*the MassStorage type */
	DEVICE MassStorage_Device_Table =
  {
    MassStorage_EP_NUM,
    1
  };

DEVICE_PROP MassStorage_Device_Property =
  {
    MassStorage_Joystick_init,
    MassStorage_Joystick_Reset,
    MassStorage_Joystick_Status_In,
    MassStorage_Joystick_Status_Out,
    MassStorage_Joystick_Data_Setup,
    MassStorage_Joystick_NoData_Setup,
    MassStorage_Joystick_Get_Interface_Setting,
    MassStorage_Joystick_GetDeviceDescriptor,
    MassStorage_Joystick_GetConfigDescriptor,
    MassStorage_Joystick_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS MassStorage_User_Standard_Requests =
  {
    MassStorage_Joystick_GetConfiguration,
    MassStorage_Joystick_SetConfiguration,
    MassStorage_Joystick_GetInterface,
    MassStorage_Joystick_SetInterface,
    MassStorage_Joystick_GetStatus,
    MassStorage_Joystick_ClearFeature,
    MassStorage_Joystick_SetEndPointFeature,
    MassStorage_Joystick_SetDeviceFeature,
    MassStorage_Joystick_SetDeviceAddress
  };

ONE_DESCRIPTOR MassStorage_Device_Descriptor =
  {
    (uint8_t*)MassStorage_Joystick_DeviceDescriptor,
    MassStorage_JOYSTICK_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR MassStorage_Config_Descriptor =
  {
    (uint8_t*)MassStorage_Joystick_ConfigDescriptor,
    MassStorage_JOYSTICK_SIZ_CONFIG_DESC
  };
ONE_DESCRIPTOR MassStorage_String_Descriptor[5] =
  {
    {(uint8_t*)MassStorage_Joystick_StringLangID, MassStorage_JOYSTICK_SIZ_STRING_LANGID},
    {(uint8_t*)MassStorage_Joystick_StringVendor, MassStorage_JOYSTICK_SIZ_STRING_VENDOR},
    {(uint8_t*)MassStorage_Joystick_StringProduct, MassStorage_JOYSTICK_SIZ_STRING_PRODUCT},
    {(uint8_t*)MassStorage_Joystick_StringSerial, MassStorage_JOYSTICK_SIZ_STRING_SERIAL},
		{(uint8_t*)MassStorage_Joystick_StringInterface, MassStorage_JOYSTICK_MASS_SIZ_STRING_INTERFACE},
  };
	
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void usb_type_set(void)
{
	switch(USB_Type){
		case HID:
			Device_Table = HID_Device_Table ;
			Device_Property = HID_Device_Property ;
			User_Standard_Requests = HID_User_Standard_Requests ;
			Device_Descriptor = HID_Device_Descriptor ;
			Config_Descriptor = HID_Config_Descriptor ;
			break;
		case MassStorage:
			Device_Table = MassStorage_Device_Table ;
			Device_Property = MassStorage_Device_Property ;
			User_Standard_Requests = MassStorage_User_Standard_Requests ;
			Device_Descriptor = MassStorage_Device_Descriptor ;
			Config_Descriptor = MassStorage_Config_Descriptor ;
			break;
		default:
			break;
	}
}
/*******************************************************************************
* Function Name  : Joystick_init.
* Description    : Joystick Mouse init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_init(void)
{

  /* Update the serial number string descriptor with the data from the unique
  ID*/
	printf("usb get serialnum\n");
  Get_SerialNum();

  pInformation->Current_Configuration = 0;
  /* Connect the device */
	printf("poweron\n");
  PowerOn();//将配置写入寄存器  启动usb枚举

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : Joystick_Reset.
* Description    : Joystick Mouse reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_Reset(void)
{
  /* Set Joystick_DEVICE as not configured */
  pInformation->Current_Configuration = 0;
  pInformation->Current_Interface = 0;/*the default Interface*/

  /* Current Feature initialization */
  pInformation->Current_Feature = HID_Joystick_ConfigDescriptor[7];
  SetBTABLE(BTABLE_ADDRESS);
  /* Initialize Endpoint 0 */
  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_STALL);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);

  /* Initialize Endpoint 1 */
  SetEPType(ENDP1, EP_INTERRUPT);//初始化为中断端点类型
  SetEPTxAddr(ENDP1, ENDP1_TXADDR); //设置发送数据的地址
	SetEPRxAddr(ENDP1, ENDP1_RXADDR);
  SetEPTxCount(ENDP1, ENDP1_SIZE);//这里的4是跟报告描述符中定义的字符数匹配的  设置发送的长度
	SetEPRxCount(ENDP1,ENDP1_SIZE);
  SetEPRxStatus(ENDP1, EP_RX_VALID);//disable
  SetEPTxStatus(ENDP1, EP_TX_NAK); //设置端点处于忙状态

  /* Set this device to response on default address */
  SetDeviceAddress(0);
  bDeviceState = ATTACHED;
}
/*******************************************************************************
* Function Name  : Joystick_SetConfiguration.
* Description    : Update the device state to configured.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
}
/*******************************************************************************
* Function Name  : Joystick_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : Joystick_Status_In.
* Description    : Joystick status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_Status_In(void)
{}

/*******************************************************************************
* Function Name  : Joystick_Status_Out
* Description    : Joystick status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HID_Joystick_Status_Out (void)
{}

/*******************************************************************************
* Function Name  : Joystick_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT HID_Joystick_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;
  if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndex0 == 0))
  {
    if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
    {
      CopyRoutine = HID_Joystick_GetReportDescriptor;
    }
    else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
    {
      CopyRoutine = HID_Joystick_GetHIDDescriptor;
    }

  } /* End of GET_DESCRIPTOR */

  /*** GET_PROTOCOL ***/
  else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
  {
    CopyRoutine = HID_Joystick_GetProtocolValue;
  }
  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }
  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Joystick_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT HID_Joystick_NoData_Setup(uint8_t RequestNo)
{
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return HID_Joystick_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : Joystick_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *HID_Joystick_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &HID_Device_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *HID_Joystick_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &HID_Config_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *HID_Joystick_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}

/*******************************************************************************
* Function Name  : Joystick_GetReportDescriptor.
* Description    : Gets the HID report descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *HID_Joystick_GetReportDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Joystick_Report_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_GetHIDDescriptor.
* Description    : Gets the HID descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *HID_Joystick_GetHIDDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Mouse_Hid_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT HID_Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Joystick_SetProtocol
* Description    : Joystick Set Protocol request routine.
* Input          : None.
* Output         : None.
* Return         : USB SUCCESS.
*******************************************************************************/
RESULT HID_Joystick_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Joystick_GetProtocolValue
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protocol value.
*******************************************************************************/
uint8_t *HID_Joystick_GetProtocolValue(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/********************   The MassStorage type function    **************/
/*******************************************************************************
* Function Name  : Joystick_init.
* Description    : Joystick Mouse init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_init(void)
{

  /* Update the serial number string descriptor with the data from the unique
  ID*/
  Get_SerialNum();

  pInformation->Current_Configuration = 0;
  /* Connect the device */
  PowerOn();//将配置写入寄存器  启动usb枚举

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : Joystick_Reset.
* Description    : Joystick Mouse reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_Reset(void)
{
  /* Set Joystick_DEVICE as not configured */
  Device_Info.Current_Configuration = 0;

  /* Current Feature initialization */
  pInformation->Current_Feature = MassStorage_Joystick_ConfigDescriptor[7];
  SetBTABLE(BTABLE_ADDRESS);
  /* Initialize Endpoint 0 */
  SetEPType(ENDP0, EP_CONTROL);
//  SetEPTxStatus(ENDP0, EP_TX_STALL);//old
	SetEPTxStatus(ENDP0, EP_TX_NAK);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);

  /* Initialize Endpoint 1 */
  SetEPType(ENDP1, EP_BULK);
  SetEPTxAddr(ENDP1, ENDP1_TXADDR);
  SetEPTxStatus(ENDP1, EP_TX_NAK);
  SetEPRxStatus(ENDP1, EP_RX_DIS);

  /* Initialize Endpoint 2 */
  SetEPType(ENDP2, EP_BULK);
  SetEPRxAddr(ENDP2, ENDP2_RXADDR);
  SetEPRxCount(ENDP2, Device_Property.MaxPacketSize);
  SetEPRxStatus(ENDP2, EP_RX_VALID);
  SetEPTxStatus(ENDP2, EP_TX_DIS);
	
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);
	
  /* Set this device to response on default address */
  SetDeviceAddress(0);
  bDeviceState = ATTACHED;
	
	CBW.dSignature = BOT_CBW_SIGNATURE;
  Bot_State = BOT_IDLE;
}
/*******************************************************************************
* Function Name  : Joystick_SetConfiguration.
* Description    : Update the device state to configured.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_SetConfiguration(void)
{
	if (pInformation->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
   
    ClearDTOG_TX(ENDP1);
    ClearDTOG_RX(ENDP2);

    Bot_State = BOT_IDLE; /* set the Bot state machine to the IDLE state */
	}
}
	/*******************************************************************************
* Function Name  : Mass_Storage_ClearFeature
* Description    : Handle the ClearFeature request.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_ClearFeature(void)
{
  /* when the host send a CBW with invalid signature or invalid length the two
     Endpoints (IN & OUT) shall stall until receiving a Mass Storage Reset     */
  if (CBW.dSignature != BOT_CBW_SIGNATURE)
    Bot_Abort(BOTH_DIR);
}
/*******************************************************************************
* Function Name  : Joystick_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : Joystick_Status_In.
* Description    : Joystick status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_Status_In(void)
{}

/*******************************************************************************
* Function Name  : Joystick_Status_Out
* Description    : Joystick status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MassStorage_Joystick_Status_Out (void)
{}

/*******************************************************************************
* Function Name  : Joystick_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT MassStorage_Joystick_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == GET_MAX_LUN) && (pInformation->USBwValue == 0)
      && (pInformation->USBwIndex == 0) && (pInformation->USBwLength == 0x01))
  {
    CopyRoutine = Get_Max_Lun;
  }
  else
  {
    return USB_UNSUPPORT;
  }

  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);

  return USB_SUCCESS;

}

/*******************************************************************************
* Function Name  : Joystick_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT MassStorage_Joystick_NoData_Setup(uint8_t RequestNo)
{
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == MASS_STORAGE_RESET) && (pInformation->USBwValue == 0)
      && (pInformation->USBwIndex == 0) && (pInformation->USBwLength == 0x00))
  {
    /* Initialize Endpoint 1 */
    ClearDTOG_TX(ENDP1);

    /* Initialize Endpoint 2 */
    ClearDTOG_RX(ENDP2);

    /*initialize the CBW signature to enable the clear feature*/
    CBW.dSignature = BOT_CBW_SIGNATURE;
    Bot_State = BOT_IDLE;

    return USB_SUCCESS;
  }
  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Joystick_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *MassStorage_Joystick_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &MassStorage_Device_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *MassStorage_Joystick_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &MassStorage_Config_Descriptor);
}

/*******************************************************************************
* Function Name  : Joystick_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *MassStorage_Joystick_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  if (wValue0 > 5)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &MassStorage_String_Descriptor[wValue0]);
  }
}


/*******************************************************************************
* Function Name  : Joystick_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT MassStorage_Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Get_Max_Lun
* Description    : Handle the Get Max Lun request.
* Input          : uint16_t Length.
* Output         : None.
* Return         : None.
*******************************************************************************/
uint8_t *Get_Max_Lun(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = LUN_DATA_LENGTH;
    return 0;
  }
  else
  {
    return((uint8_t*)(&Max_Lun));
  }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

