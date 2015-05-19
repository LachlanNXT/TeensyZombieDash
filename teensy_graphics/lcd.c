/*
 * lcd.c
 *
 * Created: 32/13/2015 12:34:56 AM
 *  Author: Michael
 */ 

#include "lcd.h"
#include <avr/io.h>
 #include <avr/pgmspace.h>
#include <util/delay.h>
// Include our font pixel data
#include "ascii_font.h"

void LCDWrite(unsigned char dc, unsigned char data) {
	// Set the DC pin based on the parameter 'dc' (Hint: use the OUTPUT_WRITE macro)
	OUTPUT_WRITE(PORTB,DCPIN,dc);
	
	// Pull the SCE/SS pin low to signal the LCD we have data
	OUTPUT_LOW(PORTD,SCEPIN);
	
	// Write the byte of data using "bit bashing"
	int i;
	for(i = 7; i >= 0; i--) {
		OUTPUT_LOW(PORTF, SCKPIN) ;
		if((data>>i) & (1 == 1)) {
			OUTPUT_HIGH(PORTB, DINPIN);
		} else {
			OUTPUT_LOW(PORTB, DINPIN);
		}
		OUTPUT_HIGH(PORTF, SCKPIN);
	}
	
	// Pull SCE/SS high to signal the LCD we are done
	OUTPUT_HIGH(PORTD,SCEPIN);
}

// Initialise the LCD with our desired settings
void LCDInitialise(unsigned char contrast) {
	SET_OUTPUT(DDRD, SCEPIN);
	SET_OUTPUT(DDRB, RSTPIN);
	SET_OUTPUT(DDRB, DCPIN);
	SET_OUTPUT(DDRB, DINPIN);
	SET_OUTPUT(DDRF, SCKPIN);
		
	OUTPUT_LOW(PORTB, RSTPIN);
	OUTPUT_HIGH(PORTD, SCEPIN);
	OUTPUT_HIGH(PORTB, RSTPIN);
  
	LCDWrite(LCD_C, 0x21); // Enable LCD extended command set
	LCDWrite(LCD_C, 0x80 | contrast ); // Set LCD Vop (Contrast)
	LCDWrite(LCD_C, 0x04);
	LCDWrite(LCD_C, 0x13); // LCD bias mode 1:48
  
	LCDWrite(LCD_C, 0x0C); // LCD in normal mode.
  	LCDWrite(LCD_C, 0x20); // Enable LCD basic command set
	LCDWrite(LCD_C, 0x0C);

	LCDWrite(LCD_C, 0x40); // Reset row to 0
	LCDWrite(LCD_C, 0x80); // Reset column to 0
}

// Simply blank out the memory of the LCD to clear the screen
void LCDClear(void) {
	int i;
	for (i = 0; i < LCD_X * LCD_Y / 8; i++) {
		LCDWrite(LCD_D, 0x00);
	}
}

void LCDCharacter(unsigned char character) {
	/*
		Blank pixel column before the character, to increase readability
		Also, our font is only 5 pixels wide, since our LCD is 84 pixels wide
		we can fit twelve 7 pixel wide characters across.
	*/
	LCDWrite(LCD_D, 0x00);
	
	int index;
	for (index = 0; index < 5; index++) {
		// Write each of the 5 pixel rows to the LCD, we subtract 0x20 since
		// our table doesn't have the unprintable ASCII characters (...)
		LCDWrite(LCD_D, pgm_read_byte(&(ASCII[character - 0x20][index])));
	}
	
	LCDWrite(LCD_D, 0x00);
}

void LCDString(unsigned char *characters) {
	// Your code goes here...
	while(*characters != 0){
		LCDCharacter(*characters);
		characters++;
	}
}

// Set the position in the LCD's memory that we want to begin writing from
void LCDPosition(unsigned char x, unsigned char y) {
	LCDWrite(LCD_C, (0x40 | y )); // Reset row to 0
	LCDWrite(LCD_C, (0x80 | x )); // Reset column to 0
}