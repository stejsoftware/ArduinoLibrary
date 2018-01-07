#include "Timer.h"

Alarm::Alarm(TimerEventHandler handler, uint32_t interval, bool repeat) :
    m_handler(handler),
    m_repeat(repeat),
    m_interval(interval),
    m_timeout(0)
{
//  Serial.println("Alarm");
}

Alarm::~Alarm()
{
//  Serial.println("~Alarm");
}

void Alarm::reset()
{
  m_timeout = millis() + m_interval;
}

void Alarm::stop()
{
  m_timeout = 0;
  m_handler = NULL;
  m_repeat = false;
}

bool Alarm::isTime() const
{
  return millis() >= m_timeout;
}

bool Alarm::isRepeat() const
{
  return m_repeat;
}

void Alarm::execute() const
{
  if (m_handler != NULL)
  {
    m_handler();
  }
}

TimerClass::TimerClass()
{
}

TimerClass::~TimerClass()
{
  Alarm * alarm = NULL;

  while (m_alarms.pop(alarm))
  {
    delete alarm;
  }
}

Alarm * TimerClass::repeat(TimerEventHandler handler, uint32_t interval)
{
  Alarm * alarm = new Alarm(handler, interval, true);
  alarm->reset();
  m_alarms.push(alarm);
  return alarm;
}

Alarm * TimerClass::delay(TimerEventHandler handler, uint32_t timeout)
{
  Alarm * alarm = new Alarm(handler, timeout, false);
  alarm->reset();
  m_alarms.push(alarm);
  return alarm;
}

void TimerClass::run()
{
  Alarm * alarm = NULL;

  if (m_alarms.pop(alarm))
  {
    if (alarm->isTime())
    {
      alarm->execute();

      if (alarm->isRepeat())
      {
        alarm->reset();
        m_alarms.push(alarm);
      }
      else
      {
        delete alarm;
      }
    }
    else
    {
      m_alarms.push(alarm);
    }
  }
}

TimerClass Timer;
