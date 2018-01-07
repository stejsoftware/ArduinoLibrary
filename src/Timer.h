#ifndef __Timer_h_
#define __Timer_h_

#include <Arduino.h>
#include "List.h"

typedef void (*TimerEventHandler)();

class Alarm
{
public:
  Alarm(TimerEventHandler handler, uint32_t interval, bool repeat);
  ~Alarm();

  void reset();
  void stop();

  bool isTime() const;
  bool isRepeat() const;
  void execute() const;

private:
  Alarm(const Alarm &rhs);
  Alarm &operator=(const Alarm &rhs);

  TimerEventHandler m_handler;
  bool m_repeat;
  uint32_t m_interval;
  uint32_t m_timeout;
};

class TimerClass
{
public:
  TimerClass();
  ~TimerClass();

  Alarm *repeat(TimerEventHandler handler, uint32_t interval);
  Alarm *delay(TimerEventHandler handler, uint32_t timeout);

  void run();

private:
  TimerClass(const TimerClass &rhs);
  TimerClass &operator=(const TimerClass &rhs);

  List<Alarm *> m_alarms;
};

extern TimerClass Timer;

#endif // __Timer_h_
