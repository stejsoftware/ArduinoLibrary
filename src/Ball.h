#ifndef _BALL_H
#define _BALL_H

#include <Arduino.h>

class BallClass : public Printable
{
  public:
    BallClass();
    ~BallClass();

    size_t printTo(Print &) const;
    const char next() const;

    void setAutoDelete();
    void clearAutoDelete();

  private:
    bool m_auto_delete;
    uint8_t m_ball_len;
    mutable uint8_t m_frame;
};

extern BallClass Ball;

#endif // _BALL_H