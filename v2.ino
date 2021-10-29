#include "LedFunction.h"

// literals that corraspond to GPIO Pins
#define LED_RED 5
#define LED_GREEN 4
#define LED_BLUE 6

/// our mode and LED object
LED::IrMode modeRefference = LED::ModeSmooth;
LED led( LED_RED, LED_GREEN, LED_BLUE );

// variables holding Value of output RGB pins {0-255}
uint8_t pinValRed = 0;
uint8_t pinValGreen = 0;
uint8_t pinValBlue = 0;

// direction of velocity & accel
int8_t redSpeed = 0;
int8_t redAccel = 0;
int8_t redDirUp = true; // keep track of direction of movement
int8_t greenSpeed = 0;
int8_t greenAccel = 0;
int8_t greenDirUp = true; // keep track of direction of movement
int8_t blueSpeed = 0;
int8_t blueAccel = 0;
int8_t blueDirUp = true; // keep track of direction of movement

// flag to represent a new mode
bool modeSwap = true;

// prototypes that will hold the type of mode algorithms
void modeSmooth();
// use this in the beginning of each method, as this will make sure the lights can transition properly
bool isNewMode( uint8_t red, uint8_t green, uint8_t blue );
void refreshSpeeds();

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing Program");  
  // must do these before anything
  led.initLights();
  led.initIR();
  Serial.println("Entering main loop");
}

void loop() 
{
  // if IR input presents itself, then lets get the code and update our global mode
  if ( led.irActive() )
  {
    // get desire mode
    LED::IrMode mode = led.getMode();
    // update our reference if the mode is true
    if ( mode != LED::NONE )
    {
      modeRefference = mode;
      modeSwap = true;
    }
  }

  switch( modeRefference )
  {
    
    case LED::ModeBusting :
      modeSmooth(); // replace with new mode
      break;
    case LED::ModeFlash :
      modeSmooth(); // replace
      break;
    case LED::ModeSmooth :
      modeSmooth(); 
      break;
    default :
      modeSmooth();
      break;
    
  }
    
  delay(50); // wait some period ms
}

bool isNewMode( uint8_t red, uint8_t green, uint8_t blue )
{
  if ( modeSwap )
  {
    modeSwap = false;
    pinValRed = red;
    pinValGreen = green;
    pinValBlue = blue;
    return true;
  }
  return false;
}
void refreshSpeeds()
{
redSpeed = 0;
redAccel = 0;
redDirUp = true; // keep track of direction of movement
greenSpeed = 0;
greenAccel = 0;
greenDirUp = true; // keep track of direction of movement
blueSpeed = 0;
blueAccel = 0;
blueDirUp = true; // keep track of direction of movement   
}

void modeSmooth()
{
  if ( isNewMode( 1, 1, 1) )
  { 
    redSpeed = 7;  
    greenSpeed = 1;
    blueSpeed = 9;
  }

  if( ((( int ) pinValRed + redSpeed ) > 255 ) || ((( int ) pinValRed + redSpeed ) < 0 ))
  {
      redDirUp = !redDirUp;
      redSpeed = redSpeed * -1;
  }
  if( ((( int ) pinValGreen + greenSpeed ) > 255 ) || ((( int ) pinValGreen + greenSpeed ) < 0 ))
  {
      greenDirUp = !greenDirUp;
      greenSpeed = greenSpeed * -1;
  }
  if( ((( int ) pinValBlue + blueSpeed ) > 255 ) || ((( int ) pinValBlue + blueSpeed ) < 0 ))
  {
      blueDirUp = !blueDirUp;
      blueSpeed = blueSpeed * -1;
  }
  pinValRed += redSpeed;
  pinValGreen += greenSpeed;
  pinValBlue += blueSpeed;

  led.setLight( pinValRed, pinValGreen, pinValBlue );
  //Serial.println( pinValRed );
  
}



