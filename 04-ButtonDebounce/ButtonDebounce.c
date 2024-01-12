#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME  1000

uint8_t debounce(void);


int main(void)
{
    uint8_t buttonWasPressed;
    PORTD |= (1 << PD2);
    DDRB = (1 << PB0);

    while(1)
    {
        if(debounce())
        {
            if(buttonWasPressed == 0)
            {
                PORTB ^= (1 << PB0);
                buttonWasPressed = 1;
            }
        }
        else
        {
            buttonWasPressed = 0;
        }
    }
    return 0;
}

uint8_t debounce(void)
{
    if(bit_is_clear(PIND,PD2))
    {
        _delay_us(DEBOUNCE_TIME);
        if(bit_is_clear(PIND,PD2))
        {
            return 1;
        }
    }
    return 0;
}