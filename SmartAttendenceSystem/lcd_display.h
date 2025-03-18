#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 13, 12, 14, 15);

void lcd_init() {
  lcd.begin(16, 2);
}

void lcd_display(String message, int line = 0) {
  lcd.setCursor(0, line);
  lcd.print(message);
}

#endif