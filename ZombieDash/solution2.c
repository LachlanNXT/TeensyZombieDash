// Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "graphics.h"
#include "byte.h"
#include "sprite.h"
#include "cpu_speed.h"

#include "my_functions.h"

#define NUM_BLOCKS 10
#define MAX_CLOCK_COUNTER_FOR_100MSECOND 5

int main() {
	
	setupGame();
	
	// INSERT_CODE_HERE
	//draw_string("eWWZ begins!",0,0);
	
	byte bitHero [] = {
		BYTE( 10100000),
		BYTE( 11100000),
		BYTE( 10100000),
	};
		
	byte bitZombie [] = {
		BYTE( 11100000),
		BYTE( 01000000),
		BYTE( 11100000),
	};
	
	Sprite my_sprite;
	my_pointer = &my_sprite;
	byte width = 3;
	byte height = 3;
	screen_x -= width;
	screen_y -= height;
	byte x = screen_x/2 - width;
	byte y = screen_y/2;
	init_sprite(my_pointer, x, y, width, height, bitHero);
	draw_sprite(my_pointer);
	
	Sprite my_sprite2;
	my_pointer2 = &my_sprite2;
	init_sprite(my_pointer2, x + 2*width, y, width, height, bitZombie);
	draw_sprite(my_pointer2);
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
	//int add = 1;
	int notRIGHT = 1;
	int notLEFT = 1;
	GAMEON = 1;
	while(1){
	/*
		my_pointer -> y += add;
		my_pointer2 -> y -= add;
		if (my_pointer -> y < 1) add = -add;
		if (my_pointer -> y > screen_y) add = -add;
	*/
		clear();

		if (RIGHT == 0) {
			notRIGHT = 1;
		}
		if (LEFT == 0) {
			notLEFT = 1;
		}
		
		if (RIGHT && notRIGHT) {
			notRIGHT = 0;
			Direction = (Direction-1);
			if (Direction < 0) {
			Direction = 3;
			}
			//bitmapa = my_pointer -> bitmap;
			//bitmapb = my_pointer2 -> bitmap;
			//bitmaptemp = bitmapa;
			//bitmapa = bitmapb;
			//bitmapb = bitmaptemp;
			//my_pointer -> bitmap = bitmapa;
			//my_pointer2 -> bitmap = bitmapb;
			
		}
		if (LEFT & notLEFT) {
			notLEFT = 0;
			Direction = (Direction+1)%4;
			
		}
		
		draw_sprite(my_pointer);
		draw_sprite(my_pointer2);
		drawScreen();	
		refresh();
	}
	
	
	return 0;
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
	
	PinChangeInit();
	TimerInit();
	
	clear();
	draw_string("ZombieDash v1.0", 4,0); // 15*5 = 75 (84 - 75)/2 = 4
	draw_string("Lachlan Robinson", 2,9); // 16*5 = 80 (84 - 80)/2 = 2
	draw_string("n8845409", 22, 28); // 8*5 = 40 (84 - 40)/2 = 22
	refresh();
	
	seedWithButtonPress();
	buttonCheck();
	CountDown();
	
}

void CountDown() {
	for (char i= 0x3; i>0x0; i--) {
		clear();
		draw_string("Game Start In: ", 2,22); // 15*5 = 75 (84 - 75)/2 = 4
		draw_character((0x30 + i), 75,22);
		refresh();
		_delay_ms(1000);
	}
}

void buttonCheck() {

	RIGHT = 0; LEFT = 0;
	
	if(PINB & 0b00000010) {
	_delay_ms(50);
	if(PINB & 0b00000010) {
		// Send output to PORTD.
		//PORTB |= (1<<3); //PORTB = 0b11111111;
		RIGHT = 1;
	}
	}
	
	if (PINB & 0b00000001 ) {
	_delay_ms(50);
	if (PINB & 0b00000001 ) {
		//PORTB |= (1<<2);
		LEFT = 1;
	}
	}
	//(fooo & foo) == fooo)
	/*
	if ((~PINB & (1<<1)) == (1<<1)) {
		PORTB &= ~((1<<3));
		RIGHT = 0;
	}
	
	if ((~PINB & (1)) == (1) ) {
		PORTB &= ~((1<<2));
		LEFT = 0;
	}
	*/
}

int randInRange(int min, int max) {
	int out = min + rand()%(max+1 - min);
	return out;
}

