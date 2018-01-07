#include "Button.h"

Button::Button(uint8_t pin, uint8_t pressed_value, bool use_pullup) :
    m_pin(pin),
    m_pressed_is_high(pressed_value == HIGH),

    m_debounce_t(0),
    m_click_t(0),
    m_dbl_click_t(0),
    m_click_count(0),
    m_last_read(false),
    m_current_state(false),
    m_held(false)
{
  memset(m_handler, 0, ButtonEvent_Count);

  pinMode(m_pin, use_pullup ? INPUT_PULLUP : INPUT);
}

Button::~Button()
{
  pinMode(m_pin, OUTPUT);
  digitalWrite(m_pin, LOW);
}

void Button::attach(ButtonEvent event, ButtonEventHandler handler)
{
  m_handler[event] = handler;
}

void Button::fire(ButtonEvent event)
{
  if (m_handler[event] != NULL)
  {
    m_handler[event](*this);
  }
}

uint8_t Button::clicks() const
{
  return m_click_count;
}

void Button::run()
{
  // read the button
  bool state = read();

  // if latch up
  if (state && !m_current_state)
  {
    m_current_state = state;
    m_click_t = millis();

    // trigger the pressed event
    fire(bePressed);
  }
  else
  // if latch down
  if (!state && m_current_state)
  {
    m_current_state = state;
    m_held = false;

    // check to see if the button was pressed long enough
    // to identify a click
    if (millis() - m_click_t <= BUTTON_CLICK_TIMEOUT)
    {
      m_click_count++;
      // trigger the click event
      fire(beClick);

      if (m_click_count == 1)
      {
        m_dbl_click_t = millis();
      }
      else if (m_click_count == 2)
      {
        m_click_count = 0;

        if ((millis() - m_dbl_click_t) <= BUTTON_DOUBLE_CLICK_TIMEOUT)
        {
          // trigger the double click event
          fire(beDblClick);
        }
      }
    }
    else
    {
      m_click_count = 0;
    }

    // trigger the released event
    fire(beReleased);
  }

  if (m_current_state)
  {
    if (!m_held && ((millis() - m_click_t) > BUTTON_HELD_TIMEOUT))
    {
      m_held = true;
      // trigger the held event
      fire(beHeld);
    }
  }
  else
  {
    if ((millis() - m_dbl_click_t) > BUTTON_DOUBLE_CLICK_TIMEOUT)
    {
      m_click_count = 0;
    }
  }
}

bool Button::read()
{
  // store the current state
  bool state = m_current_state;

  // read the button
  bool current_read =
      m_pressed_is_high ?
          (digitalRead(m_pin) == HIGH) : (digitalRead(m_pin) == LOW);

  // if the button state changed
  if (current_read != m_last_read)
  {
    // reset the timer
    m_debounce_t = millis();

    // save the current read as the last read
    m_last_read = current_read;
  }

  // if the timer has been running long enough
  // set the actual state to the current state
  if ((millis() - m_debounce_t) >= BUTTON_DEBOUNCE_DELAY)
  {
    // save the new state
    state = m_last_read;
  } // endif delay enough

  return state;
}
