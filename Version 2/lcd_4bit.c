#include <LPC21xx.h> 

#define RS (1 << 16)  
#define EN (1 << 17) 
#define DATA (0xF << 8) 


void delay_ms(int count) {
    for (int i = 0; i < count * 10000; i++) {
        __asm__("NOP"); // No Operation
    }
}


void LCD_SendNibble(unsigned char nibble) {
    IOCLR0 = DATA;          // Clear data pins
    IOSET0 = (nibble << 8); // Set nibble to data pins (P0.8 - P0.11)
    IOSET0 = EN;            // EN = 1 (Enable)
    delay_ms(1);            // Short delay
    IOCLR0 = EN;            // EN = 0 (Disable)
}


void LCD_Command(unsigned char cmd) {
    IOCLR0 = RS; // RS = 0 for command
    LCD_SendNibble(cmd >> 4); // Send higher nibble
    LCD_SendNibble(cmd & 0x0F); // Send lower nibble
    delay_ms(2); // Wait for command to execute
}


void LCD_Data(unsigned char data) {
    IOSET0 = RS; // RS = 1 for data
    LCD_SendNibble(data >> 4); // Send higher nibble
    LCD_SendNibble(data & 0x0F); // Send lower nibble
    delay_ms(2); // Wait for data to process
}


void LCD_Init() {
    IODIR0 = RS | EN | DATA; // Set RS, EN, and DATA pins as output
    delay_ms(20); // Wait for LCD to power up

    LCD_Command(0x02); // Initialize in 4-bit mode
    LCD_Command(0x28); // 2 lines, 5x7 matrix in 4-bit mode
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Auto increment cursor
    LCD_Command(0x01); // Clear display
    delay_ms(5);
}

// Display a string on the LCD
void LCD_String(char *str) {
    while (*str) {
        LCD_Data(*str++); // Send characters one by one
    }
}
