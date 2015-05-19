/*	CAB202: Assignment 2 - ZombieDash
*	Zombie Maps Library - Individual
*
*	B.Talbot, May 2015
*	Queensland University of Technology
*
*	This library provides functions for obtaining two predetermined maps for
*	the ZombieDash game. The maps are:
*		1. A small 76x48 map for use in the non-scrollable version
*		2. A big map for use in the scrolling implementation
*	
*	Maps are represented by a collection of either horizontal or vertical lines. For
*	a map of consisting of 'n' lines, this library provides the functions to get the 
*	array of '4*n' integers defining the map. The array of integers is provided in 
*	the following format:
*		int lines[] = {
*			line_0_x0, line_0_y0, line_0_x1, line_0_y1,
*			line_1_x0, line_1_y0, line_1_x1, line_1_y1,
			...
*			line_n_x0, line_n_y0, line_n_x1, line_n_y1,
*		};
*	where (x0,y0) and (x1,y1) are the start and end points respectively of each line
*	in the map.
*
*	The map definitions are stored in program memory, but obtaining a copy (through 
*	the malloc_*() functions) creates a copy in RAM. From that point on, you should be
*	very careful with your memory operations (and management), as unpredictable
*	behavior will result from any errors in your use of memory.
*
*	Demonstration functions are provided to help you confirm that you are using this
*	library correctly. This library must be used in conjunction with the Teensy Graphics 
*	library.
*/
#ifndef ZOMBIE_MAPS_H_
#define ZOMBIE_MAPS_H_

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>

#include "graphics.h"
#include "byte.h"

/***********************************************************************************
/***************************** SMALL MAP (76x48) ***********************************	
/***********************************************************************************/
/*	Function: 
*		get_line_count_small(void)
*	Inputs: 
*		None
*	Output:
*		Number of lines in the small map stored by this library.
*	Details:
*		Returns the number of lines in the small, non-scrollable version of the
*		ZombieDash map.
*/
unsigned char get_line_count_small(void);

/*	Function: 
*		unsigned int* malloc_lines_small(unsigned int size)
*	Inputs: 
*		size: size (number of bytes) of memory that you are requesting to allocate for 
*			storing the small ZombieDash map
*	Output:
*		Pointer to the allocated block of memory. If the size was incorrect, or 'malloc()' 
*			failed to allocated the memory, this pointer will be NULL. 
*	Details:
*		This function is provided as a custom version of malloc (to ensure that memory
*		is allocated dynamically rather than large static arrays) for the small, non-
*		scrollable ZombieDash map. The function checks that the size of memory requested 
*		matches the size required to store the map. If the requested size matches exactly, 
*		a new pointer is returned (and saved internally in the library). Otherwise (and 
*		also if 'malloc()' can't successfully allocated the requested amount of memory), 
*		a NULL pointer is returned.
*/
unsigned int* malloc_lines_small(unsigned int size);

/*	Function: 
*		void copy_lines_small(unsigned int* lines)
*	Inputs: 
*		lines: pointer to a block of memory that the small ZombieDash map will be copied
*			into
*	Output:
*		None
*	Details:
*		This function copies the library's data for the small ZombieDash map from program
*		memory (PROGMEM), into the memory pointed to by the input argument. You must call
*		'malloc_lines_small()' successfully first before calling this function! If the 
*		pointer supplied is NULL or does not match the pointer returned by the last call to 
*		'malloc_lines_small()', this function will return immediately (i.e. no copying will
*		be performed).
*/
void copy_lines_small(unsigned int* lines);


/***********************************************************************************
/********************************* BIG  MAP ****************************************	
/***********************************************************************************/
/*	Function: 
*		get_line_count_big(void)
*	Inputs: 
*		None
*	Output:
*		Number of lines in the big map stored by this library.
*	Details:
*		Returns the number of lines in the big, scrollable version of the ZombieDash 
*		map.
*/
unsigned char get_line_count_big(void);

/*	Function: 
*		unsigned int* malloc_lines_big(unsigned int size)
*	Inputs: 
*		size: size (number of bytes) of memory that you are requesting to allocate for 
*			storing the big ZombieDash map
*	Output:
*		Pointer to the allocated block of memory. If the size was incorrect, or 'malloc()' 
*			failed to allocated the memory, this pointer will be NULL. 
*	Details:
*		This function is provided as a custom version of malloc (to ensure that memory
*		is allocated dynamically rather than large static arrays) for the big, scrollable 
*		ZombieDash map. The function checks that the size of memory requested matches the 
*		size required to store the map. If the requested size matches exactly, a new 
*		pointer is returned (and saved internally in the library). Otherwise (and also if 
*		'malloc()' can't successfully allocated the requested amount of memory), a NULL 
*		pointer is returned.
*/
unsigned int* malloc_lines_big(unsigned int size);

/*	Function: 
*		void copy_lines_big(unsigned int* lines)
*	Inputs: 
*		lines: pointer to a block of memory that the big ZombieDash map will be copied
*			into
*	Output:
*		None
*	Details:
*		This function copies the library's data for the big ZombieDash map from program
*		memory (PROGMEM), into the memory pointed to by the input argument. You must call
*		'malloc_lines_small()' successfully first before calling this function! If the 
*		pointer supplied is NULL or does not match the pointer returned by the last call to 
*		'malloc_lines_small()', this function will return immediately (i.e. no copying will
*		be performed).
*/
void copy_lines_big(unsigned int* lines);

/***********************************************************************************
/**************************** DEMO MAP FUNCTIONS ***********************************	
/***********************************************************************************/
/*	Function: 
*		demo_map_small(void)
*	Inputs: 
*		None
*	Output:
*		None
*	Details:
*		This function demonstrates the small, non-scrollable ZombieDash map (and a dummy
*		score bar on the left hand side). Use this function to check that you have
*		included this library correctly, and have drawn the map in your game correctly.
*/
void demo_map_small(void);

/*	Function: 
*		demo_map_big(void)
*	Inputs: 
*		None
*	Output:
*		None
*	Details:
*		This function demonstrates the big, scrollable ZombieDash map (and a dummy
*		score bar on the left hand side). Use this function to check that you have
*		included this library correctly, and have drawn the map in your game correctly.
*/
void demo_map_big(void);

#endif