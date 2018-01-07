#ifndef __Button_h_
#define __Button_h_

#include <Arduino.h>

// the amount of time required to identify a latch
#define BUTTON_DEBOUNCE_DELAY 50

// the max amount of time allowed to identify a click / double click
#define BUTTON_CLICK_TIMEOUT 200
#define BUTTON_DOUBLE_CLICK_TIMEOUT 500
#define BUTTON_HELD_TIMEOUT 1000

class Button;

typedef void (*ButtonEventHandler)(Button &button);

enum ButtonEvent
{
  bePressed,
  beReleased,
  beClick,
  beDblClick,
  beHeld,
  ButtonEvent_Count
};

class Button
{
public:
  // CTOR: creates a button object
  //    pin: the pin that the button is attached to
  //    pressed_value: either HIGH or LOW; the value indicating the  (defaults to HIGH)
  //                   button was pressed
  Button(uint8_t pin, uint8_t pressed_value = HIGH, bool use_pullup = false);
  ~Button();

  // setup an event handler
  void attach(ButtonEvent event, ButtonEventHandler handler);

  // returns the number of clicks that have occurred
  uint8_t clicks() const;

  // returns the current state of the button accounting for debounce
  bool read();

  // reads the button and executes events as they occur
  void run();

private:
  // executes an event
  void fire(ButtonEvent event);

  Button(const Button &rhs);
  Button &operator=(const Button &rhs);

  uint8_t m_pin;
  bool m_pressed_is_high;

  uint32_t m_debounce_t;
  uint32_t m_click_t;
  uint32_t m_dbl_click_t;
  uint8_t m_click_count;
  bool m_last_read;
  bool m_current_state;
  bool m_held;

  ButtonEventHandler m_handler[ButtonEvent_Count];
};

#endif // __Button_h_
