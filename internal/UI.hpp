#pragma once
// #include <>
#include "../internal/index.hpp"

#include <AntTweakBar\AntTweakBar.h>
#include <memory>
#include <vector>
#include "../internal/ITweakable.hpp"

class UI{
	//friend class API;
	TwBar* ui;

	
	std::vector<ITweakable*> tweaks;
	unsigned int idsTw = 0;
public:

	void AddITweakable(ITweakable *tw) {


		tw->DebugUI(ui, idsTw);

		Transform * t = dynamic_cast<Transform*>(tw);
		if (t) {
			idsTw++;
		}
		tweaks.push_back(tw);
	}

public: bool Init() {
		bool success = TwInit(TW_OPENGL, NULL);

		ui = TwNewBar("Model");

		TwDefine("Model refresh = '0.0001f'");
		TwDefine("Model resizable = false");
		TwDefine("Model fontresizable = false");
		TwDefine("Model movable = true");
		TwDefine("Model position = '20 20'");
		TwDefine("Model size = '220 320'");

		TwWindowSize(500, 500);

		
		return success;
}
	UI() {
	}

	~UI(){
		TwDeleteBar(ui);
	}


public: void Update() {
	TwDraw();
}

public: void Reshape(int width, int height){
        TwWindowSize(width, height);
    }
};