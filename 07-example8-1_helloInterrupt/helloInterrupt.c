#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pinDefines.h"

#define DEBOUNCE_TIME 1000

ISR(INT0_vect){         //ISR for INT0
    if(debounce())
    {
        PORTB |= (1 << PB1);     //turn on LED1
    }
    else{
        PORTB &= ~(1 << PB1);    //turn off LED1
    }
}

void initInterrupt0(void)
{
    EIMSK |= (1 << INT0); //enable INT0
    EICRA |= (1 << ISC00); //trigger interrupt when change
    sei(); //assemly to set the global interrupt enable bit 
}

uint8_t debounce(void)
{
    if(bit_is_clear(PIND, PD2))
    {
        _delay_ms(DEBOUNCE_TIME);
        if(bit_is_clear(PIND, PD2))
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    //Inits:
    DDRB = 0xff;
    BUTTON_PORT |= (1 << PD2); /*enable pullup */
    initInterrupt0();

    while (1){
        _delay_ms(200);
        LED_PORT ^= (1 << LED0);
    }
    return(0); 
}