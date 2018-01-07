#include <Relay.h>

Relay relay(13);

// The setup function is called once at startup of the sketch
void setup()
{
    Serial.begin(9600);

    Serial.print("Relay state: ");
    Serial.println(relay.state());

    // engage the relay
    relay.on();

    Serial.print("Relay state: ");
    Serial.println(relay.state());

    delay(1000);

    // disengage the relay
    relay.off();

    Serial.print("Relay state: ");
    Serial.println(relay.state());

    delay(1000);

    // temporarily engage the relay as if clicking a button
    relay.flash();
}

// The loop function is called in an endless loop
void loop()
{
    // required for flash program to run
    relay.run();
}