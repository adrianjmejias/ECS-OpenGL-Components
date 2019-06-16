#pragma once

#include "../framework/Component.hpp"

#include <memory>
#include <vector>



class Transform : public Component
{
public:
    Transform() = default;
    Transform(Transform &&) = default;
    Transform(const Transform &) = default;
    Transform &operator=(Transform &&) = default;
    Transform &operator=(const Transform &) = default;
    ~Transform() = default;

    
    std::shared_ptr<Transform> parent;
    std::vector<std::shared_ptr<Transform> > children;

    virtual void Update(){
        
    }
private:
    
};

typedef std::weak_ptr<Transform> h_reference_t; // h is for hierarchy