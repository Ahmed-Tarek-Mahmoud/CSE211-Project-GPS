#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/*******************< Macros needed *******************/






/******************< Functions ***********************/

/**
 * This function initializes the given switch with negative logic 
 * @param SwitchNo : switch number
 * 
 *          options: 1) PF_SW1
 *                   2) PF_SW2
*/

void Switch_Init(uint8_t SwitchNo);

/**
 * This function turns on the led with the passed color
 *  @param LedColor : led color
 * 
 *           options: 1) RGB_RED
 *                    2) RGB_BLUE
 *                    3) RGB_GREEN
*/

void LEDx_On(uint8_t LedColor);

#endif