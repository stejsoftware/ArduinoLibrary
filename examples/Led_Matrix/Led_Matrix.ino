#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include "Led_Matrix.h"

Led_Matrix matrix(
  16,  // width in pixels 
  8,   // height in pixels
  2,   // number of devices wide  (rows)
  1    // number of devices high (cols)
);

// The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  Serial.println("started");

  matrix.begin();  
  matrix.test(); 
  matrix.setText("Hello World!");
}

// The loop function is called in an endless loop
void loop()
{  
  matrix.run(mpScrollLeft, 150);
}
