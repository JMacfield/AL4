#pragma once

#include "Object/Ground/Ground.h"
#include "Object/Ground/MoveGround.h"
#include "3D/ViewProjection.h"
#include "3D/Model.h"
#include "MyMath/MyMath.h"

#include <memory>

using namespace std;

class GroundManager {
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& view);
	
	OBB GetOBB(int num) { return Obb_[num]; }
    MoveGround* GetMoveGround() { return moveGround_.get(); }
	Ground* GetGround(int num) { return ground_->get(); }

private:
	unique_ptr<Ground>ground_[2];
	unique_ptr<MoveGround> moveGround_;
	unique_ptr<Model> model_;
	unique_ptr<Model> movemodel_;
	OBB Obb_[3];
};