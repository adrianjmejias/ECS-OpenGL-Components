#pragma once
#include "../framework/Component.hpp"
class MeshRenderer : public Component
{
public:
    MeshRenderer() = default;
    MeshRenderer(MeshRenderer &&) = default;
    MeshRenderer(const MeshRenderer &) = default;
    MeshRenderer &operator=(MeshRenderer &&) = default;
    MeshRenderer &operator=(const MeshRenderer &) = default;
    ~MeshRenderer() = default;
    

    public: int VAO_ID = -1;

    virtual void Update(){
        
    }


    public: void operator()(){

    }
private:
    
};