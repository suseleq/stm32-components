/*
 *	LCD_I2C.h
 *
 *  Created on: May 3, 2025
 *  Author: Susel
 */
#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "stdbool.h"
#include "stm32f7xx_hal.h" //change for your board

#define LCD_ADDRESS                 0x27

#define RS_PIN                      0x01
#define RW_PIN                      0x02
#define EN_PIN                      0x04
#define BL_PIN                      0x08

#define INIT_8_BIT_MODE             0x30
#define INIT_4_BIT_MODE             0x02

#define CURSOR_OFF_BLINK_OFF       0x0C
#define CURSOR_OFF_BLINK_ONN       0x0D
#define CURSOR_ON_BLINK_OFF        0x0E
#define CURSOR_ON_BLINK_ON         0x0F

#define CLEAR_LCD                  0x01

#define FIRST_LINE_START           0x80
#define SECOND_LINE_START          0xC0

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t adress;
    char first_line[17];
    char second_line[17];
    bool back_light;
} LCD_t;

void lcd_write(LCD_t *lcd, uint8_t dt, uint8_t rs_pin);
void lcd_clear(LCD_t *lcd);
void lcd_init(LCD_t *lcd, I2C_HandleTypeDef *i2c, bool bl);
void lcd_display(LCD_t *lcd);



#endif /* INC_LCD_I2C_H_ */
