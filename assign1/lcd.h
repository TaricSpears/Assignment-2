#ifndef _LCD_H_
#define _LCD_H_

#include <LiquidCrystal_I2C.h>

void lcd_init();

void lcd_display_string(char* first_line, char* second_line);
void lcd_display_string(char* first_line, char* second_line, int second_line_number);

#endif