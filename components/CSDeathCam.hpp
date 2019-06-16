#pragma once

#include "../framework/Component.hpp"
class CSDeathCam : public Component
{
public:
    CSDeathCam() = default;
    CSDeathCam(CSDeathCam &&) = default;
    CSDeathCam(const CSDeathCam &) = default;
    CSDeathCam &operator=(CSDeathCam &&) = default;
    CSDeathCam &operator=(const CSDeathCam &) = default;
    ~CSDeathCam() = default;

    virtual void Update(){

    }
private:
    
};