/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *
 -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition
 *
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct {
  uint32 VECACT : 8;
  uint32 : 3;
  uint32 RETBASE : 1;
  uint32 VECPEND : 7;
  uint32 : 2;
  uint32 ISRPEND : 1;
  uint32 ISRPRE : 1;
  uint32 : 1;
  uint32 PENDSTCLR : 1;
  uint32 PENDSTSET : 1;
  uint32 UNPENDSV : 1;
  uint32 PENDSV : 1;
  uint32 : 2;
  uint32 NMISET : 1;
} INTCTRL_BF;
typedef union {
  uint32 R;
  INTCTRL_BF B;
} INTCTRL_Tag;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CORTEXM4_PERI_BASE_ADDRESS 0xE000E000
/* NVIC Registers */
#define NVIC_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + 0x100)
#define NVIC_EN_OFFSET 0x0
#define NVIC_PRI_OFFSET 0x300
#define NVIC_BASE_EN_ADDRESS (NVIC_BASE_ADDRESS + NVIC_EN_OFFSET)
#define NVIC_BASE_PRI_ADDRESS (NVIC_BASE_ADDRESS + NVIC_PRI_OFFSET)
#define APINT *((volatile uint32 *)(CORTEXM4_PERI_BASE_ADDRESS + 0xD0C))
/* SYSTICK Registers */
#define SYSTICK_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + 0x010)
#define SCB_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + 0xD00)

#define APINT *((volatile uint32 *)(CORTEXM4_PERI_BASE_ADDRESS + 0xD0C))
#define INTCTRL *((volatile INTCTRL_Tag *)(CORTEXM4_PERI_BASE_ADDRESS + 0xD04))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define GET_REG(Base, Offset) *((volatile uint32 *)(Base + Offset))

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#endif /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
