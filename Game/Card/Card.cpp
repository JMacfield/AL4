#include "Card/Card.h"

void Card::Initialize() {
	textureManager_ = TextureManager::GetInstance();
	input_ = Input::GetInstance();

	spriteTexture_[0] = textureManager_->Load("Resource/Card/playerturn.png");
	spriteTexture_[1] = textureManager_->Load("Resource/Card/enemyturn.png");

	Vector4 a = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b = { 300.0f,100.0f,0.0f,1.0f };

	sprite_[0] = std::make_unique<Sprite>();
	sprite_[0]->Initialize(a, b);

	sprite_[1] = std::make_unique<Sprite>();
	sprite_[1]->Initialize(a, b);

	spriteTransform_[0] = { {0.5f,0.5f, 0.5f},{0.0f,0.0f,0.0f},{100.0f,250.0f,0.0f} };
	spriteTransform_[1] = { {0.5f,0.5f, 0.5f},{0.0f,0.0f,0.0f},{100.0f,100.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	spriteMaterial_[0] = { 1.0f,1.0f,1.0f,1.0f };
	spriteMaterial_[1] = { 1.0f,1.0f,1.0f,1.0f };

	arrow_ = std::make_unique<Model>();
	arrow_.reset(Model::CreateModelFromObj("Resource/Arrow", "plane.obj"));
	arrowTransform_.Initialize();
	arrowTransform_.translation_ = { 0.0f,2.0f,-8.0f };

	enemyModel_ = std::make_unique<Model>();
	enemyModel_.reset(Model::CreateModelFromObj("Resource/Enemy", "plane.obj"));
	enemyTransform_.Initialize();
	enemyTransform_.translation_ = { 0.0f,4.0f,16.0f };
	enemyTransform_.scale_ = { 6.0f,6.0f,6.0f };

	enemyHandModel_ = std::unique_ptr<Model>();
	enemyHandModel_.reset(Model::CreateModelFromObj("Resource/EnemyHand", "plane.obj"));
	enemyHandTransform_.Initialize();
	enemyHandTransform_.translation_ = { 0.0f,4.0f,-8.0f };

	table_ = std::make_unique<Model>();
	table_.reset(Model::CreateModelFromObj("Resource/Wall", "plane.obj"));
	tableTransform_.Initialize();
	tableTransform_.translation_ = { 0.0f,-1.0f,0.0f };
	tableTransform_.scale_ = { 100.0f,100.0f,100.0f };
	tableTransform_.rotation_ = { 4.75f,0.0f,0.0f };

	nowTurn_ = PlayerTurn;

	pTimer = 0;
	pFlag = false;

	isWin = false;

	for (int i = 0; i < 20; i++) {
		isShown[i] = true;
	}

	for (int i = 0; i < 7; i++) {
		redModel_[i] = std::make_unique<Model>();
		blueModel_[i] = std::make_unique<Model>();
		yellowModel_[i] = std::make_unique<Model>();
		greenModel_[i] = std::make_unique<Model>();

		redTransform_[i].Initialize();
		blueTransform_[i].Initialize();
		yellowTransform_[i].Initialize();
		greenTransform_[i].Initialize();
	}

	count = 0;

	redModel_[0].reset(Model::CreateModelFromObj("Resource/Card/Red0", "plane.obj"));
	redModel_[1].reset(Model::CreateModelFromObj("Resource/Card/Red1", "plane.obj"));
	redModel_[2].reset(Model::CreateModelFromObj("Resource/Card/Red2", "plane.obj"));
	redModel_[3].reset(Model::CreateModelFromObj("Resource/Card/Red3", "plane.obj"));
	redModel_[4].reset(Model::CreateModelFromObj("Resource/Card/Red4", "plane.obj"));
	redModel_[5].reset(Model::CreateModelFromObj("Resource/Card/Red5", "plane.obj"));
	redModel_[6].reset(Model::CreateModelFromObj("Resource/Card/Red6", "plane.obj"));

	blueModel_[0].reset(Model::CreateModelFromObj("Resource/Card/Blue0", "plane.obj"));
	blueModel_[1].reset(Model::CreateModelFromObj("Resource/Card/Blue1", "plane.obj"));
	blueModel_[2].reset(Model::CreateModelFromObj("Resource/Card/Blue2", "plane.obj"));
	blueModel_[3].reset(Model::CreateModelFromObj("Resource/Card/Blue3", "plane.obj"));
	blueModel_[4].reset(Model::CreateModelFromObj("Resource/Card/Blue4", "plane.obj"));
	blueModel_[5].reset(Model::CreateModelFromObj("Resource/Card/Blue5", "plane.obj"));
	blueModel_[6].reset(Model::CreateModelFromObj("Resource/Card/Blue6", "plane.obj"));

	yellowModel_[0].reset(Model::CreateModelFromObj("Resource/Card/Yellow0", "plane.obj"));
	yellowModel_[1].reset(Model::CreateModelFromObj("Resource/Card/Yellow1", "plane.obj"));
	yellowModel_[2].reset(Model::CreateModelFromObj("Resource/Card/Yellow2", "plane.obj"));
	yellowModel_[3].reset(Model::CreateModelFromObj("Resource/Card/Yellow3", "plane.obj"));
	yellowModel_[4].reset(Model::CreateModelFromObj("Resource/Card/Yellow4", "plane.obj"));
	yellowModel_[5].reset(Model::CreateModelFromObj("Resource/Card/Yellow5", "plane.obj"));
	yellowModel_[6].reset(Model::CreateModelFromObj("Resource/Card/Yellow6", "plane.obj"));

	greenModel_[0].reset(Model::CreateModelFromObj("Resource/Card/Green0", "plane.obj"));
	greenModel_[1].reset(Model::CreateModelFromObj("Resource/Card/Green1", "plane.obj"));
	greenModel_[2].reset(Model::CreateModelFromObj("Resource/Card/Green2", "plane.obj"));
	greenModel_[3].reset(Model::CreateModelFromObj("Resource/Card/Green3", "plane.obj"));
	greenModel_[4].reset(Model::CreateModelFromObj("Resource/Card/Green4", "plane.obj"));
	greenModel_[5].reset(Model::CreateModelFromObj("Resource/Card/Green5", "plane.obj"));
	greenModel_[6].reset(Model::CreateModelFromObj("Resource/Card/Green6", "plane.obj"));

	//red.suit[0] = 'r';
	//red.suit[1] = 'b';
	//red.suit[2] = 'y';
	//red.suit[3] = 'g';

	//blue.suit[0] = 'r';
	//blue.suit[1] = 'b';
	//blue.suit[2] = 'y';
	//blue.suit[3] = 'g';

	//yellow.suit[0] = 'r';
	//yellow.suit[1] = 'b';
	//yellow.suit[2] = 'y';
	//yellow.suit[3] = 'g';

	//green.suit[0] = 'r';
	//green.suit[1] = 'b';
	//green.suit[2] = 'y';
	//green.suit[3] = 'g';

	//3.315
	/*for (int i = 0; i < 7; i++) {
		redTransform_[i].translation_ = { 0.0f,0.0f,-8.0f };
		blueTransform_[i].translation_ = { 0.0f,0.0f,-8.0f };
		yellowTransform_[i].translation_ = { 0.0f,0.0f,-8.0f };
		greenTransform_[i].translation_ = { 0.0f,0.0f,-8.0f };
	}*/
	
	blueTransform_[5].translation_ = { 3.0f,0.0f,-1.0f };
	blueTransform_[5].rotation_ = { 1.3f,0.0f,0.0f };

	redTransform_[0].translation_ = { -6.0f,0.0f,-8.0f };
	blueTransform_[0].translation_ = { -3.0f,0.0f,-8.0f };
	yellowTransform_[3].translation_ = { 0.0f,0.0f,-8.0f };
	yellowTransform_[2].translation_ = { 3.0f,0.0f,-8.0f };
	greenTransform_[1].translation_ = { 6.0f,0.0f,-8.0f };

	redTransform_[3].translation_ = { -6.0f,0.0f,8.0f };
	redTransform_[3].rotation_ = { 0.0f,3.35f,0.0f };
	redTransform_[1].translation_ = { -3.0f,0.0f,8.0f };
	redTransform_[1].rotation_ = { 0.0f,3.35f,0.0f };
	blueTransform_[2].translation_ = { 0.0f,0.0f,8.0f };
	blueTransform_[2].rotation_ = { 0.0f,3.35f,0.0f };
	yellowTransform_[4].translation_ = { 3.0f,0.0f,8.0f };
	yellowTransform_[4].rotation_ = { 0.0f,3.35f,0.0f };
	yellowTransform_[1].translation_ = { 6.0f,0.0f,8.0f };
	yellowTransform_[1].rotation_ = { 0.0f,3.35f,0.0f };

	select_ = 0;

	//Particle* particle = new Particle();
	//particle->Initialize({3.0f,0.0f,-1.0f});
	//particles_.push_back(std::unique_ptr<Particle>(particle));

	//StartCard();

	moveRight = true;
}

void Card::Update() {
	uint16_t T = 120;

	float step = 2.0f * (float)M_PI / T;
	float floatingAmplitude = 0.3f;

	floatingParametor_ += step;
	floatingParametor_ = (float)std::fmod(floatingParametor_, 2.0f * M_PI);

	enemyTransform_.translation_.y = std::sin(floatingParametor_) * floatingAmplitude + 1.0f;

	particles_.remove_if([](std::unique_ptr<Particle>& particle) {
		if (particle->GetIsAlive() == false)
		{
			particle.reset();
			return true;
		}
		return false;
		});

	for (const std::unique_ptr<Particle>& particle : particles_) {
		particle->Update();
	}

	if (pFlag == true) {
		pTimer++;
		
		Particle* particle = new Particle();
		particle->Initialize({3.0f,0.0f,-1.0f});
		particles_.push_back(std::unique_ptr<Particle>(particle));
	}

	if (pTimer > 5) {
		pFlag = false;
		pTimer = 0;
	}

	for (int i = 0; i < 6; i++) {
		redTransform_[i].UpdateMatrix();
		blueTransform_[i].UpdateMatrix();
		yellowTransform_[i].UpdateMatrix();
		greenTransform_[i].UpdateMatrix();
	}

	arrowTransform_.UpdateMatrix();
	tableTransform_.UpdateMatrix();
	enemyTransform_.UpdateMatrix();
	enemyHandTransform_.UpdateMatrix();

	if (nowTurn_ == PlayerTurn) {
		spriteMaterial_[1] = { 1.0f,1.0f,1.0f,0.4f };
		spriteMaterial_[0] = { 1.0f,1.0f,1.0f,1.0f };
	}
	else {
		spriteMaterial_[0] = { 1.0f,1.0f,1.0f,0.4f };
		spriteMaterial_[1] = { 1.0f,1.0f,1.0f,1.0f };
	}

	// カーソルの移動
	if (input_->PushKey(DIK_A)) {
		arrowTransform_.translation_.x -= 3.0f;
	}
	if (input_->PushKey(DIK_D)) {
		arrowTransform_.translation_.x += 3.0f;
	}

	switch (nowTurn_) {
	case PlayerTurn:
		if (isShown[0] == true) {
			if (input_->PushKey(DIK_SPACE) && arrowTransform_.translation_.x == -3.0f) {
				isShown[0] = false;
				pFlag = true;
				blueTransform_[0].translation_ = { 3.0f,0.0f,-1.0f };
				blueTransform_[0].rotation_ = { 1.3f,0.0f,0.0f };
				nowTurn_ = EnemyTurn;
			}
		}

		if (isShown[2] == true && isShown[3] == false) {
			if (input_->PushKey(DIK_SPACE) && arrowTransform_.translation_.x == 0.0f) {
				isShown[5] = false;
				pFlag = true;
				yellowTransform_[3].translation_ = { 3.0f,0.0f,-1.0f };
				yellowTransform_[3].rotation_ = { 1.3f,0.0f,0.0f };
				nowTurn_ = EnemyTurn;
			}
		}

		if (isShown[3] == true && isShown[0] == false) {
			if (input_->PushKey(DIK_SPACE) && arrowTransform_.translation_.x == 3.0f) {
				isShown[4] = false;
				pFlag = true;
				yellowTransform_[2].translation_ = { 3.0f,0.0f,-1.0f };
				yellowTransform_[2].rotation_ = { 1.3f,0.0f,0.0f };
				nowTurn_ = EnemyTurn;
			}
		}

		if (isShown[7] == true && isShown[2] == false) {
			if (input_->PushKey(DIK_SPACE) && arrowTransform_.translation_.x == 6.0f) {
				isShown[6] = false;
				pFlag = true;
				greenTransform_[1].translation_ = { 3.0f,0.0f,-1.0f };
				greenTransform_[1].rotation_ = { 1.3f,0.0f,0.0f };
				nowTurn_ = EnemyTurn;
			}
		}

		if (isShown[8] == true && isShown[7] == false) {
			if (input_->PushKey(DIK_SPACE) && arrowTransform_.translation_.x == -6.0f) {
				isShown[7] = false;
				pFlag = true;
				redTransform_[1].translation_ = { 3.0f,0.0f,-1.0f };
				redTransform_[1].rotation_ = { 1.3f,0.0f,0.0f };
				//nowTurn_ = EnemyTurn;
				isWin = true;
			}
		}

		break;

	case EnemyTurn:
		if (nowTurn_ == EnemyTurn) {
			timer++;

			if (moveRight == true) {
				if (timer % 60 == 0) {
					enemyHandTransform_.translation_.x += 1.5f;
				}
				if (enemyHandTransform_.translation_.x > 3.0f) {
					moveRight = false;
					enemyHandTransform_.translation_.x = 3.0f;
				}
			}

			if (moveRight == false) {
				if (timer % 60 == 0) {
					enemyHandTransform_.translation_.x -= 1.5f;
				}
				if (enemyHandTransform_.translation_.x < -3.0f) {
					moveRight = true;
					enemyHandTransform_.translation_.x = -3.0f;
				}
			}
		}

		if (timer > 300 && count == 0) {
			if (isShown[1] == true) {
				isShown[1] = false;
				blueTransform_[2].translation_ = { 3.0f,0.0f,-1.0f };
				blueTransform_[2].rotation_ = { 1.3f,0.0f,0.0f };
				timer = 0;
				count += 1;
				nowTurn_ = PlayerTurn;
			}
		}

		if (timer > 300 && count == 1) {
			if (isShown[5] == true) {
				isShown[3] = false;
				yellowTransform_[4].translation_ = { 3.0f,0.0f,-1.0f };
				yellowTransform_[4].rotation_ = { 1.3f,0.0f,0.0f };
				timer = 0;
				count += 1;
				nowTurn_ = PlayerTurn;
			}
		}

		if (timer > 300 && count == 2) {
			if (isShown[6] == true) {
				isShown[5] = false;
				isShown[2] = false;
				yellowTransform_[1].translation_ = { 3.0f,0.0f,-1.0f };
				yellowTransform_[1].rotation_ = { 1.3f,0.0f,0.0f };
				timer = 0;
				count += 1;
				nowTurn_ = PlayerTurn;
			}
		}

		if (timer > 300 && count == 3) {
			if (isShown[7] == true) {
				isShown[7] = false;
				redTransform_[3].translation_ = { 3.0f,0.0f,-1.0f };
				redTransform_[3].rotation_ = { 1.3f,0.0f,0.0f };
				timer = 0;
				count += 1;
				nowTurn_ = PlayerTurn;
			}
		}

		break;
	}

	// カーソルの移動制限
	if (arrowTransform_.translation_.x < -6.0f) {
		arrowTransform_.translation_.x = -6.0f;
	}
	if (arrowTransform_.translation_.x > 6.0f) {
		arrowTransform_.translation_.x = 6.0f;
	}

	ImGui::Begin("Debug");
	ImGui::DragFloat3("Rotate", &tableTransform_.rotation_.x, 0.1f);
	ImGui::DragInt("Timer", &timer);
	ImGui::DragInt("Count", &count);
	ImGui::DragFloat3("Trans", &enemyHandTransform_.translation_.x, 0.1f);
	ImGui::End();
}

void Card::Draw(const ViewProjection& viewProjection) {
	//if (input_->PushKey(DIK_SPACE)) {
		for (const std::unique_ptr<Particle>& particle : particles_) {
			particle->Draw(viewProjection);
		}
	//}

	enemyModel_->Draw(enemyTransform_, viewProjection);

	//if (nowTurn_ == EnemyTurn) {
		enemyHandModel_->Draw(enemyHandTransform_, viewProjection);
	//}
	
	table_->Draw(tableTransform_, viewProjection);

	if (isShown[0] == true) {
		blueModel_[5]->Draw(blueTransform_[5], viewProjection);
	}

	if (isShown[1] == true) {
		blueModel_[0]->Draw(blueTransform_[0], viewProjection);
	}

	if (isShown[2] == true) {
		yellowModel_[3]->Draw(yellowTransform_[3], viewProjection);
	}

	if (isShown[3] == true) {
		yellowModel_[2]->Draw(yellowTransform_[2], viewProjection);
	}

	if (isShown[4] == true) {
		blueModel_[2]->Draw(blueTransform_[2], viewProjection);
	}

	if (isShown[5] == true) {
		yellowModel_[4]->Draw(yellowTransform_[4], viewProjection);
	}

	if (isShown[6] == true) {
		yellowModel_[1]->Draw(yellowTransform_[1], viewProjection);
	}

	if (isShown[7] == true) {
		greenModel_[1]->Draw(greenTransform_[1], viewProjection);
	}

	if (isShown[8] == true) {
		redModel_[3]->Draw(redTransform_[3], viewProjection);
	}

	if (isShown[9] == true) {

	}

	redModel_[0]->Draw(redTransform_[0], viewProjection);

	redModel_[1]->Draw(redTransform_[1], viewProjection);

	arrow_->Draw(arrowTransform_, viewProjection);
	
}

void Card::Draw2D() {
	sprite_[0]->Draw(spriteTransform_[0], spriteUvTransform_, spriteMaterial_[0], spriteTexture_[0]);
	sprite_[1]->Draw(spriteTransform_[1], spriteUvTransform_, spriteMaterial_[1], spriteTexture_[1]);
}

void Card::StartCard() {
	srand((unsigned int)time(NULL));

	playerHand_[0].rank = rand() % 5 + 0;
	playerHand_[1].rank = rand() % 5 + 0;
	playerHand_[2].rank = rand() % 5 + 0;
	playerHand_[3].rank = rand() % 5 + 0;
	playerHand_[4].rank = rand() % 5 + 0;
}