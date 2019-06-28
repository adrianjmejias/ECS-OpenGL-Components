#pragma once
#include "../framework/UpdatableComponent.hpp"
#include "../internal/API.hpp"

class ShaderProgram;
class ReloadShader : public StartableComponent
{
public:

	std::vector<ShaderProgram*> shaderPrograms;


	virtual void Start(const API &api) {
		
		api.RegisterGetKeyDown(KeyCode::R, [&]() {
			for (auto *shaderProgram : shaderPrograms) {
				shaderProgram->ReCompile();

			}
		});
		api.RegisterGetKeyDown(KeyCode::ESCAPE, [&]() {
			api.Close();

		});
	}


    virtual void Update(const API &api){
    }
private:
    
};
