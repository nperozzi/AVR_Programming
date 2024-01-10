/* Capacitive touch sensor.
    This program controls a capacitive touch sensor by counting how many times the capacitor is charged and discharged in a period of time.
    The program uses pin-change interrupt to count each charge-discharge cycle and evaluates if the sensor was pressed or not.
    The charge-discharge cycle count gets transmitted through serial.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/power.h>
#include "USART.h"

#define SENSE_TIME              50
#define THRESHOLD               6000
#define CAP_DDR                 DDRC
#define CAP_PORT                PORTC
#define CAP_PIN                 PC1
#define LED_DDR                 DDRB
#define LED_PORT                PORTB
#define LED_PIN                 PB0

//Global Variables
volatile uint16_t chargeCycleCount;

//Prototypes
void initPinChargeInterrupt(void);
ISR(PCINT1_vect);

//Main
int main(void)
{
    //Inits
    clock_prescale_set(clock_div_1);            //Set clock to full speed for faster sampling
    MCUCR |= (1 << PUD);                        //Desable pullup in PC1 by desabling all pullups
    CAP_PORT |= (1 << CAP_PIN);                 //Set capacitor as high for charging when it is set as output
    initPinChargeInterrupt();                   //Init interrupt

    LED_DDR = (1 << LED_PIN);                   //Set LED as output

    initUSART();                                //Initialize USART
    //printString("Capacitive Sensor\r\n");

    //Main Loop
    while(1)
    {
        chargeCycleCount = 0;                   //reset counter
        CAP_DDR |= (1 << CAP_PIN);              //set as output
        sei();                                  //start interrupt counting
        _delay_ms(SENSE_TIME);                  //Intterrupt repeats for the duration of the delay. 
                                                //PinChangeInterrupts get triggered on every change of the pin.
        cli();                                  //stop interrupt counting
        
        //Evaluation if capacitive sensor was pressed
        if(chargeCycleCount < THRESHOLD)
        {
            LED_PORT = 0x01;
        }
        else
        {
            LED_PORT = 0x00;
        }
        printWord(chargeCycleCount);            //print for calibration
        printString("\r\n");
    }
    //End Main loop

    return(0);
}

void initPinChargeInterrupt(void)
{
    PCICR |= (1 << PCIE1);                      //Pin Change Interrupt Control Register(PCICR): Enable Pin Change Interrupt 1 (PCIE1)
    PCMSK1 |= (1 << PCINT9);                    //Pin Change Mask Register 1 (PCMSK1): Enable pin PCINT9
}

ISR(PCINT1_vect)                                //Use PCINT1_vect because we use pin PC1
{
    chargeCycleCount++;                         //up count by 1
    CAP_DDR |= (1 << CAP_PIN);                  //set output mode to charge capacitor
    //_delay_ms(1);                             //charging delay. 

    CAP_DDR &= ~(1 << CAP_PIN);                 //set input mode to discharge capacitor
    PCIFR |= (1 << PCIF1);                      // Pin Change Interrupt Flag Register (PCIFR): reseting the flag PCIF1. This is needed because we charged the cap sensor to logic 1
}