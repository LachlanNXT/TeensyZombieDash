/*
 * Graphics.h
 *
 * Created: 20/12/2012 11:59:59 PM
 *  Author: Michael a.k.a Mickey Mouse
 */ 


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "ascii_font.h"
#include "lcd.h"

// The size of the buffer we need to represent the LCD RAM
#define LCD_BUFFER_SIZE (LCD_X * (LCD_Y / 8))

// #define boxsize 14
 
#define ABS(x)							((x >= 0) ? x : -1*x)
#define SIGN(x)							((x > 0) - (x < 0))
 
// We declare the screen buffer here as extern, since it is defined in our C file.
// This way other files have will have direct access to the buffer if they include Graphics.h
extern unsigned char screenBuffer[LCD_BUFFER_SIZE];

// LCD library interfacing
void refresh(void); //PresentBuffer()

// Buffer management
void clear(void); //ClearBuffer();
void set_pixel(unsigned char x, unsigned char y, unsigned char value);

// Basic drawing functions (not used with sprites)
void draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2); // include bresenhams
// void draw_box(unsigned char top_left_x, unsigned char top_left_y, unsigned char width, unsigned char height);

void draw_character(unsigned char character, unsigned char top_left_x, unsigned char top_left_y);
void draw_string(char *characters, unsigned char top_left_x, unsigned char top_left_y);

#endif /* GRAPHICS_H_ */