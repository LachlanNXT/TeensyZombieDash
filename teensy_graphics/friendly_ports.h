/*
*	File:	friendly_ports.h
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Some macros to make the manipulation of teensy buttons and LEDs less putrid.
*/

#ifndef __FRIENDLY_PORTS__
#define __FRIENDLY_PORTS__

#include <avr/io.h>

// define the bit mask and register for LED 0 (left)
#define LED0 (1<<2)
#define LED0_PORT PORTB

// define the bit mask and register for LED 1 (right) 
#define LED1 (1<<3)
#define LED1_PORT PORTB

// define the bit mask and register for LED2 (What I'm calling the little yellow LED) 
#define LED2 (1<<6)
#define LED2_PORT PORTD

// define the bit mask and register for switch 0 (left)
#define SW0 (1<<0)
#define SW0_PORT PINB

// define the bit mask and register for switch 1 (right)
#define SW1 (1<<1)
#define SW1_PORT PINB

// Turns on a LED, which should be one of LED0, LED1 or LED2
#define turn_on(led) led##_PORT |= (led)

// Turns on a LED, which should be one of LED0, LED1 or LED2
#define turn_off(led) led##_PORT &= ~(led)

// Turns on a LED, which should be one of LED0, LED1 or LED2
#define pressed(button) ((button##_PORT & (button)) != 0)

// Busy-loop wait until a condition becomes true.
#define wait_until( cond ) while ( !cond ) {}

// Turn on left LED, wait for button.
#define db_wait(zzz) { \
	turn_on( LED0 ); \
	wait_until( pressed( SW0 ) ); \
	turn_off( LED0 ); \
}

#endif