void seedWithButtonPress() {
// turn on teensy LED
PORTD |= 0b01000000;
// Configure port B for the buttons....
DDRB |= 0b00001100;
// Wait for the button press on SW0 while iterating the seed
unsigned int seed = 0;
while (!RIGHT && !LEFT) {
seed++;
}
// Seed the random number generator
srand(seed);
// What does dgbI do? where is it from?
// dbgI((int) seed, 10);
// turn off teensy LED
PORTD = 0b00000000;
}

void PinChangeInit(void)
{
	//Enable PCINT0 and PCINT1 (both buttons) in the PCMSK0 register
	PCMSK0 |= (1<<PCINT0);
	PCMSK0 |= (1<<PCINT1);

	//Enable Pin change interrupts in the Pin Change Interrupt Control Register
	PCICR |= (1<<PCIE0);
	
	//Set the PCINT0 and PCINT1 interrupts to trigger on rising edge
	EICRA |= ((1<<ISC00)&&(1<<ISC01)&&(1<<ISC10)&&(1<<ISC11));
		
	//Ensure to enable global interrupts as well.
	sei();
}

ISR(PCINT0_vect) {	
	RIGHT = 0; LEFT = 0;
	
	if(PINB & 0b00000010) {
	//_delay_ms(50);
	//if(PINB & 0b00000010) {
		// Send output to PORTD.
		//PORTB |= (1<<3); //PORTB = 0b11111111;
		RIGHT = 1;
	//}
	}
	
	if (PINB & 0b00000001 ) {
	//_delay_ms(50);
	//if (PINB & 0b00000001 ) {
		//PORTB |= (1<<2);
		LEFT = 1;
	//}
	}
	/*
	buttonPressed=0;
	if ((PINB>>PINB0)&1){
		buttonPressed = 1;
	}
	if ((PINB>>PINB1)&1){
		if (buttonPressed){
			buttonPressed = 3;
		} else {
			buttonPressed = 2;
		}
	}
	if (buttonPressed==1){
		heroX = heroX-3;
	} else if (buttonPressed==2){
		heroX = heroX+3;
	}
	clear();
	draw_character('*',heroX,heroY);
	refresh();
	*/
}

void TimerInit(void)
{
	//Set to Normal Timer Mode using TCCR0A and TCCR0B
	TCCR0A &= ~((1<<WGM01)|(WGM00));
	TCCR0B &= ~((1<<WGM02));
	
	//Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(Clock Speed/Prescaler)
	//Prescaler = 1024
	//Timer Speed = 128 nano seconds NOT 16MHZ
	//Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer) NOT 16MHZ
	TCCR0B |= (1<<CS02)|(1<<CS00);
	TCCR0B &= ~((1<<CS01));
	
	//Enable TOIE0 interrupt in the TIMSK0 register
	TIMSK0 |= (1<<TOIE0);
	
	//Ensure to enable global interrupts as well.
	sei();
}


ISR(TIMER0_OVF_vect)
{
	//Clear the flag by writing a one
	TIFR0 |= (1<<TOV0);
	//Add one to our clockCounter
	clockCounter++;
	//DEBUG LED
	//PORTB ^= (1<<PINB2);
	//Check to see if our clockCounter is greater/equal to than our MAX_CLOCK_COUNTER_FOR_100MSECOND
	if(clockCounter >= MAX_CLOCK_COUNTER_FOR_100MSECOND && GAMEON)
	{
		//PORTB ^= (1<<PINB3);
		//Reset clockCounter
		clockCounter = 0;
		heroForward();	
	}
}

void heroForward(void) {

if (Direction == 0) {
	HeroY = 1;
	HeroX = 0;
	if (my_pointer -> y > screen_y-1) {
	HeroY = 0;
	}
}
if (Direction == 1) {
	HeroX = 1;
	HeroY = 0;
	if (my_pointer -> x > screen_x-1) {
	HeroX = 0;
	}
}
if (Direction == 2) {
	HeroY = -1;
	HeroX = 0;
	if (my_pointer -> y < 10) {
	HeroY = 0;
	}
}
if (Direction == 3) {
	HeroX = -1;
	HeroY = 0;
	if (my_pointer -> x < 2) {
	HeroX = 0;
	}
}

my_pointer -> x += HeroX;
my_pointer -> y += HeroY;

}

void drawScreen(void) {
	draw_line(0,8,screen_x_Full,8);
	draw_line(0,8,0,screen_y_Full);
	draw_line(screen_x_Full,8,screen_x_Full,screen_y_Full);
	draw_line(0,screen_y_Full,screen_x_Full,screen_y_Full);
	draw_string("L: ",0,0);
	draw_character((0x30 + Lives),11,0);
	draw_string("S: ", 21,0);
	draw_character((0x30 + Score),31,0);
	draw_character((0x30 + Direction),70,0);

}