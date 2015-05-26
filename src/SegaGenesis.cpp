
#include "SegaGenesis.h"
#include <Arduino.h>

SegaGenesis::SegaGenesis(PinConfig pins)
    :inputMap{
	  { pins.UpPin,     UP,    UP,     Z}, // P0 DB9 Pin 1
	  { pins.DownPin,   DOWN,  DOWN,   Y}, // P0 DB9 Pin 2
	  { pins.LeftPin,   ON,    LEFT,   X}, // P0 DB9 Pin 3
	  { pins.RightPin,  ON,    RIGHT,  0}, // P0 DB9 Pin 4
	  { pins.ABPin,     A,     B,      0}, // P0 DB9 Pin 6
	  { pins.StartCPin, START, C,      0}, // P0 DB9 Pin 9
	},
      selectPin(pins.SelectPin),
      lastState(-1),
      sixButtonMode(0),
      currentState(0)
 {

	// Setup input pins
	  for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++)
	  {
	    pinMode(inputMap[i].pin, INPUT);
	    digitalWrite(inputMap[i].pin, HIGH);
	  }


	  pinMode(selectPin, OUTPUT);
	  digitalWrite(selectPin, HIGH);


	  Serial.begin(9600);
}

SegaGenesis::~SegaGenesis() {
	// TODO Auto-generated destructor stub
}

int SegaGenesis::readButtons()
{
    resetState();
    if (sixButtonMode)
    {
      read6buttons();
    }
    else
    {
      read3buttons();
    }
    return currentState;
}

int  SegaGenesis::readChangedButtons()
{
  readButtons();

  if (currentState != lastState)
  {
    lastState = currentState;
    return currentState;
  }
  return 0;
}

void SegaGenesis::resetState()
{
  currentState = 0;
}

void SegaGenesis::read3buttons()
{
  // Set SELECT LOW and read lowFlag
  digitalWrite(selectPin, LOW);

  delayMicroseconds(20);

  for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++)
  {
    if (digitalRead(inputMap[i].pin) == LOW)
    {
      currentState |= inputMap[i].lowFlag;
    }
  }

  // Set SELECT HIGH and read highFlag
  digitalWrite(selectPin, HIGH);

  delayMicroseconds(20);

  for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++)
  {
    if (digitalRead(inputMap[i].pin) == LOW)
    {
      currentState |= inputMap[i].highFlag;
    }
  }

  // When a six-button first connects, it'll spam UP and DOWN,
  // which signals the game to switch to 6-button polling
  if (currentState == (ON | UP | DOWN))
  {
    sixButtonMode = true;
  }
  // When a controller disconnects, revert to three-button polling
  else if ((currentState & ON) == 0)
  {
    sixButtonMode = false;
  }

  delayMicroseconds(20);
}

void SegaGenesis::read6buttons()
{
  // Poll for three-button states twice
  read3buttons();
  read3buttons();

  // After two three-button polls, pulse the SELECT line
  // so the six-button reports the higher button states
  digitalWrite(selectPin, LOW);
  delayMicroseconds(20);
  digitalWrite(selectPin,HIGH);

  for(int i = 0; i < sizeof(inputMap) / sizeof(Input); i++)
  {
    if ( digitalRead(inputMap[i].pin) == LOW)
    {
      currentState |= inputMap[i].pulse3Flag;
    }
  }

  delayMicroseconds(1000);
}






