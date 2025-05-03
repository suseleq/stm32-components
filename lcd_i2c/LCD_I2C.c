/*
 *  LCD_I2C.c
 *
 *  Created on: May 3, 2025
 *  Author: Susel
 */

#include "LCD_I2C.h"

void lcd_write(LCD_t *lcd, uint8_t dt, uint8_t rs_pin) {
    uint8_t data[4];

    uint8_t bl_pin = 0;
    if (lcd->back_light) bl_pin = BL_PIN;

    uint8_t bl_rs = bl_pin | rs_pin;

    data[0] = (dt & 0xF0) | EN_PIN | bl_rs;
    data[1] = (dt & 0xF0) | bl_rs;
    data[2] = (dt << 4) | EN_PIN | bl_rs;
    data[3] = (dt << 4) | bl_rs;

    HAL_I2C_Master_Transmit(lcd->hi2c, lcd->adress, data, 4, 100);
    HAL_Delay(5);
}

void lcd_clear(LCD_t *lcd) {
    lcd_write(lcd, CLEAR_LCD, 0);
}

void lcd_init(LCD_t *lcd, I2C_HandleTypeDef *i2c, bool bl) {
    lcd->adress = LCD_ADDRESS << 1;
    lcd->hi2c = i2c;
    lcd->back_light = bl;

    HAL_Delay(40);
    lcd_write(lcd, INIT_8_BIT_MODE, 0);
    HAL_Delay(5);
    lcd_write(lcd, INIT_8_BIT_MODE, 0);
    HAL_Delay(1);
    lcd_write(lcd, INIT_8_BIT_MODE, 0);

    lcd_write(lcd, INIT_4_BIT_MODE, 0);

    lcd_write(lcd, CURSOR_OFF_BLINK_OFF, 0);
    lcd_clear(lcd);
}

void lcd_display(LCD_t *lcd) {
    lcd_clear(lcd);
    lcd_write(lcd, FIRST_LINE_START, 0);

    int i = 0;
    while (lcd->first_line[i]) {
        lcd_write(lcd, lcd->first_line[i], RS_PIN);
        i++;
    }

    i = 0;
    lcd_write(lcd, SECOND_LINE_START, 0);
    while (lcd->second_line[i]) {
        lcd_write(lcd, lcd->second_line[i], RS_PIN);
        i++;
    }
}
