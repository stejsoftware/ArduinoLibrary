#include <Timer.h>

#define SECOND 1000
#define MINUTE 60 * SECOND
#define HOUR 60 * SECOND

void second()
{
    Serial.println("Tick");
}

void minute()
{
    Serial.println("It has been a minute.");
}

void wake()
{
    Serial.println("Time to wake!")
}

void setup()
{
    Serial.begin(9600);

    Timer.alarm(wake, HOUR);
    Timer.repeat(second, SECOND);
    Timer.repeat(minute, MINUTE);
}

void loop()
{
    Timer.run();
}