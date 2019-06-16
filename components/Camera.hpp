#pragma once

#include "../framework/Component.hpp"
class Camera : public Component
{
public:
    Camera() = default;
    Camera(Camera &&) = default;
    Camera(const Camera &) = default;
    Camera &operator=(Camera &&) = default;
    Camera &operator=(const Camera &) = default;
    ~Camera() = default;


    virtual void Update(){

    }
private:
    
};