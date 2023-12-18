#pragma once
#include "Event.h"
#include <iostream>
#include <string>
class WindowCloseEvent : public Event
{
    EventType eventType() const override
    {
    }
    std::string toString() const override
    {
    }
};

