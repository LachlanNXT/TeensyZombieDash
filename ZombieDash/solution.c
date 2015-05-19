// Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "byte.h"
#include "sprite.h"
#include "cpu_speed.h"

#include "my_functions.h"

// Global Variables
int LEFT = 0;
int RIGHT = 0;
int screen_x = 84;
int screen_y = 48;
int charWidth = 8;
int charHeight = 8;
	

int main() {
	
	setupGame();
	
	// INSERT_CODE_HERE
	//draw_string("eWWZ begins!",0,0);
	
	byte bitmap1[] = {
		UINT( 00000111, 11100000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100000, 00000100 ),
		UINT( 01001100, 00110010 ),
		UINT( 01001100, 00110010 ),
		UINT( 01000000, 00000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100100, 00100100 ),
		UINT( 00010011, 11001000 ),
		UINT( 00010000, 00001000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00000111, 11100000 ),
	};
		
		byte bitmap2[] = {
		UINT( 00000111, 11100000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100000, 00000100 ),
		UINT( 01001100, 00110010 ),
		UINT( 01001100, 00110010 ),
		UINT( 01000000, 00000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100111, 11100100 ),
		UINT( 00010000, 00001000 ),
		UINT( 00010000, 00001000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00000111, 11100000 ),
	};
	
		byte bitmap3[] = {
		UINT( 00000111, 11100000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100000, 00000100 ),
		UINT( 01001100, 00110010 ),
		UINT( 01001100, 00110010 ),
		UINT( 01000000, 00000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100011, 11000100 ),
		UINT( 00010100, 00101000 ),
		UINT( 00010000, 00001000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00000111, 11100000 ),
	};
	
		byte bitmap4[] = {
		UINT( 00000111, 11100000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100000, 00000100 ),
		UINT( 01001100, 00110010 ),
		UINT( 01001100, 00110010 ),
		UINT( 01000000, 00000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 01000001, 10000010 ),
		UINT( 00100000, 00000100 ),
		UINT( 00100000, 00000100 ),
		UINT( 00010011, 11001000 ),
		UINT( 00010100, 00101000 ),
		UINT( 00011000, 00011000 ),
		UINT( 00000111, 11100000 ),
	};
	
	byte *bitmaptemp;
	byte *bitmapa;
	byte *bitmapb;
	
	Sprite my_sprite;
	byte width = 16;
	byte height = 16;
	screen_x -= width;
	screen_y -= height;
	byte x = screen_x/2 - width;
	byte y = screen_y/2;
	init_sprite(&my_sprite, x, y, width, height, bitmap1);
	draw_sprite(&my_sprite);
	
	Sprite my_sprite2;
	init_sprite(&my_sprite2, x + 2*width, y, width, height, bitmap3);
	draw_sprite(&my_sprite2);
	refresh();
	
	refresh();
	
	_delay_ms(100);
	/*
	my_sprite.bitmap = bitmap2;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	my_sprite.bitmap = bitmap3;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	my_sprite.bitmap = bitmap4;
	draw_sprite(&my_sprite);
	refresh();
	_delay_ms(1000);
	clear();
	refresh();
	draw_string("Press a button", 0,0);
	refresh();
	*/
	int add = 1;
	while(1){
	my_sprite.y += add;
	my_sprite2.y -= add;
	if (my_sprite.y < 1) add = -add;
	if (my_sprite.y > screen_y) add = -add;
	buttonCheck();
	clear();
	if (RIGHT == 1 && LEFT == 1) {
	bitmapa = my_sprite.bitmap;
	bitmapb = my_sprite2.bitmap;
	bitmaptemp = bitmapa;
	bitmapa = bitmapb;
	bitmapb = bitmaptemp;
	my_sprite.bitmap = bitmapa;
	my_sprite2.bitmap = bitmapb;
	}
	draw_sprite(&my_sprite);
	draw_sprite(&my_sprite2);
	refresh();
	}
	
	
	return 0;
}

