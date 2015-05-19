// Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Libraries
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_functions"

int randInRange(min, max) {
	out = min + rand()%(max+1 - min);
	return out;
}

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