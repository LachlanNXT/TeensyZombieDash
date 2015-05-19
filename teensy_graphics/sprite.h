#ifndef __SPRITE__
#define __SPRITE__

#include "byte.h"

typedef struct sprite {
	float x;			// Horizontal offset to top-left corner of sprite.
	float y;            // Vertical offset to top-left corner of sprite.
	byte width;         // Pixel width of sprite.
	byte height;        // Pixel height of sprite. 
	byte is_visible;    // Boolean visibility of sprite.
	byte * bitmap;      // Pizel data, bit-packed into byte array.
	float dx;			// The horizontal step size for a "moving" sprite.
	float dy;           // The vertical step size for a "moving" sprite.
} Sprite;

void init_sprite( Sprite * sprite, byte x, byte y, byte width, byte height, byte * bitmap );

void draw_sprite( Sprite * sprite );

#endif