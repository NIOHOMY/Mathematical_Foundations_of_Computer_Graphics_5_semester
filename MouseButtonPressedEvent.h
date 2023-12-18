#pragma once
#include "MouseButtonEvent.h"
#include <iostream>
#include <string>
class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(const MouseCode button)
        : MouseButtonEvent(button) {}
    std::string toString() const override {
        return "MouseButtonPressedEvent: " + std::to_string(static_cast<int>(m_button));
    }
    EventType eventType() const {
        return EventType::MouseButtonPressed;
    }
};

