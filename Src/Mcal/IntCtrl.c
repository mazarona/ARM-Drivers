/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/ /**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups
 *and subgroups Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Inc/IntCtrl.h"
#include "../Common/Mcu_Hw.h"
#include "../Common/Std_Types.h"
#include "../Config/IntCtrl_Cfg.h"
#include "Inc/IntCtrl_Types.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define NVIC_GROUPING_SYS_XXX 4
#define NVIC_GROUPING_SYS_XXY 5
#define NVIC_GROUPING_SYS_XYY 6
#define NVIC_GROUPING_SYS_YYY 7
#define APINT_VECTKEY 0x05FA

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const NVIC_CfgType NVIC_Cfg[];
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
 * \Syntax          : void IntCrtl_Init(void)
 * \Description     : initialize Nvic\SCB Module by parsing the
 *Configuration into Nvic\SCB registers
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : None
 *******************************************************************************/
void IntCrtl_Init(void) {
  uint32 interruptNumber;
  uint8 groupPriority, subGroupPriority, prio;
  /*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
  APINT = (APINT_VECTKEY << 16) | (NVIC_GROUPING_SYS << 8);

  for (int i = 0; i < NUMBER_OF_ACTIVE_INT; i++) {
    interruptNumber = NVIC_Cfg[i].interruptNumber;
    groupPriority = NVIC_Cfg[i].groubPriority;
    subGroupPriority = NVIC_Cfg[i].subGroupPriority;
/*Assign Group-Subgroup priority in NVIC_PRIx */
#if NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XXX
    prio = groupPriority;
#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XXY
    prio = (groupPriority << 1) | subGroupPriority;
#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XYY
    prio = (groupPriority << 2) | subGroupPriority;
#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_YYY
    prio = subGroupPriority;
#endif
    GET_REG(NVIC_BASE_PRI_ADDRESS, (interruptNumber / 4)) |=
        (prio << ((interruptNumber % 4 * 8) + 5));

    /*Enable-Disable interrupts based on user configurations in NVIC_ENx */
    GET_REG(NVIC_BASE_EN_ADDRESS, (interruptNumber / 32) * 4) |=
        (1 << (interruptNumber % 32));
  }
}

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
