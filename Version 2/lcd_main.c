#include <LPC21xx.h> 
#include "lcd_4bit.c" 

int main(void) {
    LCD_Init();                 // Initialize the LCD
    LCD_Command(0x80);          // Move cursor to the first row, first column
    LCD_String("Hello, World!"); // Display the message

    while (1); // Infinite loop
}
