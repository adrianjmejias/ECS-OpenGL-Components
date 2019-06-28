#pragma once

class API;

class IStartable{
    virtual void Start(const API &api) = 0;
};
    
