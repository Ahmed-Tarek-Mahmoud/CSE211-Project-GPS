
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H 

/*******************< Ports Macros ********************/

#define GPIO_PORTA   0  /**< Port A */
#define GPIO_PORTB   1  /**< Port B */
#define GPIO_PORTC   2  /**< Port C */
#define GPIO_PORTD   3  /**< Port D */
#define GPIO_PORTE   4  /**< Port E */
#define GPIO_PORTF   5  /**< Port F */

/*******************< Pin Value Macros ********************/

#define GPIO_LOW            0   /**< GPIO Low value */
#define GPIO_HIGH           1   /**< GPIO High value */

/******************< Pin Direction Macros ******************/

#define GPIO_INPUT            0   /**< GPIO input mode  */
#define GPIO_OUTPUT           1   /**< GPIO output mode */

/*******************< Pins Macros  **********************/

#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
#define PIN4        4
#define PIN5        5
#define PIN6        6
#define PIN7        7


//***************************************************************
/**
 * @brief this function will initialize the passed port as digital input output
*/

void GPIO_Init(uint8_t PortID);

/**
 * @brief this function will set the direction of the passed pin in the passed port (digital input or digital output)
*/

void GPIO_SetPinDirection (uint8_t PortId, uint8_t PinId,uint8_t PinDirection);

/**
 * @brief this function sets the passed pin value in passed port 
*/

void GPIO_SetPinValue(uint8_t PortId, uint8_t PinId);

/**
 * this function gets the pin value of the passed pin in the passed port and assigns the value at the given address
*/

void GPIO_GetPinValue(uint8_t PortId, uint8_t PinId, uint8_t *ReturnedValue);



#endif