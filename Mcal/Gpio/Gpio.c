/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief
 *
 *      \details
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Inc/Gpio.h"
#include "../../Lib/Mcu_Hw.h"
#include "../../Lib/Std_Types.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define NUMBER_OF_CHANNELS_PER_PORT 8u

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static const uint32 gpioDataPorts[] = {
    GPIO_PORT_A_BASE_ADDRESS, GPIO_PORT_B_BASE_ADDRESS,
    GPIO_PORT_C_BASE_ADDRESS, GPIO_PORT_D_BASE_ADDRESS,
    GPIO_PORT_E_BASE_ADDRESS, GPIO_PORT_F_BASE_ADDRESS,
};

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
Gpio_LevelType Gpio_ReadChannel(Gpio_ChannelType channelId) {
  uint32 pinIndex, portIndex, dataPortMaskAdd;
  Gpio_LevelType level;

  portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
  pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;

  dataPortMaskAdd = ((1 << pinIndex) << 2);
  level =
      GET_REG(gpioDataPorts[portIndex], GPIO_DATA_OFFSET + dataPortMaskAdd) >>
      pinIndex;
  return level;
}

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void GPIO_WriteChannel(Gpio_ChannelType channelId, Gpio_LevelType level) {
  uint32 pinIndex, portIndex, dataPortMaskAdd;

  portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
  pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;

  dataPortMaskAdd = ((1 << pinIndex) << 2);
  GET_REG(gpioDataPorts[portIndex], GPIO_DATA_OFFSET + dataPortMaskAdd) =
      level << pinIndex;
}

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
Gpio_PortLevelType Gpio_ReadPort(Gpio_PortType portId) {
  Gpio_PortLevelType level;
  uint32 dataPortMaskAdd;
  dataPortMaskAdd = 0xFF << 2;
  level = GET_REG(gpioDataPorts[portId], GPIO_DATA_OFFSET + dataPortMaskAdd);
  return level;
}

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Gpio_WritePort(Gpio_PortType portId, Gpio_PortLevelType level) {
  uint32 dataPortMaskAdd;
  dataPortMaskAdd = 0xFF << 2;
  GET_REG(gpioDataPorts[portId], GPIO_DATA_OFFSET + dataPortMaskAdd) = level;
}

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
Gpio_LevelType Gpio_FlipChannel(Gpio_ChannelType channelId) {
  Gpio_LevelType level;
  if (Gpio_ReadChannel(channelId) == GPIO_LEVEL_HIGH) {
    GPIO_WriteChannel(channelId, GPIO_LEVEL_LOW);
    level = GPIO_LEVEL_LOW;
  } else {
    GPIO_WriteChannel(channelId, GPIO_LEVEL_HIGH);
    level = GPIO_LEVEL_HIGH;
  }
  return level;
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
