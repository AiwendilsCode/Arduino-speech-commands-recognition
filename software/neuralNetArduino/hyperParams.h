#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

#define NUM_SEGMENTS 13
#define NUM_BANDS	 7

#define pinA 2
#define pinB 3
#define pinC 4
#define pinD 5
#define pinE 6
#define pinF 7
#define pinG 8

#ifndef getBit
#define getBit(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#endif

#define NUM_OUTPUT 8
#define NUM_HIDDEN 30
#define NUM_INPUT  (NUM_SEGMENTS * NUM_BANDS)

#define NUM_LEDS 10

#define EFFECT(x) (x)

const int AUDIO_IN = A5;

const char SegmentSize = 50; //in mS
const char hyster = 2;
const char thresh = 100;

float CurBandData[NUM_SEGMENTS][NUM_BANDS];

#endif // !HYPERPARAMS_H
