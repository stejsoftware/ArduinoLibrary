#include "Led.h"

Led::Led(uint8_t pin, uint8_t on_value) :
    m_on_is_high(on_value == HIGH),

    m_millis(millis()),
    m_value(0),
    m_pin(pin),

    m_frame(0),
    m_frame_count(0),
    m_handler(NULL),

    m_max(100)
{
  memset(m_program, 0, LED_MAX_FRAMES);

  pinMode(m_pin, OUTPUT);
  brightness(0);
}

Led::~Led()
{
  pinMode(m_pin, OUTPUT);
  digitalWrite(m_pin, LOW);
}

uint8_t Led::pin() const
{
  return m_pin;
}

bool Led::isOn() const
{
  return brightness() > 50;
}

void Led::setMax(uint8_t precent)
{
  m_max = precent;
}

void Led::brightness(uint8_t percent)
{
  if( percent > m_max )
  {
    percent = m_max;
  }

  if (m_on_is_high)
  {
    m_value = percent * (255.0 / 100.0);
  }
  else
  {
    m_value = (100 - percent) * (255.0 / 100.0);
  }

  analogWrite(m_pin, m_value);
}

uint8_t Led::brightness() const
{
  uint8_t percent;

  if (m_on_is_high)
  {
    percent = m_value * (100.0 / 255.0);
  }
  else
  {
    percent = 100 - (m_value * (100.0 / 255.0));
  }

  return percent;
}

void Led::on(LedEventHandler handler)
{
  m_frame_count = 0;
  m_program[m_frame_count++] = 100;
  m_frame = 0;
  m_handler = handler;
}

void Led::off(LedEventHandler handler)
{
  m_frame_count = 0;
  m_program[m_frame_count++] = 0;
  m_frame = 0;
  m_handler = handler;
}

void Led::flash(LedEventHandler handler)
{
  m_frame_count = 0;
  m_program[m_frame_count++] = 0;
  m_program[m_frame_count++] = 25;
  m_program[m_frame_count++] = 50;
  m_program[m_frame_count++] = 75;
  m_program[m_frame_count++] = 100;
  m_program[m_frame_count++] = 100;
  m_program[m_frame_count++] = 75;
  m_program[m_frame_count++] = 50;
  m_program[m_frame_count++] = 25;
  m_program[m_frame_count++] = 0;
  m_frame = 0;
  m_handler = handler;
}

void Led::fadeOn(LedEventHandler handler, uint8_t delay)
{
  m_frame_count = 0;
  
  for( uint8_t x = 0; x < delay; x++ )
  {
    m_program[m_frame_count++] = 0;
  }
  
  m_program[m_frame_count++] = 0;
  m_program[m_frame_count++] = 25;
  m_program[m_frame_count++] = 50;
  m_program[m_frame_count++] = 75;
  m_program[m_frame_count++] = 100;
  m_program[m_frame_count++] = 100;
  m_frame = 0;
  m_handler = handler;
}

void Led::fadeOff(LedEventHandler handler, uint8_t delay)
{
  m_frame_count = 0;

  for( uint8_t x = 0; x < delay; x++ )
  {
    m_program[m_frame_count++] = 100;
  }

  m_program[m_frame_count++] = 100;
  m_program[m_frame_count++] = 75;
  m_program[m_frame_count++] = 50;
  m_program[m_frame_count++] = 25;
  m_program[m_frame_count++] = 0;
  m_program[m_frame_count++] = 0;
  m_frame = 0;
  m_handler = handler;
}

void Led::display()
{
  if ((millis() - m_millis) > LED_FRAME_INTERVAL)
  {
    m_millis = millis();

    if (m_frame < m_frame_count)
    {
      brightness(m_program[m_frame++]);
    }
    else if (m_handler != NULL)
    {
      LedEventHandler handler = m_handler;
      m_handler = NULL;
      
      handler(*this);
    }
  }
}

bool operator==(const Led & lhs, const Led & rhs)
{
  return lhs.pin() == rhs.pin();
}
