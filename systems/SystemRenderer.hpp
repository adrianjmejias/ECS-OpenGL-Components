#pragma once 

#include "../framework/System.hpp";

class SystemRenderer : public System
{
public:
    SystemRenderer() = default;
    SystemRenderer(SystemRenderer &&) = default;
    SystemRenderer(const SystemRenderer &) = default;
    SystemRenderer &operator=(SystemRenderer &&) = default;
    SystemRenderer &operator=(const SystemRenderer &) = default;
    virtual ~SystemRenderer() = default;
    virtual void Update() = 0;
    unsigned long lastVAO = 0;
private:
    
};

