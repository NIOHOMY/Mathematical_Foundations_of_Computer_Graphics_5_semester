#pragma once
#include "KeyEvent.h"
#include <iostream>
#include <string>
class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(const KeyCode keycode)
        : KeyEvent(keycode) {}
    EventType eventType() const override {
        return EventType::KeyReleased;
    }
    std::string toString() const override
    {
        return "KeyReleasedEvent: " + std::to_string(static_cast<int>(m_KeyCode));
    }
};

