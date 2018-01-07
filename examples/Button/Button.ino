#include <Button.h>

Button button(4, HIGH);

void pressed(Button &button)
{
  Serial.println("pressed");
}

void held(Button &button)
{
  Serial.println("held");
}

void click(Button &button)
{
  Serial.print("click: ");
  Serial.println(button.clicks());
}

void double_click(Button &button)
{
  Serial.println("double click");
}

// The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  Serial.println("Started");

  button.attach(bePressed, pressed);
  button.attach(beHeld, held);
  button.attach(beClick, click);
  button.attach(beDblClick, double_click);
}

// The loop function is called in an endless loop
void loop()
{
  button.read();
}
