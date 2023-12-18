#pragma once
#include "MouseButtonEvent.h"
#include <iostream>
#include <string>
class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(const MouseCode button)
        : MouseButtonEvent(button) {}
    std::string toString() const override {
        return "MouseButtonReleasedEvent: " + std::to_string(static_cast<int>(m_button));
    }
    EventType eventType() const {
        return EventType::MouseButtonReleased;
    }
};

