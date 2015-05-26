#include "SegaGenesis.h"

SegaGenesis controller1({40,42,44,46,48,50,52});

SegaGenesis controller2({41,43,45,47,49,51,53});

void setup()
{
  Serial.begin(9600);
}

void printState(int state){
	if(state != 0){
	  Serial.print((state & SegaGenesis::ON)	? "+" : "-");
	  Serial.print((state & SegaGenesis::UP) 	? "U" : "0");
	  Serial.print((state & SegaGenesis::DOWN) 	? "D" : "0");
	  Serial.print((state & SegaGenesis::LEFT) 	? "L" : "0");
	  Serial.print((state & SegaGenesis::RIGHT)  	? "R" : "0");
	  Serial.print((state & SegaGenesis::START) 	? "S" : "0");
	  Serial.print((state & SegaGenesis::A) 	? "A" : "0");
	  Serial.print((state & SegaGenesis::B) 	? "B" : "0");
	  Serial.print((state & SegaGenesis::C)		? "C" : "0");
	}
}

void loop()
{
	printState(controller1.readChangedButtons());
	printState(controller2.readChangedButtons());
	
}
