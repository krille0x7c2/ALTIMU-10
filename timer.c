#include <avr/io.h>
#include <avr/interrupt.h>

  
// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 8
    TCCR1B |= (1 << CS11);
  
    // initialize counter
    TCNT1 = 0;
  
}