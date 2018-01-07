#include <Led.h>

// create an LED object that uses PIN 6 and uses 5+ for on
Led led(6, HIGH);

void done(Led &led)
{
  if (led.brightness() == 0)
  {
    led.fadeOn(done);
  }
  else if (led.brightness() == 100)
  {
    led.fadeOff(done);
  }
}

// The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  Serial.println("Started");

  led.brightness(100);
  delay(1000);
  led.brightness(0);
  delay(1000);

  led.fadeOn(done);
}

// The loop function is called in an endless loop
void loop()
{
  led.display();
}
