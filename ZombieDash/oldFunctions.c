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