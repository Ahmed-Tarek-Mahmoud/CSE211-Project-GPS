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
*/
void NVIC_GetActiveFlag(uint8_t IntNumber, uint8_t *Result);

#endif