#pragma once
#include "Asset.hpp"

#include "../framework/Component.hpp"
#include "../components/Transform.hpp"
#include <vector>
#include <memory>
class Object : Asset
{
public:
    Object() = default;
    Object(Object &&) = default;
    Object(const Object &) = default;
    Object &operator=(Object &&) = default;
    Object &operator=(const Object &) = default;
    ~Object() = default;
    std::shared_ptr<Transform> transform;

    template <typename comp_t>
    std::shared_ptr<Component> GetComponent() const {
        
    }
    
    template <typename comp_t>
    std::shared_ptr<comp_t> AddComponent(std::shared_ptr<comp_t> comp){

        components.push_back(std::static_pointer_cast<std::shared_ptr<Component> >(comp));

        return comp;
    }

    void Update(){
        for (auto &&i : components)
        {
            i->Update();
        }
        
    }
private:
    std::vector<std::shared_ptr<Component> > components;
    
};