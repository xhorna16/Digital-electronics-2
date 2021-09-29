/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5 // ledka na desce
#define LED_2 PC0     // druha ledka AVR pin where green LED is connected
#define BLINK_DELAY 500
#define BUTTON PD0 // tlacitko
#ifndef F_CPU
# define F_CPU 16000000     // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>
#include <avr/sfr_defs.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs when a push button is pressed.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Green LED at port B
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN); //kdybychom chteli ledku rozsvitit, pak bychom poouzili OR a bez negace

    // Configure the second LED at port C
    DDRC = DDRC | (1<<LED_2); // nastaveni vystupu
    PORTC = PORTC & ~(1<<LED_2);  // sviti, pokud je zapojena jako "active-LOW"
    // Configure Push button at port D and enable internal pull-up resistor
    DDRD = DDRD & ~(1 << BUTTON); //vstupni registr, bude tam NULA
    
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
       // _delay_ms(BLINK_DELAY); //ocad dolu pubvodni kod pro kmitani ledek
        //PORTB = PORTB ^ (1<<LED_GREEN);
        //_delay_ms(BLINK_DELAY);
        //PORTC = PORTC ^ (1<<LED_2);
        if(bit_is_clear(PIND, PD0)) //kazda ledka je zapojena jinak (HIGH a LOW), takze se cvakanim budou prepinat, PIN je dalsi drugh registru
        {
            PORTB = PORTB ^ (1<<LED_GREEN); //behame ve smycce a sledujeme, zda je port v nule, funkce se proto musi upravit
            PORTC = PORTC ^ (1<<LED_2);
            loop_until_bit_is_clear(PIND,BUTTON); //doplnime aby to lepsi fungovalo
        }   
    }

    // Will never reach this
    return 0;
}