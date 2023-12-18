#pragma once
#include "Event.h"
#include <iostream>
#include <string>
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width(width), m_height(height) {}
    int width() const {
        return m_width;
    }
    int height() const {
        return m_height;
    }
    EventType eventType() const override
    {
        return EventType::WindowResize;
    }
    std::string toString() const override
    {
        return "WindowResizeEvent: " + std::to_string(m_width) + ", " +
            std::to_string(m_height);
    }
private:
    unsigned int m_width;
    unsigned int m_height;
};

