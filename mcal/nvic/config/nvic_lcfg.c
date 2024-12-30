/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Nvic_Lcfg.c
 *        \brief  Configuration file for Nvic module
 *
 *      \details  Configuration file for Nvic module
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../../Lib/Std_Types.h"
#include "../Inc/Nvic_Types.h"
#include "Nvic_Cfg.h"
/* TODO : Should I change the type definitions for the config inside of this
file instead of inside Nvic_Types.h since It's not really a part of my driver
API... It's only used to config how my code behaves... I mean the user will
never use the type NVIC_CfgType in main when he includes my driver right??? The
purpose of this type is to configure the driver before building the project, It
will NEVER be used in main. Maybe in the future i seperate declared types for
config in a seperate Module_ConfigTypes.h*/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
const Nvic_CfgType NVIC_Cfg[NVIC_NUMBER_OF_ACTIVE_INT] = {
    /*Interrupt Number | Group Priority | Sub-Groub Priority */
    {NVIC_DIO_PORT_F, 0, 1},
};

/**********************************************************************************************************************
 *  END OF FILE: Nvic_Lcfg.c
 *********************************************************************************************************************/
