
#ifndef SEGA_H_
#define SEGA_H_

#include <Arduino.h>

class SegaGenesis {
public:

	typedef struct PinConfig{
	  int SelectPin;
	  int StartCPin;
	  int ABPin;
	  int RightPin;
	  int LeftPin;
	  int DownPin;
	  int UpPin;

	};

	// Controller Button Flags
	static const int ON = 1;
	static const int UP = 2;
	static const int DOWN = 4;
	static const int LEFT = 8;
	static const int RIGHT = 16;
	static const int START = 32;
	static const int A = 64;
	static const int B = 128;
	static const int C = 256;
	static const int X = 512;
	static const int Y = 1024;
	static const int Z = 2048;

	SegaGenesis(PinConfig pins);
	virtual ~SegaGenesis();
	int readButtons();
	int readChangedButtons();

private:

	typedef struct
	{
	  int pin;
	  int lowFlag;
	  int highFlag;
	  int pulse3Flag;
	} Input;

	// Controller DB9 Pin 7 Mappings
	int selectPin;
	// Controller DB9 Pin to Button Flag Mappings
	// First column is the controller index, second column
	// is the Arduino pin that the controller's DB9 pin is
	// attached to
	Input inputMap[6];

	// Controller State
	int currentState;
	int lastState;
	// Default to three-button mode until six-button connects
	boolean sixButtonMode;

	void read3buttons();
	void read6buttons();
	void resetState();
	void sendStates();

};

#endif /* SEGA_H_ */
