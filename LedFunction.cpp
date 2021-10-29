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
    //if(IR.decode(&resultsIR)){
    //  Serial.println(resultsIR.value);
  
  IrMode res = NONE;
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
