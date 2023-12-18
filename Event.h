#pragma once
#include <iostream>
enum class EventType
{
    None = 0,
    WindowClose, WindowResize,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};
// Базовый класс события
class Event
{
public:
    virtual ~Event() = default;
    virtual EventType eventType() const = 0;
    virtual std::string toString() const = 0;
};

