#pragma once
#include "KeyEvent.h"
#include <iostream>
#include "KeyCode.h"
class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(const KeyCode keycode)
        : KeyEvent(keycode) {}
private:
};

