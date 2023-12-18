#pragma once
#include "Event.h"
#include <iostream>
#include "KeyCode.h"
class KeyEvent : public Event
{
public:
    KeyCode GetKeyCode() const { return m_KeyCode; }
protected:
    KeyEvent(const KeyCode keycode)
        : m_KeyCode(keycode) {}
    KeyCode m_KeyCode;
};

