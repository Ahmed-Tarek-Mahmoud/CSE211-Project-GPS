#ifndef MCAL_NVIC_INTERFACE_H
#define MCAL_NVIC_INTERFACE_H

#include "stdint.h"
/**
 * @brief: Enables the interrupt specified by the interrupt number.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number to be enabled.
*/
void NVIC_EnableInterrupt(uint8_t IntNumber);

/**
 * @brief: Disables the interrupt specified by the interrupt number.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number to be disabled.
*/
void NVIC_DisableInterrupt(uint8_t IntNumber);

/**
 * @brief: Sets the pending flag for the specified interrupt.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number for which the pending flag is to be set.
 *
*/
void NVIC_SetPendingFlag(uint8_t IntNumber);

/**
 * @brief: Clears the pending flag for the specified interrupt.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number for which the pending flag is to be cleared.
 *
*/
void NVIC_ClearPendingFlag(uint8_t IntNumber);

/**
 * @brief: Retrieves the active flag status for the specified interrupt.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number for which the active flag status is to be retrieved.
 *
 * @param Result: A pointer to an 8-bit unsigned integer where the active flag status will be stored. This parameter will be updated by the function call.
 *
 * Result is set to 1 if the specified flag is active.
 *
*/
void NVIC_GetActiveFlag(uint8_t IntNumber, uint8_t *Result);

/**
 * @brief: Set the priority of the wanted interrupt range from 0 to 7.
 *
 * @param IntNumber: An 8-bit unsigned integer representing the interrupt number for which the priority wanted to be set.
 *
 * @param priority: An 8-bit unsigned integer which specify the priority of the interrupt (0-->7).
 *
*/
void NVIC_SetPriority(uint8_t IRQ,uint8_t priority);

/**
 * @brief: Enables the interrupt of GPIO port F pin 0 and 4.
 *
 * The two switches are Edge sensitive reacts on a single falling edge.
 *
 * @param No param.
*/
void NVIC_GPIO_PORTF_Enable(void);

#endif
