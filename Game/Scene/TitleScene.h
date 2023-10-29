#pragma once

#include "Iscene.h"
#include "EngineManager/Input/Input.h"

class TitleScene : public Iscene {
public:
	~TitleScene()override;
	 
	void Initialize() override;

	 void Update() override;

	 void Draw() override;
	
	 void Finalize()override;

private:
	Input* input = nullptr;
	int count;
};