void playGame() {
	
	buttonCheck();
	// set up random number generator
	seedWithButtonPress();
	
	buttonCheck();
	
	int posX;
	int posY;
	for (int i = 0; i<5; i++) {
		posX = rand()%(screen_x - charWidth);
		posY = rand()%(screen_y - charHeight);
		draw_character('Z',posX,posY);
	}
	refresh();
	
	buttonCheck();
	_delay_ms(1000);

	clear();
	
}
	
void buttonCheck() {

	if(PINB & 0b00000010) {
	_delay_ms(50);
	if(PINB & 0b00000010) {
		// Send output to PORTD.
		PORTB |= (1<<3); //PORTB = 0b11111111;
		RIGHT = 1;
	}
	}
	
	if (PINB & 0b00000001 ) {
	_delay_ms(50);
	if (PINB & 0b00000001 ) {
		PORTB |= (1<<2);
		LEFT = 1;
	}
	}
	//(fooo & foo) == fooo)
	
	if ((~PINB & (1<<1)) == (1<<1)) {
		PORTB &= ~((1<<3));
		RIGHT = 0;
	}
	
	if ((~PINB & (1)) == (1) ) {
		PORTB &= ~((1<<2));
		LEFT = 0;
	}
	
}

/**
* Random number generation:
* - 'seedWithButtonPress()': seeds the random number generator with an
* iterated count while waiting for a button press
* - 'randInRange()': uses the random number generator (assumes it has
* been seeded) to produce a random number between
* 'min' (inclusive') and 'max' (not inclusive)
*/
void seedWithButtonPress() {
// turn on teensy LED
PORTD |= 0b01000000;
// Configure port B for the buttons....
DDRB |= 0b00001100;
// Wait for the button press on SW0 while iterating the seed
unsigned int seed = 0;
while (!((PINB >> PB0) & 1)) {
buttonCheck();
seed++;
}
// Seed the random number generator
srand(seed);
// What does dgbI do? where is it from?
// dbgI((int) seed, 10);
// turn off teensy LED
PORTD = 0b00000000;
}

void setupGame() {

	// SW0 and SW1 are connected to pins B0 and B1
	// LED1 and LED2 connected to pins B2 and B3
	// 0 for input 1 for output
	DDRB |= 0b00001100;
    // Teensy LED is connected to D6
    DDRD |= 0b01000000;
    // turn OFF LED initially
	PORTD |= 0b00000000;
	PORTB |= (1<<2)||(1<<3); //not sure why this is here
	
	//initialise clock
	//CLKPR |= 1 << CLKPCE;
	//CLKPR |= 1 << CLKPS0;
	CPU_PRESCALE(CPU_16MHz);
	
	
	LCDInitialise(LCD_DEFAULT_CONTRAST);
	clear();
	
	clear();
	draw_string("ZombieDash v1.0", 4,0); // 15*5 = 75 (84 - 75)/2 = 4
	draw_string("Lachlan Robinson", 2,9); // 16*5 = 80 (84 - 80)/2 = 2
	draw_string("n8845409", 22, 28); // 8*5 = 40 (84 - 40)/2 = 22
	refresh();
	
	while ((LEFT == 0) & (RIGHT == 0)) {
		buttonCheck();
	}
	CountDown();
	
}

void CountDown() {
		clear();
		draw_string("Game Start In: ", 2,22); // 15*5 = 75 (84 - 75)/2 = 4
		draw_string("3", 75,22);
		refresh();
		_delay_ms(1000);
		clear();
		draw_string("Game Start In: ", 2,22); // 15*5 = 75 (84 - 75)/2 = 4
		draw_string("2", 75,22);
		refresh();
		_delay_ms(1000);
		clear();
		draw_string("Game Start In: ", 2,22); // 15*5 = 75 (84 - 75)/2 = 4
		draw_string("1", 75,22);
		refresh();
		_delay_ms(1000);
		clear();
}

