#include <avr/io.h> 
#include <util/delay.h> 
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"

volatile int buttonPressed = 0;
int previousButton = 0;

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

ISR(PCINT0_vect)
{
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