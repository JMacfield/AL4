#pragma once

#include "2D/Sprite.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Texture/TextureManager.h"
#include "3D/Model.h"
#include "2D/Particle.h"

#include <memory>
#include <string>
#include <stdlib.h>

typedef struct {
	char suit;
	int rank;
} CardType;

enum Turn {
	PlayerTurn,
	EnemyTurn,
};

class Card {
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void Draw2D();

	void StartCard();

	bool GetWin() { return isWin; }

private:
	TextureManager* textureManager_;
	Input* input_;

	uint32_t spriteTexture_[2];
	std::unique_ptr<Sprite> sprite_[2];
	Transform spriteTransform_[2];
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_[2];

	WorldTransform redTransform_[7];
	WorldTransform blueTransform_[7];
	WorldTransform yellowTransform_[7];
	WorldTransform greenTransform_[7];

	std::unique_ptr<Model> redModel_[7];
	std::unique_ptr<Model> blueModel_[7];
	std::unique_ptr<Model> yellowModel_[7];
	std::unique_ptr<Model> greenModel_[7];

	std::unique_ptr<Model> enemyModel_;
	std::unique_ptr<Model> enemyHandModel_;
	WorldTransform enemyTransform_;
	WorldTransform enemyHandTransform_;

	/*CardType red;
	CardType blue;
	CardType yellow;
	CardType green;*/

	CardType playerHand_[5];
	CardType enemyHand_[5];

	int nowTurn_;
	int select_;

	std::unique_ptr<Model> arrow_;
	WorldTransform arrowTransform_;

	std::unique_ptr<Model> table_;
	WorldTransform tableTransform_;

	std::list<std::unique_ptr<Particle>> particles_;

	bool isShown[20];
	int timer;
	int count;

	int pTimer;
	bool pFlag;

	bool isWin;

	bool moveRight;

	float floatingParametor_ = 0.0f;
};