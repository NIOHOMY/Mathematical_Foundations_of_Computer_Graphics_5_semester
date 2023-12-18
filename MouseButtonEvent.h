#pragma once
#include "Event.h"
#include <iostream>
#include "MouseCode.h"
class MouseButtonEvent : public Event
{
public:
    MouseButtonEvent(const MouseCode button) :
        m_button(button)/*, m_mods(mods)*/ {}
    MouseCode GetMouseButton() const {
        return m_button;
    }
protected:
    MouseCode m_button;
};

