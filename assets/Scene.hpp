#pragma once


#include <vector>
#include "Object.hpp"
class Scene
{
public:
    Scene() = default;
    Scene(Scene &&) = default;
    Scene(const Scene &) = default;
    Scene &operator=(Scene &&) = default;
    Scene &operator=(const Scene &) = default;
    ~Scene() = default;


    bool AddObject(const std::shared_ptr<Object> object){
        rootNodes.push_back(object);

        return true;
    }
    void update(){
        for (auto &&i : rootNodes)
        {
            i->Update();
        }    
    }
private:
    std::vector<std::shared_ptr<Object> > rootNodes;
};