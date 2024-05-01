#ifndef HAL_LCD_CONFIG
#define HAL_LCD_CONFIG

//*************************LCD_MODES***************************
#define LCD_MODE                LCD_4_BIT_MODE
#define LCD_8_BIT_MODE          8
#define LCD_4_BIT_MODE          4

//*************************CONTROL PORT*************************
#define LCD_CONTROL_PORT                GPIO_PORTB
#define LCD_RS_PIN                      PIN0
#define LCD_RW_PIN                      PIN1
#define LCD_EN_PIN                      PIN2

//*************************DATA PORT****************************
#define LCD_DATA_PORT                   GPIO_PORTB
#define LCD_D0_PIN                      PIN0
#define LCD_D1_PIN                      PIN1 
#define LCD_D2_PIN                      PIN2
#define LCD_D3_PIN                      PIN3
#define LCD_D4_PIN                      PIN4
#define LCD_D5_PIN                      PIN5
#define LCD_D6_PIN                      PIN6
#define LCD_D7_PIN                      PIN7

//***************************LCD command**********************
#define LCD_CLEAR_COMMAND                       0x01
#define LCD_DECREMENT_CURSOR                    0x04
#define LCD_INCREMENT_CURSOR                    0x06
#define LCD_SHIFT_DISPLAY_RIGHT                 0x05
#define LCD_SHIFT_DISPLAY_LEFT                  0x07
#define LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define LCD_DISPLAY_ON_CURSOR_BLINKING          0x0F
#define LCD_CURSOR_SHIFT_LEFT                   0x10
#define LCD_CURSOR_SHIFT_RIGHT                  0x14
#define LCD_DISPLAY_SHIFT_LEFT                  0x18
#define LCD_DISPLAY_SHIFT_RIGHT                 0x1C
#define LCD_CURSOR_BEGIN_FIRST_LINE             0x80
#define LCD_CURSOR_BEGIN_SECOND_LINE            0xC0
#define LCD_8_BIT_MODE_COMMAND                  0x38
#define LCD_4_BIT_MODE_COMMAND                  0x28




#endif