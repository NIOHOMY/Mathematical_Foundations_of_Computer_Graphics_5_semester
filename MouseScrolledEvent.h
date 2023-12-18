#pragma once
#include "Event.h"
#include <iostream>
class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(const double& xOffset, const double& yOffset)
        : m_xOffset(xOffset), m_yOffset(yOffset) {}
private:
    double m_xOffset;
    double m_yOffset;
};

