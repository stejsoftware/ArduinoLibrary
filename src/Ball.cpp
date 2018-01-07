#include "Ball.h"

#define BALL "/-\\|"

BallClass::BallClass() : m_frame(0),
                         m_auto_delete(false),
                         m_ball_len(strlen(BALL))
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
    p.write(next());

    if (m_auto_delete)
        p.write(char(8));
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
