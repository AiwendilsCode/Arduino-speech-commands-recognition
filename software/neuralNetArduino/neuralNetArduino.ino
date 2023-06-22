#include <math.h>
#include <SPI.h>
#include <Arduino.h>

#include "hyperParams.h"
#include "linear.h"
#include "loadAudio.h"
#include "LEDeffects.h"
#include "timers.h"

/*
* 0 = hey nano
* 1 = random
* 2 = switching
* 3 = rain
* 4 = blinking
* 5 = loop
* 6 = turn off
* 7 = turn on
*/

int computed = 2;
Linear numberRecog = Linear(NUM_INPUT, NUM_HIDDEN, NUM_OUTPUT);
int currEffect = 6; // turn off

int prevComputed = 1;

float dummyInput[13][7] = {{20,34,50,66,57,36,26},
{26,28,43,52,52,30,17},
{20,24,34,50,38,19,9},
{31,24,39,57,58,40,37},
{19,27,43,47,45,31,24},
{10,25,40,39,31,19,9},
{4,12,17,24,28,17,11},
{0,7,11,10,7,4,3},
{0,1,2,4,3,2,2},
{0,1,1,1,2,2,2},
{0,1,1,1,2,2,2},
{0,1,1,1,2,2,2},
{0,1,2,1,2,2,2}
};

bool computeOutput()
{
  if (getInput(false))
  {
    computed = numberRecog.forward(CurBandData);
    return true;
  }
  return false;
}

void setup()
{
  Serial.begin(57600);
  Serial.println("reset");
  pinMode(AUDIO_IN, INPUT);
  analogReference(EXTERNAL);
  randomSeed(analogRead(AUDIO_IN)); // init audio capture and set random seed
  getInput(true);
  
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < NUM_LEDS; j++)
    {
      pinMode(leds[i][j], OUTPUT);
    }
  }

  numberRecog.forward(dummyInput);
  cli();
  interruptFunc = runEffect[EFFECT(currEffect)];
  sei();

  TIM1_enableOverflowInterrupt();
}

void loop()
{
  if (computeOutput())
  {
    if (computed == 0)
    {
      currEffect = computed;
      interruptFunc = runEffect[EFFECT(currEffect)];
    }
    else if (prevComputed == 0 && computed != 0)
    {
      Serial.println("effect detected");
      
      currEffect = computed;
      cli();
      interruptFunc = runEffect[EFFECT(currEffect)];
      sei();
    }
    Serial.println(computed);

    prevComputed = computed;
  }
  //runEffect[EFFECT(currEffect)]();
}
