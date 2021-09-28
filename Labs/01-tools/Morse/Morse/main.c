/***********************************************************************
 * 
 * Blink a LED and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
/* The preprocessor will process directives that are inserted into the C
 * source code. These directives allow additional actions to be taken on
 * the C source code before it is compiled into object code. Directives
 * are not part of the C language itself.
 *
 * Preprocessor directives begin with a pound (#) symbol and may have 
 * several arguments. Do NOT put a semicolon character at the end of 
 * directives. This is a common mistake.
 */
#define LED_GREEN   PB5 // AVR pin where green LED is connected, timto pin prejmenujeme z PB5 na nas nazev
#define SHORT_DELAY 300 // Delay in milliseconds
#define LONG_DELAY 900 // vytvorime si promenne a definujeme je
#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif

/* Includes ----------------------------------------------------------*/
/* Include another C language file into the current file at the location
 * of the #include statement prior to compiling the source code.
 */
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h>     // AVR device-specific IO definitions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // k vystupum pristupujeme pres registry
	// Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
	// datovy registr drzi udaje o tom, zda se piny chovaji jako vstupy nebo vystupy
	// jeho hodnota je dvojkove cislo, kde bity reprezentuji zpusob chovani prislusnych pinu
    DDRB = DDRB | (1<<LED_GREEN); // zde k hodnote DDR pricteme pin s LEDkou, ktery se ma chovat jako vystup, pricitame tedy 1 na prislusnou posici DDR

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(LONG_DELAY); // 0, mezera

        // Invert LED in Data Register
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<LED_GREEN); //1
		_delay_ms(SHORT_DELAY); // 1, tecka
		PORTB = PORTB ^ (1<<LED_GREEN); //0
		_delay_ms(SHORT_DELAY); // 0, mezera
		PORTB = PORTB ^ (1<<LED_GREEN); // 1
		_delay_ms(LONG_DELAY); // 1, carka
		PORTB = PORTB ^ (1<<LED_GREEN); // 0
    }

    // Will never reach this
    return 0;
}
