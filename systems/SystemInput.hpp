#pragma once 

#include "../framework/System.hpp";


class SystemInput : public System
{
public:
    SystemInput() = default;
    SystemInput(SystemInput &&) = default;
    SystemInput(const SystemInput &) = default;
    SystemInput &operator=(SystemInput &&) = default;
    SystemInput &operator=(const SystemInput &) = default;
    virtual ~SystemInput() = default;
    virtual void Update() = 0;


    bool GetKey(){}
    bool GetKeyDown(){}
    bool GetKeyUp(){}
    
private:
    
};

