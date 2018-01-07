#include "Ball.h"

#define BALL "/-\\|"

BallClass::BallClass() : m_auto_delete(false),
                         m_ball_len(strlen(BALL)),
                         m_frame(0)
{
}

BallClass::~BallClass()
{
}

const char BallClass::next() const
{
    m_frame = ((m_frame + 1) % m_ball_len);
    return BALL[m_frame];
}

size_t BallClass::printTo(Print &p) const
{
    size_t s = p.write(next());

    if (m_auto_delete)
        s += p.write(char(8));

    return s;
}

void BallClass::setAutoDelete()
{
    m_auto_delete = true;
}

void BallClass::clearAutoDelete()
{
    m_auto_delete = false;
}

BallClass Ball;
