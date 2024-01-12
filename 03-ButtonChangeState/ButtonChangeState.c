#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    uint8_t buttonWasPressed;
    PORTD |= (1 << PD2);
    DDRB = (1 << PB0);

    while(1)
    {
        if((PIND & (1 << PD2)) == 0)
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