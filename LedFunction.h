#define _LEDFUNCTION_H_
#ifdef _LEDFUNCTION_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <IRremoteInt.h>

class LED 
{
public:
  // ---------------------- constructors ------------------------------------
  LED();
  LED( int red, int green, int blue, int irPin = 2 );

  //----------------------- enum -----------------------------------------------
  // defining the type of signal recieve from IR sensor. should correspond to some type of pattern
  enum IrMode
  {
    NONE = 0,
    ModeBusting,
    ModeFlash,
    ModeSmooth = 5
  }; 

  // ------------------------------- initialization ---------------------------------
  // methods that initialize pins in GPIO
  void initLights();
  void initIR();

  //-------------------- bread and butter methods--------------------------------
  // links the IR code to a certain name
  IrMode getMode(); 
  // sets the output of each pin values 0 - 255
  void setLight( uint8_t red, uint8_t green, uint8_t blue );
  // utility methods
  bool irActive();

private:

  //variables / structs
  uint8_t irPin;
  uint8_t pinRed;
  uint8_t pinGreen;
  uint8_t pinBlue;
  decode_results resultsIR;
  IRrecv IR;
  


};

//extern something();
#endif // _LEDFUNCTION_H_
