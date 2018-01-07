#include <Led.h>
#include <Button.h>

Led led(6, HIGH);       // led attached to pin 6 and requires a high (+5v) to light
Button button(4, HIGH); // button attached to pin 4 and will pull it high (+5v) when closed

// called whenever a "pressed" event occurs.
void pressed(Button &button)
{
  Serial.println("pressed");
}

// called whenever a "click" event occurs.
void click(Button &button)
{
  // if the button is on
  if (led.isOn())
  {
    // turn it off
    led.off();
  }
  else
  {
    // turn it on
    led.on();
  }

  Serial.println("click");
}

// The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  Serial.println("start");

  // setup event handlers
  button.attach(bePressed, pressed);
  button.attach(beClick, click);

  led.flash();
}

// The loop function is called in an endless loop
void loop()
{
  led.display();
  button.read();
}
