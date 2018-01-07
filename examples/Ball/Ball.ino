#include <Ball.h>
#include <Timer.h>

void wait()
{
    Serial.print(Ball);
}

// The setup function is called once at startup of the sketch
void setup()
{
    Serial.begin(9600);

    Timer.repeat(wait, 500);
}

// The loop function is called in an endless loop
void loop()
{
    Timer.run();
}