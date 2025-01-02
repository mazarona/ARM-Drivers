/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  gpio.c
 *        \brief  An implementation of the Gpio driver
 *
 *      \details  It implements 5 sub-routines used for wirting or reading a particular pin
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "inc/gpio.h"
#include "../../lib/mcu_hw.h"
#include "../../lib/std_types.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define NUMBER_OF_CHANNELS_PER_PORT 8u
#define BAND_REGION_START 0x40000000
#define BAND_ALIAS_REGION_START 0x42000000
#define BIT_BANDING 1

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static const uint32 gpioDataPorts[] = {
    GPIO_PORT_A_BASE_ADDRESS,
    GPIO_PORT_B_BASE_ADDRESS,
    GPIO_PORT_C_BASE_ADDRESS,
    GPIO_PORT_D_BASE_ADDRESS,
    GPIO_PORT_E_BASE_ADDRESS,
    GPIO_PORT_F_BASE_ADDRESS,
};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : Gpio_LevelType Gpio_ReadChannel(Gpio_ChannelType channelId);
 * \Description     : read level from channel
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : channelId   Identifies what channel to read
 * \Parameters (out): None
 * \Return value:   : Gpio_LevelType  GPIO_LEVEL_HIGH
 *                                    GPIO_LEVEL_LOW
 *******************************************************************************/

Gpio_LevelType Gpio_ReadChannel(Gpio_ChannelType channelId)
{
  uint32 pinIndex, portIndex, dataPortMaskAdd, gpioDataPortAddress;
  Gpio_LevelType level;
  portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
  pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;
#if BIT_BANDING == 1
  uint32 bitWordOffset, byteOffset, bitNumber, bitWordAddress;
  byteOffset = gpioDataPorts[portIndex] + 0x3FC - BAND_REGION_START;
  bitNumber = pinIndex;
  bitWordOffset = (byteOffset * 32) + (bitNumber * 4);
  level = GET_REG(BAND_ALIAS_REGION_START, bitWordOffset) & 1;

#else
  gpioDataPortAddress = gpioDataPorts[portIndex];
  dataPortMaskAdd = ((1 << pinIndex) << 2);
  level = GET_REG(gpioDataPortAddress, GPIO_DATA_OFFSET + dataPortMaskAdd) >>
          pinIndex;
#endif
  return level;
}

/******************************************************************************
 * \Syntax          : void Gpio_WriteChannel(Gpio_ChannelType channelId, Gpio_LevelType level)
 * \Description     : Write level to channel
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : channelId   Identifies what channel to write
                      level       The value to be written on the channel
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Gpio_WriteChannel(Gpio_ChannelType channelId, Gpio_LevelType level)
{
  uint32 pinIndex, portIndex, dataPortMaskAdd;
  portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
  pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;
#if BIT_BANDING == 1
  uint32 bitWordOffset, byteOffset, bitNumber, bitWordAddress;
  byteOffset = gpioDataPorts[portIndex] + 0x3FC - BAND_REGION_START;
  bitNumber = pinIndex;
  bitWordOffset = (byteOffset * 32) + (bitNumber * 4);
  GET_REG(BAND_ALIAS_REGION_START, bitWordOffset) = level;
#else
  dataPortMaskAdd = ((1 << pinIndex) << 2);
  GET_REG(gpioDataPorts[portIndex], GPIO_DATA_OFFSET + dataPortMaskAdd) =
      level << pinIndex;
#endif
}

/******************************************************************************
 * \Syntax          : Gpio_PortLevelType Gpio_ReadPort(Gpio_PortType portId)
 * \Description     : Read level from port
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : portId         Identifies the port
 * \Parameters (out): None
 * \Return value:   : Gpio_PortLevelType  uint8
 *******************************************************************************/
Gpio_PortLevelType Gpio_ReadPort(Gpio_PortType portId)
{
  Gpio_PortLevelType level;
  uint32 dataPortMaskAdd;
  dataPortMaskAdd = 0xFF << 2;
  level = GET_REG(gpioDataPorts[portId], GPIO_DATA_OFFSET + dataPortMaskAdd);
  return level;
}

/******************************************************************************
 * \Syntax          : void Gpio_WritePort(Gpio_PortType portId, Gpio_PortLevelType level)
 * \Description     : Write level to port
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : portId  Identifies the port
                      level   The value to be written on the port
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Gpio_WritePort(Gpio_PortType portId, Gpio_PortLevelType level)
{
  uint32 dataPortMaskAdd;
  dataPortMaskAdd = 0xFF << 2;
  GET_REG(gpioDataPorts[portId], GPIO_DATA_OFFSET + dataPortMaskAdd) = level;
}

/******************************************************************************
 * \Syntax          : Gpio_LevelType Gpio_FlipChannel(Gpio_ChannelType channelId)
 * \Description     : Toggel the given channel level
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant  // TODO: Use synchronous primitives to make it reentrant
 * \Parameters (in) : channelId   Identifies the channel
 * \Parameters (out): None
 * \Return value:   : Gpio_LevelType  GPIO_LEVEL_LOW
                                      GPIO_LEVEL_HIGH
 *
 *******************************************************************************/
Gpio_LevelType Gpio_FlipChannel(Gpio_ChannelType channelId)
{
  Gpio_LevelType level;
  if (Gpio_ReadChannel(channelId) == GPIO_LEVEL_HIGH)
  {
    Gpio_WriteChannel(channelId, GPIO_LEVEL_LOW);
    level = GPIO_LEVEL_LOW;
  }
  else
  {
    Gpio_WriteChannel(channelId, GPIO_LEVEL_HIGH);
    level = GPIO_LEVEL_HIGH;
  }
  return level;
}

/**********************************************************************************************************************
 *  END OF FILE: gpio.c
 *********************************************************************************************************************/
