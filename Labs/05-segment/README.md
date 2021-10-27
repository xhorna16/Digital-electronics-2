## 7-seg library
1. In your words, describe the difference between Common Cathode and Common Anode 7-segment display.
Pro oba druhy displejů obecně platí, že svítívé diody, tvořící segmenty, jsou zapojeny způsobem, kdy 7 elektrod stejného druhu (polarity) je spojeno v jeden vodič, který je pak vyveden z pouzdra displeje, a 7 zbylých  elektrod opačného druhu je volných a jsou vyvedeny každá zvlášť. Rozdíl mezi CA a CC je potom orientace diod, pro CA jsou sloučenými elektrodami anody diod, v případě CC jsou to jejich katody.
2. Code listing with syntax highlighting of two interrupt service routines (TIMER1_OVF_vect, TIMER0_OVF_vect) from counter application with at least two digits, ie. values from 00 to 59:
```c
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment counter value from 00 to 59.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    num++;
    if (num == 60) num = 0;
}

/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt, running at switching frequency
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/

ISR(TIMER0_OVF_vect)
{
  static uint8_t tempPosition = 0;    
  static int pow10[5] = { 1, 10, 100, 1000, 10000 };
  uint16_t tempValue;
  val = (num % pow10[position+1]) / (pow10[position]);
  SEG_update_shift_regs(val, position);
  position++;
  if (position == 4) position = 0;  
}
```
## Kitchen alarm
![sch](schema.jpg)