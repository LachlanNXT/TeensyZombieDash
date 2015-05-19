/*
 * Graphics.c
 *
 * Created: 20/12/2012 11:59:59 PM
 *  Author: Michael a.k.a Not that there's anything wrong with that
 */ 
#include <avr/pgmspace.h>
#include "graphics.h"
#include "lcd.h"

unsigned char screenBuffer[LCD_BUFFER_SIZE]; // Our screen buffer array

void refresh(void) {
	// Reset our position in the LCD RAM
	LCDPosition(0,0);
	// Iterate through our buffer and write each byte to the LCD.
	unsigned int i;
	for(i = 0; i < LCD_BUFFER_SIZE; i++){
		LCDWrite(LCD_D, screenBuffer[i]);
	}
	
}

void clear(void) {
	unsigned int i;
	for(i = 0; i < LCD_BUFFER_SIZE; i++){
		 screenBuffer[i] = 0;
	}
}
void set_pixel(unsigned char x, unsigned char y, unsigned char value){
	// Sanity check (bad things happen otherwise...)
	if (x >= LCD_X || y >= LCD_Y) {
		return;
	}

	// Calculate the pixel 'subrow', within that LCD row
	unsigned char row = y/8;
	unsigned char subrow = y%8;
	
	// Set that particular pixel in our screen buffer
	if (value){
		screenBuffer[row*84+x] |= (1 << subrow); //Set Pixel 
	} else {
		screenBuffer[row*84+x] &= ~(1 << subrow); //Clear Pixel
	}
}

void draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	// Insert algorithm here.
	if (x1 == x2) {
		//Draw Horizontal line
		unsigned char i;
		for (i = y1; i <= y2; i++){
			set_pixel(x1, i, 1);
		}			
	} else if (y1 == y2){
		//Draw vertical line
		unsigned char i;
		for (i = x1; i <= x2; i++){
			set_pixel(i, y1, 1);
		}		
	} else {
		//As if I am going to bother with diagonal
		// Figure out octant
		unsigned int oct;
		float g = ((float) y2-y1)/((float) x2-x1);
		if (x2 > x1) {
			if (g > 1) {
				oct = 1;
			} else if (g <= 1 && g > 0) {
				oct = 0;
			} else if (g <= 0 && g > -1) {
				oct = 7;
			} else {
				oct = 6;
			}
		} else {
			if (g > 1) {
				oct = 5;
			} else if (g <= 1 && g > 0) {
				oct = 4;
			} else if (g <= 0 && g > -1) {
				oct = 3;
			} else {
				oct = 2;
			}
		}

		// Translate octants to settings
		unsigned int useX;
		switch(oct) {
			case 0:
			case 3:
			case 4:
			case 7:
				useX = 1;
				break;
			case 1:
			case 2:
			case 5:
			case 6:
				useX = 0;
				break;

		}
		unsigned int i1, i, i2, c;
		float dx = (float) x2-x1, dy = (float) y2-y1, m;
		if (useX) {
			m = dy/dx;
			c = y1; i1 = x1; i2 = x2;
		} else {
			m = dx/dy;
			c = x1; i1 = y1; i2 = y2;
		}

		int flipM;
		switch(oct) {
			case 0:
			case 1:
			case 2:
			case 7:
				flipM = 1;
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				flipM = -1;
				break;
		}

		// Perform the actual loop
		float err = 0.0;
		for (i = i1; (i2>i1) ? i <= i2 : i >= i2; (i2>i1) ? i++ : i--) {
			(useX) ? set_pixel(i, c, 1) : set_pixel(c, i, 1);
			err += ABS(m);
			if (err > 0.5f) {
				(SIGN(m*flipM) > 0) ? c++ : c--;
				err -= 1.0f;
			}
		}
	}
}

void draw_character(unsigned char character, unsigned char top_left_x, unsigned char top_left_y) {
	int i, j;
	int char_width = 5;
	int char_height = 8;
	
	// loop through each pixel in the character array and plot each one individually
	for (i = 0; i<char_width; i++) {
		for (j = 0; j<char_height; j++) {
			set_pixel(top_left_x+i, top_left_y+j, (pgm_read_byte(&(ASCII[character - 0x20][i])) & (1 << j)) >> j);
		}
	}
}

void draw_string( char *characters, unsigned char top_left_x, unsigned char top_left_y ) {
	int i = 0;
	while (*characters != 0) {
		draw_character(*(characters), top_left_x+i*5, top_left_y);
		// Add a column of spaces here if you want to space out the lettering.
	    // See lcd.c for a hint on how to do this.
		characters++;
		i++;
	}
}




// Extend this file with whatever other graphical functions you need for your assignment...
/*
void drawBall(unsigned char x, unsigned char y){
	SetPixel(x,y,1);

	SetPixel(x,y-1,1);
	//SetPixel(x,y-2,1);

	SetPixel(x,y+1,1);
	//SetPixel(x,y+2,1);

	SetPixel(x-1,y,1);
	//SetPixel(x-2,y,1);
	
	SetPixel(x+1,y,1);	
	//SetPixel(x+2,y,1);	

	SetPixel(x+1,y+1,1);	
	SetPixel(x-1,y+1,1);	
	SetPixel(x+1,y-1,1);	
	SetPixel(x-1,y-1,1);	
}


void drawBox1(unsigned char y){
	int x;
	for (x = y-boxsize/2; x < y+boxsize/2; x++){
		SetPixel(0,x,1);
		SetPixel(1,x,1);
	}

}	



void drawBox2(unsigned char y){
	int x;
	for (x = y-boxsize/2; x < y+boxsize/2; x++){
		SetPixel(83,x,1);
		SetPixel(82,x,1);
	}
}
*/