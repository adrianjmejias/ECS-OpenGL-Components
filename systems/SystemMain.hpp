#pragma once

#include "../framework/System.hpp";
#include <vector>
#include <memory>

class SystemMain : public System
{
public:
    SystemMain() = default;
    SystemMain(SystemMain &&) = default;
    SystemMain(const SystemMain &) = default;
    SystemMain &operator=(SystemMain &&) = default;
    SystemMain &operator=(const SystemMain &) = default;
    virtual ~SystemMain() = default;
    virtual void Update() {

    }


    bool GetKey() {}
    bool GetKeyDown() {}
    bool GetKeyUp() {}



    std::vector<System> systems;

private:

};

