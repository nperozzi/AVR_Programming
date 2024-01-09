/* Maybe I can do scrolling text using the pattern from this website
https://embeddedthoughts.com/2016/04/19/scrolling-text-on-the-8x8-led-matrix-with-max7219-drivers/
*/

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define ROW_PORT PORTB
#define COL_PORT PORTD

// ------ Prototypes ------ //
void initMatrix();
void activateRow(uint8_t row);
void activateColumn(uint8_t col);
void show(uint8_t* pattern);
void scrollText(char* text);
void displaypattern(uint8_t pattern[8]);

// ------ Main ------ //
int main(void) 
{

  // -------- Inits --------- //
  initMatrix();
  uint8_t pattern[8] = {0};

  for(uint8_t j = 0; j < 8; j++)
  {
    if(j < 4)
    {
      pattern[j] = (1 << (3 - j)) | ((1 << j) << 4); 
    }
    else
    {
      pattern[j] = (1 << (3 - j - 4)) | ((1 << (j - 4)) << 4); 
    }

  }

  // ------ Event loop ------ //
  while (1)
  {
    void displaypattern(pattern);
  };
/*
    for(uint8_t i = 0; i < 8; i++)
    {
      COL_PORT &= ~(1 << i);
      _delay_ms(5);
      
    }

    for(uint8_t i = 7; i < 255; i--)
    {
      COL_PORT |= (1 << i);
      _delay_ms(5);
    }

    for(uint8_t i = 7; i < 255; i--)
    {
      COL_PORT &= ~(1 << i);
      _delay_ms(5);
    }
*/
  return 0;
}

// ------ Function Def. ------ //
void initMatrix()
{
  DDRB = 0xff; //Rows pins set as outputs
  DDRD = 0xff; //Columm pins set as outputs
}

void activateRow(uint8_t row) //Common cathod (-) matrix. The active column must be +5V
{
  ROW_PORT = ~(1 << row);
}

void activateColumn(uint8_t col) 
{
  COL_PORT = (1 << col); //0b00001000
}

void displaypattern(uint8_t pattern[8])
{
  for (int row = 0; row < 8; row++)
  {
    activateRow(row);
    COL_PORT = pattern[row];
    _delay_us(50);
  }

}