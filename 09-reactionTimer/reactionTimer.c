/* Reaction Time:
    This program measure your reaction time in milliseconds.
    The program waits for a keyboard key to be pressed, then it prompts you
    to get ready to press the button connected to PD2 when the LED randomly
    turns on. The program counts how many times, Timer1 has overflown from 
    the moment the LED goes off to the moment the button is pressed.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <USART.h>

#define LED_DDR         DDRB
#define LED_PORT        PORTB
#define BUTTON_PORT     PORTD
#define BUTTON_PIN      PD2
#define BUTTON_INPUT    PIND

//Prototypes
static inline void initTimer1(void);
void randomDelay(void);

//Main
int main(void)
{
    char byte;
    uint16_t timerValue;

    //Inits
    initUSART();
    initTimer1();
    LED_DDR = 0x01;                                     //set led pin as output
    BUTTON_PORT |= (1 << BUTTON_PIN);                   //enable pull-up

    printString("\r\nReaction Timer:\r\n");
    printString("Press any key to start.\r\n");

    //Event Loop
    while (1)
    {
        byte = receiveByte();                           //Read serial for key presses
        printString("Get ready...");
        randomDelay();

        printString("\r\nGo!\r\n");
        LED_PORT = 0x01;

        //Start timing
        TCNT1 = 0;                                      //Reset Timer/Counter 1 value (TCNT1)
        loop_until_bit_is_clear(BUTTON_INPUT, BUTTON_PIN);
        timerValue = TCNT1 >> 4;                            //"bit-shift devide by 8"
        printWord(timerValue);
        printString(" milliseconds\r\n");

        //Clear LED
        LED_PORT = 0x00;
        printString("\r\nPress any key to try again.\r\n");
    }
    return (0);
}

//Functions Declaration
static inline void initTimer1(void)
{
    TCCR1B |= (1 << CS11) | (1 << CS10);                //Setting the prescaler systClk/64 (from 1Mhz to 15625 tick/sec): Timer/Counter control register B (TCCR1B): set Clock Selct (CS12:0) to 011 
}

void randomDelay(void)
{
  uint8_t randomTime;
  _delay_ms(1000);                                      //wait at least 1 sec
  randomTime = (uint8_t) TCNT1;                         //add random time by type-casting the 16-bit TCNT1 to 8-bit number, to keeps the 8 lsb
  while (--randomTime) {                                //max value is 255 ~= 2.5secs
    _delay_ms(10);
  }
}