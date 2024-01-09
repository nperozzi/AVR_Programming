#include <avr/io.h>
#include <util/delay.h>

int main()
{
    PORTD |= (1 << PD2);
    DDRB = 0xff;

    while(1)
    {
        if((PIND & (1 << PD2)) == 0)  //macro: bit_is_clear(PIND,PD2)
        {
            PORTB = 0x01;
        }
        else
        {
            PORTB = 0x00;
        }
    }
    return 0;
}
