#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

static inline void initADC0(void);

int main(void)
{
    //Inits
    uint8_t ledValue;
    uint16_t adcValue;
    uint8_t i;
    
    initADC0();
    LED_DDR = 0xff;

    //Event loop
    while (1)
    {
        ADCSRA |= (1 << ADSC);                      //start ADC conversion
        loop_until_bit_is_clear(ADCSRA, ADSC);      //wait until done
        adcValue = ADC;                             //read ADC
        ledValue = (adcValue >> 7);                 //ADC is a 10bit value.Take the 3 msb to generate a value from 0 to 7

        //light up leds
        LED_PORT = 0;
        for (i = 0; i <= ledValue; i++)
        {
            LED_PORT |= (1 << i);
        }
        _delay_ms(50);
    }
    return(0);
}

static inline void initADC0(void){
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADEN);
}
