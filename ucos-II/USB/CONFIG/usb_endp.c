/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
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
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_desc.h"
#include "usb_prop.h"
#include "usb_bot.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;
extern __IO uint8_t ReciveDataFromUsbHost;
extern __IO uint8_t USB_Receive_Buffer[ENDP1_SIZE];
extern USBClass USB_Type;
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  通过USB发送数据
  * @param  data 数据存储首地址
  * @param  dataNum 发送的数据字节数
  * @retval 发送的字节数
  */
uint32_t USB_SendData(uint8_t *data,uint32_t dataNum)
{
	PrevXferComplete = 0;//tell the usb trans is using
	USB_SIL_Write(EP1_IN, data, dataNum);  
  SetEPTxValid(ENDP1);
  while(PrevXferComplete != 1); //等待发送缓存区可用
	return dataNum;  
}
/**
  * @brief  接收从USB获取的数据
  * @param  data 数据存储首地址
  * @param  dataNum 准备读取的数据字节数
  * @retval 读取的字节数
  */
uint32_t USB_GetData(uint8_t *data,uint32_t dataNum)
{
  uint32_t len=0;
	if(dataNum>sizeof(USB_Receive_Buffer)){
		dataNum = sizeof(USB_Receive_Buffer);
	}
	for(len=0;len<dataNum;len++){
		*data=USB_Receive_Buffer[len];
		data++;
	}
  return dataNum;
}
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_OUT_Callback(void)
{
  /* Read received data (64 bytes) */  
	if(USB_Type == HID){
		USB_SIL_Read(EP1_OUT, USB_Receive_Buffer);        //获取数据

		SetEPRxStatus(ENDP1, EP_RX_VALID);
		ReciveDataFromUsbHost = true;
		PrevXferComplete = 1;//缓存有数据标志
	}
}
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
  /* Set the transfer complete token to inform upper layer that the current 
  transfer has been complete */
	if(USB_Type == HID){
		PrevXferComplete = 1; 
	}else if(USB_Type == MassStorage){
		Mass_Storage_In();
	}
}
void EP2_OUT_Callback(void)
{
	Mass_Storage_Out();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

