/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SysTick.c
 *        \brief Implemetiation of the system timer driver
 *
 *      \details Implemetiation of the system timer driver. It only has
 a single function that initializes the SysTick. And another one for preloading
 the timer with a user specified duration.
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Inc/SysTick.h"
#include "../../Lib/Mcu_Hw.h"
#include "../../Lib/Std_Types.h"
#include "Config/SysTick_Cfg.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define SYSTICK_STCURRENT_CLEAR 1
#define SYSTICK_ENABLE 1
#define SYSTICK_DISABLE 0
#define SYSTICK_SYSTEM_CLOCK 1
#define SYSTICK_INTERNAL 0
#define KEIL_SIM_CLOCK_FREQ 12e6

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static void (*sysTickISR)(void);
uint32 numberOfOverFlows = 0;
uint32 onNumberOfOverFlows = 0;
uint32 offNumberOfOverFlows = 0;

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
 * \Syntax          :  void SysTick_Init(void)
 * \Description     : Initialize the system timer periferal

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void SysTick_Init(void) {
  /* Program the value in the STRRELOAD register with user define value */
  SYSTICK_STRELOAD_ADDRESS = SYSTICK_INIT_PRELOAD_VAL;

  /* Clear the STCURRENT register by writing to it with any value*/
  SYSTICK_STCURRENT_ADDRESS = SYSTICK_STCURRENT_CLEAR;

  /* Configure STCTRL register for the required operation */
  /* 1. Choose the clock source for the system timer according to the user
   * configuration*/
  SYSTICK_STCTRL_ADDRESS.BF.CLK_SRC = SYSTICK_CLOCK_SOURCE;

  /* 2. Enable or Disable Interrupt according to the user configuration */
  SYSTICK_STCTRL_ADDRESS.BF.INEN = SYSTICK_INTERRUPT_STATE;
  /* 3. Enable The counter */
  SYSTICK_STCTRL_ADDRESS.BF.EN = 1;
}

void SysTick_SetDuration(SysTick_DurationInSType onDuration,
                         SysTick_DurationInSType offDuration) {
  /* Program the value in the STRRELOAD */
  onNumberOfOverFlows = (int)(onDuration * 1000.0);
  offNumberOfOverFlows = (int)(offDuration * 1000.0);

  numberOfOverFlows = onNumberOfOverFlows;

  /* Clear the STCURRENT register by writing to it with any value*/
  SYSTICK_STCURRENT_ADDRESS = SYSTICK_STCURRENT_CLEAR;
}

/******************************************************************************
 * \Syntax          : void SysTick_SetISRCallBack(void (*funPtr)(void))
 * \Description     : Set the callback funtion for the system timer ISR

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : void(*funPtr)(void) a pointer funtion to ISR
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void SysTick_SetISRCallBack(void (*funPtr)(void)) { sysTickISR = funPtr; }

/******************************************************************************
 * \Syntax          : void SysTick_Handler(void)
 * \Description     : SysTick ISR

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
/* ISR IS EXECUTED EVERY 1 MS */
void SysTick_Handler(void) { sysTickISR(); }

/**********************************************************************************************************************
 *  END OF FILE: SysTick.c
 *********************************************************************************************************************/
