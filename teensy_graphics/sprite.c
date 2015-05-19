/*
*	File:	sprite.h
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Portable declaration of byte literals.
*/

#include "sprite.h"
#include "lcd.h"
#include "graphics.h"

void init_sprite(
	Sprite * sprite,
	byte x,
	byte y,
	byte width,
	byte height,
	byte * bitmap
	) {
	sprite->x = x;
	sprite->y = y;
	sprite->width = width;
	sprite->height = height;
	sprite->bitmap = bitmap;
}

void draw_sprite( Sprite * sprite ) {
	if ( !sprite->is_visible ) return;

	// Index into the bitmap. This is updated as we traverse the 
	// pixels of the image.
	int idx = 0;

	for ( int row = 0; row < sprite->height; row++ ) {
		float screen_y = sprite->y + row;

		if ( screen_y < 0 ) continue;

		if ( screen_y >= LCD_Y ) break;

		int col = 0;
		int bitmask = 1 << 7;

		while ( col < sprite->width ) {
			byte pixel = sprite->bitmap[idx] & bitmask;
			float screen_x = sprite->x + col;

			if ( (screen_x >= 0) && ( screen_x < LCD_X ) && pixel ) {
				// Set pixel only if the bit is set. 0 is transparent.
				set_pixel( screen_x, screen_y, 1 );
			}

			col++;

			if ( col % 8 == 0 ) {
				idx++;
				bitmask = 1 << 7;
			}
			else {
				bitmask >>= 1;
			}
		}

		if ( sprite->width % 8 != 0 ) {
			idx++;
		}
	}
}
