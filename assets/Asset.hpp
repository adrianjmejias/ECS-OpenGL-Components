#pragma once 
#include <string>

class Asset
{
public:
    Asset() = default;
    Asset(Asset &&) = default;
    Asset(const Asset &) = default;
    Asset &operator=(Asset &&) = default;
    Asset &operator=(const Asset &) = default;
    ~Asset() = default;


    public: std::string path;
    public: std::string name;
private:
    
};