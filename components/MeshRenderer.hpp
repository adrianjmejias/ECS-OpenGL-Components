#pragma once
#include <GL/gl3w.h> 
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
    

    public: unsigned int VAO_ID = -1;


    


    virtual void Update(){


        //glBindBuffer(VAO_ID, GL_ARRAY_BUFFER);

        ////glDrawArrays(GL_TRIANGLES, )

        //glBindBuffer(0, GL_ARRAY_BUFFER);
    }


    public: void operator()(){

    }
private:




    
};
