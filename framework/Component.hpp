#pragma once

class Component
{
public:
    Component() = default;
    Component(Component &&) = default;
    Component(const Component &) = default;
    Component &operator=(Component &&) = default;
    Component &operator=(const Component &) = default;
    virtual ~Component() = default;
    virtual void Update() = 0;
private:
    
};