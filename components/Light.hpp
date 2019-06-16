#pragma once
#include "../framework/Component.hpp"
class Light : public Component
{
public:
    Light() = default;
    Light(Light &&) = default;
    Light(const Light &) = default;
    Light &operator=(Light &&) = default;
    Light &operator=(const Light &) = default;
    ~Light() = default;
    virtual void Update(){
        
    }
private:
    
};