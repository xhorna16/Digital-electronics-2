/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD display when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");

    
    lcd_gotoxy(11, 0);
    lcd_putc('a');

    lcd_gotoxy(1, 1);
    lcd_putc('b');
    

    lcd_gotoxy(11, 1);
    lcd_putc('c');
    
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set the overflow prescaler to 16 ms and enable interrupt
TIM2_overflow_16ms();
TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

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
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD display every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER2_OVF_vect)
{
 static uint8_t number_of_overflows = 0;
 static uint8_t tens = 0;        // Tenths of a second
 static uint8_t secs = 0;        // Seconds
 char lcd_string[2] = "  ";      // String for converting numbers by itoa()

 number_of_overflows++;
 if (number_of_overflows >= 6)
 {
     // Do this every 6 x 16 ms = 100 ms
     number_of_overflows = 0;

     // WRITE YOUR CODE HERE

 }
     tens++;
     if(tens >= 10){
         tens = 0;
         secs++;
     }
     if(secs >= 60){
         secs = 0;
     }

 

 // Display tenths of seconds
    itoa(tens, lcd_string, 10);
    lcd_gotoxy(7,0);
    lcd_puts(lcd_string);
    
  // Display seconds
    itoa(secs, lcd_string, 10);
    if(secs < 10){
      lcd_gotoxy(5,0);
    } else{
        lcd_gotoxy(4,0);
    }
    lcd_puts(lcd_string);
 

}
