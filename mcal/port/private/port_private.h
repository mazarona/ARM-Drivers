/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *
 -------------------------------------------------------------------------------------------------------------------
 *         File:  port_private.h
 *       Module:  PORT
 *
 *  Description:  A private file used to declare types that the user will use to
 configure the module. I put it here instead of Port_Types.h to not clutter my
 API types with Config Types. These config types shouldn't be visible to the
 user in main when using my driver.
 *
 *********************************************************************************************************************/
#ifndef PORT_PRIVATE_H
#define PORT_PRIVATE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../inc/port_types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
  Port_PinType pinId;
  Port_PinDirectionType pinDirection;
  Port_PinModeType pinMode;
  Port_PinInternalAttachType pinInternalAttach;
  Port_PinOutputCurrentType pinOutputCurrent;
  Port_PinExternalInterruptType pinExternalInterrupt;
} Port_ConfigType;

#endif /* PORT_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: port_private.h
 *********************************************************************************************************************/
