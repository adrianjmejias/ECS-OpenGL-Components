#pragma once



class Entity
{
public:
    Entity() = default;
    Entity(Entity &&) = default;
    Entity(const Entity &) = default;
    Entity &operator=(Entity &&) = default;
    Entity &operator=(const Entity &) = default;
    virtual ~Entity() = default;
    virtual void Update() = 0;
private:
    
};