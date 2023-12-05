#pragma once

#include "MyMath/MyMath.h"

struct Quaternion {
	float x, y, z, w;
};

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

Quaternion IdentityQuaternion();

Quaternion Conjugate(const Quaternion& quaternion);

float Norm(const Quaternion& quaternion);

Quaternion Normalize(const Quaternion& quaternion);

Quaternion Inverse(const Quaternion& quaternion);