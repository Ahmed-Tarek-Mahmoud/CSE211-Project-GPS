#ifndef MCAL_STK_INTERFACE_H
#define MCAL_STK_INTERFACE_H

#include "stdint.h"



/** @brief 	This function configures the SysTick timer with the specified number of ticks 
 *			and enables it with the system clock as its clock source
 *  @param 	Ticks : reload value to the Systick Timer.
 *
 * 
 *   please add in the config file preprocessing to the configuration such as
 *   clock source and interrupt enable or disable
 */ 

void STK_Init(uint32_t Ticks);

/** @brief 	This function resets the SysTick timer to its initial state, 
 *			with a reload value of 0 and the count flag cleared
 *
 */

void STK_Reset(void);

/** @brief 	This function returns the current value of the SysTick timer, 
 *			which is the number of ticks remaining before it reaches 0 and generates an interrupt
 * @param 	Current : pointer to return the current value in it
 * 
 */

void STK_GetCurrentValue(uint32_t *Current);

/** @brief 	This function sets the reload value for the SysTick timer, 
 *			which determines the initial value of the timer when it is enabled or reloaded
 *
 * @param 	copy_u32Ticks: value you want the SysTick start count down from it
 *
 */

void STK_SetReloadValue(uint32_t Ticks);

/**
 *  @brief 	This function enables the SysTick timer with the system clock as its clock source
 *
 */
void STK_Enable(void);

/** 
 * @brief 	This function disables the SysTick timer
 *
 *
 */
void STK_Disable(void);

/** @brief 	This function enables the SysTick interrupt
 *
 *
 */
void STK_EnableInterrupt(void);

/** @brief 	This function disables the SysTick interrupt
 *
 *
 */
void STK_DisableInterrupt(void);

/** @brief 	TThis function generates a software delay of the specified duration 
 *			using the SysTick timer
 *
 * @param 	DelayMs : The time in millisecond you want to make the delay by it.
 *
 */
void STK_Delay(uint32_t DelayMs);

#endif