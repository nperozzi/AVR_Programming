#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

static inline void blinkLED(void);

int main(void)
{
    PORTD |= (1 << PD2);
    DDRB = (1 << 0);
    blinkLED();

    initUSART();
    transmitByte('0');

    while(1)
    {
        if(bit_is_clear(PIND,PD2)){
            transmitByte('X');
            blinkLED();
        }
    }
    return 0;
}

static inline void blinkLED(void)
{
    PORTB = (1 << 0);
    _delay_ms(500);
    PORTB &= ~(1 << 0);
}