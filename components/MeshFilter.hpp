#pragma once
#include "../framework/Component.hpp"
#include "../assets/Mesh.hpp"

#include <memory>
class MeshFilter : public Component
{
public:
    std::shared_ptr<Mesh> mesh;

    MeshFilter(std::shared_ptr<Mesh> mesh){
        this->mesh = mesh;
    }
    MeshFilter(MeshFilter &&) = default;
    MeshFilter(const MeshFilter &) = default;
    MeshFilter &operator=(MeshFilter &&) = default;
    MeshFilter &operator=(const MeshFilter &) = default;
    ~MeshFilter() = default;
    virtual void Update(){
        
    }
private:
    
};