#pragma once

#include "../framework/Component.hpp"
#include <vector>
#include <string>
class Entity
{
public:
    Entity() = default;
    Entity(Entity &&) = default;
    Entity(const Entity &) = default;
    Entity &operator=(Entity &&) = default;
    Entity &operator=(const Entity &) = default;
    virtual ~Entity() = default;
    virtual void Update() {
        for (size_t i = 0; i < components.size(); i++)
        {
            components[i]->Update();
        }

    }

    std::vector< std::shared_ptr<Component> > components;
    std::string name;
    private:
    
};
