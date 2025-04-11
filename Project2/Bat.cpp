#include "Bat.h"
using namespace sf;
Bat::Bat(float startX, float startY)
{
    m_Position.x = startX;
    m_Position.y = startY;

    m_Shape.setSize(Vector2f(100.0, 10.0));
    m_Shape.setPosition(m_Position);
}

FloatRect Bat::getPosition()
{
    return m_Shape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
    return m_Shape;
}

void Bat::moveLeft()
{
    m_MovingLeft = true;
}

void Bat::moveRight()
{
    m_MovingRight = true;
}

void Bat::stopLeft()
{
    m_MovingLeft = false;
}

void Bat::stopRight()
{
    m_MovingRight = false;
}

void Bat::update(Time dt)
{
    if (m_MovingLeft)
    {
        m_Position.x -= m_Speed * dt.asSeconds();
        // extra code to confirm bat shoud not to outs
        if (m_Position.x < 0)
        {
            stopLeft();
        }
            
    }

    if (m_MovingRight)
    {
        m_Position.x += m_Speed * dt.asSeconds();
        // extra code to confirm bat should not to outs
        if (m_Position.x > 1400)
        {
            stopRight();
        }
    }

    m_Shape.setPosition(m_Position);
}
