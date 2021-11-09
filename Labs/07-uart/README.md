## Analog to digital conversion
| **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0   | 0 |
   | Up     | 0,495&nbsp;V | 101 | 99 |
   | Down   |     1,203&nbsp;V  |  246   | 256 |
   | Left   |    1,970&nbsp;V   |   403  | 410 |
   | Select |    3,182&nbsp;V   |   651  | 640 |
   | none   |   5&nbsp;V    |   1023  | 1023 |
## Interrupt service routine
```c
ISR(ADC_vect)
{
        uint16_t value = 0;
        char lcd_string[4] = "0000";
        char lcd_hex_string[3] = "000";

        value = ADC;                  // Copy ADC result to 16-bit variable
        itoa(value, lcd_string, 10);  // Convert decimal value to string
        itoa(value, lcd_hex_string, 16);
        uart_puts(lcd_string);
        uart_puts("\n\r");
        uart_puts(lcd_hex_string);
        uart_puts("\n\r");
        lcd_gotoxy(8,0);
        lcd_puts("    ");
        lcd_gotoxy(8,0);
        lcd_puts(lcd_string);
        lcd_gotoxy(12,0);
        lcd_puts(" ");
        lcd_gotoxy(13,0);
        lcd_puts("   ");
        lcd_gotoxy(13,0);
        lcd_puts(lcd_hex_string);
        switch(value){
        case 0 ... 90       : lcd_gotoxy(8,1); lcd_puts("right"); uart_puts("right"); uart_puts("\r\n");  break;
        case 91 ... 200     : lcd_gotoxy(8,1); lcd_puts("up"); uart_puts("up"); uart_puts("\r\n");  break;
        case 201 ... 400    : lcd_gotoxy(8,1); lcd_puts("down"); uart_puts("down"); uart_puts("\r\n");  break;
        case 401 ... 600    : lcd_gotoxy(8,1); lcd_puts("left"); uart_puts("left"); uart_puts("\r\n");  break;
        case 601 ... 1000   : lcd_gotoxy(8,1); lcd_puts("select"); uart_puts("select"); uart_puts("\r\n");  break;
        case 1001 ... 1050  : lcd_gotoxy(8,1); lcd_puts("none"); uart_puts("none"); uart_puts("\r\n");  break;
        default:lcd_puts("       ");
}
```
## UART communication
[2.png](2.png)!
## Thermometer
(1.png)[1.png]!
