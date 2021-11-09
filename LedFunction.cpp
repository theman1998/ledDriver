#include "LedFunction.h"

// default constructor
LED::LED(): IR{2}
{
  pinRed = 5;
  pinGreen = 4;
  pinBlue = 6;
  irPin = 2;
}

// user specific constructor. irPin can be ignore
LED::LED( int red, int green, int blue, int irPin ) : IR{irPin}
{
  pinRed = red;
  pinGreen = green;
  pinBlue = blue;
  this->irPin = irPin;
}


// will use the code created from the IR sensor and will shoot out
// a enum value representing the requested mode
// @return IrMode enum value represented from IR input
LED::IrMode LED::getMode()
{
  IrMode res = NONE;
  if(IR.decode(&resultsIR)){
    Serial.println(resultsIR.value);
    IR.resume(); // resume receiver

    // this next part will iterate through the modes and return based on position. 
    // codes will go left to right then top to bottom starting at red, using the basic LED
    // remote given from amazon
    switch( resultsIR.value )
    {
      //Off button code value = 16712445
      //Row 1
      case 16718565: return (IrMode)(res + 1);
      case 16751205: return (IrMode)(res + 2);
      case 16753245: return (IrMode)(res + 3);
      case 16720605: return (IrMode)(res + 4);
      // row 2
      case 16722645: return (IrMode)(res + 5);
      case 16755285: return (IrMode)(res + 6);
      case 16749165: return (IrMode)(res + 7);
      case 16716525: return (IrMode)(res + 8);
      // row 3
      case 16714485: return (IrMode)(res + 9);
      case 16747125: return (IrMode)(res + 10);
      case 16757325: return (IrMode)(res + 10);
      case 16724685: return (IrMode)(res + 10);
      // row 4
      case 16726215: return (IrMode)(res + 10);
      case 16758855: return (IrMode)(res + 11);
      case 16742535: return (IrMode)(res + 12);
      case 16775175: return (IrMode)(res + 13);
      
    }
  }
  return res;
}

// sets the output of each pin values 0 - 255
// @param[in] red analog value set to pin red
// @param[in] green analog value set to pin green
// @param[in] blue analog value set to pin blue
void LED::setLight( uint8_t red, uint8_t green, uint8_t blue )
{
  analogWrite( pinRed, red );
  analogWrite( pinGreen, green );
  analogWrite( pinBlue, blue );
}



// initialize Pins for LED lights
void LED::initLights()
{
  Serial.print("Initializing LED PIN(R,G,B): ");
  Serial.print( pinRed );
  Serial.print( ", " );
  Serial.print( pinGreen );
  Serial.print( ", " );
  Serial.println( pinBlue );
  pinMode( pinRed, OUTPUT );
  pinMode( pinGreen, OUTPUT );
  pinMode( pinBlue, OUTPUT );
  pinMode( pinRed, LOW );
  pinMode( pinGreen, LOW );
  pinMode( pinBlue, LOW );
}

// initialize Pins for IR Sensor
void LED::initIR()
{
 Serial.print("Initializing IR Pin: ");
 Serial.println( irPin );
 IR.enableIRIn();
 randomSeed( analogRead( 0 )); 
}

// check state of IR pin
// @return "true" if there input in the pin
bool LED::irActive()
{
    if( IR.decode( &resultsIR ))
    {
        return true;
    }
    else
        return false;
}
