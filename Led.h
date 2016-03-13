#ifndef __LED_h_
#define __LED_h_

#include "Arduino.h"

#define LED_MAX_FRAMES 20
#define LED_FRAME_INTERVAL 60

class Led;

typedef void (*LedEventHandler)(Led & led);

class Led
{
public:
  Led(uint8_t pin = 13, uint8_t on_value = HIGH);
  ~Led();

  // returns the PIN of the LED
  uint8_t pin() const;

  // indicates if the LED is at least 50% on
  bool isOn() const;

  // indicates if the led is completely off.
  bool isOff() const;

  void setMax(uint8_t precent);
  // sets the value (%) of the LED.
  void brightness(uint8_t percent);
  // returns the current value (%) of the LED
  uint8_t brightness() const;

  // programs

  // turns the led on
  void on(LedEventHandler handler = NULL);
  // turns the led off
  void off(LedEventHandler handler = NULL);
  // turns the led on then off
  void flash(LedEventHandler handler = NULL);
  // Gradually turns the led on (PWM)
  void fadeOn(LedEventHandler handler = NULL, uint8_t delay = 0);
  // Gradually turns the led off (PWM)
  void fadeOff(LedEventHandler handler = NULL, uint8_t delay = 0);

  // displays the next frame of the current program.
  void display();

private:
  Led(const Led & rhs);
  Led & operator=(const Led & rhs);

  bool m_on_is_high;

  uint32_t m_millis;
  uint16_t m_value;
  uint8_t m_pin;

  uint8_t m_program[LED_MAX_FRAMES];
  uint8_t m_frame;
  uint8_t m_frame_count;
  LedEventHandler m_handler;

  uint8_t m_max;
};

bool operator==(const Led & lhs, const Led & rhs);

#endif // __LED_h_
