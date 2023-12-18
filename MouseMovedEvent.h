#pragma once
#include "Event.h"
#include <iostream>
class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(const double& x, const double& y)
        : m_mouseX(x), m_mouseY(y)
    {}
private:
    double m_mouseX;
    double m_mouseY;
};

