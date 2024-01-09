#pragma once

#include "Iscene.h"
#include "EngineManager/Input/Input.h"
#include "CommSystem/CommSystem.h"

class ClearScene : public Iscene {
public:
	~ClearScene()override;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize()override;

private:
	Input* input = nullptr;
	int count;
};