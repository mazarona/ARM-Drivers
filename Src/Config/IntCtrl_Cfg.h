/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *
 -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NUMBER_OF_ACTIVE_INT 3
/*
 * NVIC_GROUPING_SYS_XXX -> group[0:7], sub-group[0:0]
 * NVIC_GROUPING_SYS_XXY -> group[0:3], sub-group[0:1]
 * NVIC_GROUPING_SYS_XYY -> group[0:1], sub-group[0:3]
 * NVIC_GROUPING_SYS_YYY -> group[0:0], sub-group[0:7] -> No preemption
 */
#define NVIC_GROUPING_SYS NVIC_GROUPING_SYS_YYY

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* INTCTRL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Cfg.h
 *********************************************************************************************************************/
