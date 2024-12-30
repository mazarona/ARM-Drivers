/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  systick.c
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
#include "inc/systick.h"
#include "../../lib/mcu_hw.h"
#include "../../lib/std_types.h"
#include "config/systick_cfg.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define SYSTICK_STCURRENT_CLEAR 1
#define SYSTICK_ENABLE 1
#define SYSTICK_DISABLE 0
#define SYSTICK_SYSTEM_CLOCK 1
#define SYSTICK_INTERNAL 0
#define KEIL_SIM_CLOCK_FREQ 8e6

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static void (*sysTickISR)(void);
uint32 numberOfOverFlows = 0;
uint32 onNumberOfOverFlows = 0;
uint32 offNumberOfOverFlows = 0;

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
void SysTick_Init(void)
{
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

/******************************************************************************
 * \Syntax          :  void SysTick_SetDuration(SysTick_DurationInSType onDuration,
                       SysTick_DurationInSType offDuration)
 * \Description     :  Set two delay durations for the SysTick ISR

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : onDuration  The amount of time for the LED to be on
                      offDuration The amount of time for the LED to be off
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
/* TODO: Should this function be in the HAL layer? */
void SysTick_SetDuration(SysTick_DurationInSType onDuration, SysTick_DurationInSType offDuration)
{
  /* Program the value in the STRRELOAD */
  onNumberOfOverFlows = (int)(onDuration * 1000.0);
  offNumberOfOverFlows = (int)(offDuration * 1000.0);

  numberOfOverFlows = offNumberOfOverFlows;

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
 * \Reentrancy      : Reentrant/Non Reentrant --> Depends on the user implementation of the ISR
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
/* ISR IS EXECUTED EVERY 1 MS */
void SysTick_Handler(void) { sysTickISR(); }

/**********************************************************************************************************************
 *  END OF FILE: systick.c
 *********************************************************************************************************************/
