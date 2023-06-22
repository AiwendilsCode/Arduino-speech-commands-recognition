#include "hyperParams.h"

byte leds[2][5] = {{6, 5, 4, 3, 2},
  {A4, A3, A2, A1, A0}
};

void rotating();
void raining();
void turnOn();
void randomBlinking();
void turnOff();
void switching();
void blinking();
void waitForEffect();

void (*runEffect[])() = {waitForEffect, randomBlinking, switching, raining, blinking, rotating, turnOff, turnOn};

void raining()
{
  turnOff();
  static int8_t pos1 = 0;
  static int8_t pos2 = -3;
  
  digitalWrite(leds[0][abs(pos1 - 5) % 5], LOW);
  digitalWrite(leds[0][abs(((pos1 + 1) % NUM_LEDS) - 5) % 5], LOW);
  digitalWrite(leds[1][abs(pos2 + 5) % 5], LOW);
  digitalWrite(leds[1][abs(((pos2 - 1) % NUM_LEDS) + 5) % 5], LOW);
  pos1 = ++pos1 % 5;
  pos2 = ++pos2 % 5;
  digitalWrite(leds[0][abs(pos1 - 5) % 5], HIGH);
  digitalWrite(leds[0][abs(((pos1 + 1) % NUM_LEDS) - 5) % 5], HIGH);
  digitalWrite(leds[1][abs(pos2 + 5) % 5], HIGH);
  digitalWrite(leds[1][abs(((pos2 - 1) % NUM_LEDS) + 5) % 5], HIGH);
}

void rotating()
{
  turnOff();
  static byte pos = 0;
  static byte indexes[10] = {0x00, 0x01, 0x02, 0x03, 0x04,
                             0x10, 0x11, 0x12, 0x13, 0x14
                            };
  digitalWrite(leds[(0xf0 & indexes[pos]) >> 4][0x0f & indexes[pos]], LOW);
  digitalWrite(leds[(0xf0 & indexes[(pos + 1) % NUM_LEDS]) >> 4][0x0f & indexes[(pos + 1) % NUM_LEDS]], LOW);
  pos = ++pos % NUM_LEDS;
  digitalWrite(leds[(0xf0 & indexes[pos]) >> 4][0x0f & indexes[pos]], HIGH);
  digitalWrite(leds[(0xf0 & indexes[(pos + 1) % NUM_LEDS]) >> 4][0x0f & indexes[(pos + 1) % NUM_LEDS]], HIGH);
}

void turnOn()
{
  PORTC |= 0b0011111; // zapni led
  PORTD |= 0b011111100; // zapni led
}

void randomBlinking()
{
  turnOff();
  static int wait = 0;
  static int prevLed = 0;

  digitalWrite(leds[prevLed / 5][prevLed % (NUM_LEDS / 2)], LOW);
  prevLed = random(NUM_LEDS);
  digitalWrite(leds[prevLed / 5][prevLed % (NUM_LEDS / 2)], HIGH);
}

void waitForEffect()
{
  PORTD &= 0b10000011; // vypni led
  PORTC &= 0b1100000; // vypni led

  PORTD |= 0b11000111; // wait state
  PORTC |= 0b1110001; // wait state
}

void turnOff()
{
  PORTD &= 0b10000011; // vypni led
  PORTC &= 0b1100000; // vypni led
}

void switching()
{
  turnOff();
  static byte state = 0;

  if (state)
  {
    PORTD &= 0b10000011; // vypni led
    PORTC |= 0b0011111; // zapni led

    state = 0;
  }
  else if (!state)
  {
    PORTC &= 0b1100000; // vypni led
    PORTD |= 0b011111100; // zapni led

    state = 1;
  }
}

void blinking()
{
  turnOff();
  static byte state = 0;

  if (state)
  {
    PORTD &= 0b10000011; // vypni led
    PORTC &= 0b1100000; // vypni led

    state = 0;
  }
  else if (!state)
  {
    PORTD |= 0b011111100; // zapni led
    PORTC |= 0b0011111; // zapni led

    state = 1;
  }
}
