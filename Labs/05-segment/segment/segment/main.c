/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC

volatile uint8_t cnt0 = 0; // 
volatile uint8_t cnt1 = 0; // druhy citac
/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Display decimal counter values on SSD (Seven-segment 
 *           display) when 16-bit Timer/Counter1 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Configure SSD signals
    SEG_init();

    // Test of SSD: display number '3' at position 0
                        //  abcdefgDP   p3 p2 p1 p0
    SEG_update_shift_regs(0b00001101, 0b00010000); // posledni 4 bity nefunkcni
    // Configure 16-bit Timer/Counter1 for Decimal counter
    // Set the overflow prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable(); //jen predstupen povoleni preruseni
    
    TIM0_overflow_4ms(); // pro pouziti vice displehju
    TIM0_overflow_interrupt_enable();
    // Enables interrupts by setting the global interrupt mask
    sei(); // globalni povoleni preruseni, zakaze se globalne pomoci "cli"

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
        
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment decimal counter value and display it on SSD.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
    cnt0++;
    if (cnt0 > 9)
    {    cnt0=0;
         cnt1++; // doplneni
         if (cnt1 > 5)
            cnt1 = 0;
    }        
    SEG_update_shift_regs(cnt0, 0);
}
ISR(TIMER1_OVF_vect)
{
    static uint8_t pos = 0; // klicove slovo static uvnitr funkce znamena??
    pos++
    if (pos > 1)
    {    
        pos = 0;
    }    
    SEG_update_shift_regs(cnt0, 0);
}