#include "lcd.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_init() {
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
}

void lcd_display_string(char* first_line, char* second_line) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(first_line);
    lcd.setCursor(0, 1);
    lcd.print(second_line);
}

void lcd_display_string(char* first_line, char* second_line, int second_line_number) {
    char buffer[50];
    strcpy(buffer, second_line);
    char num_buffer[10];
    snprintf(num_buffer, 10, "%d", second_line_number);
    strcat(buffer, num_buffer);
    lcd_display_string(first_line, buffer);
}