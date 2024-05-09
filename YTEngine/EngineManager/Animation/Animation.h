//#pragma once
//
//#include <map>
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include "MyMath/MyMath.h"
//
//struct KeyframeVector3 {
//	Vector3 value;
//	float time;
//};
//
//struct KeyframeQuaternion {
//	Quaternion value;
//	float time;
//};
//
//template<typename tValue>
//struct Keyframe {
//	float time;
//	tValue value;
//};
//
//using KeyframeVector3 = Keyframe<Vector3>;
//using keyFrameQuaternion = Keyframe<Quaternion>;
//
//struct NodeAnimation {
//	std::vector<KeyframeVector3> translate;
//	std::vector<KeyframeQuaternion> rotate;
//	std::vector<KeyframeVector3> scale;
//};
//
//template<typename tValue>
//struct AnimationCurve {
//	std::vector<Keyframe<tValue>> keyframes;
//};
//
//struct NodeAnimation {
//	AnimationCurve<Vector3> translate;
//	AnimationCurve<Quaternion> rotate;
//	AnimationCurve<Vector3> scale;
//};
//
//struct Animation {
//	float duration;
//	std::map<std::string, NodeAnimation> nodeAnimations;
//};
//
//class AnimationManager {
//public:
//	Animation LoadAnimationFile(const std::string& directoryPath, const std::string& fileName);
//
//private:
//
//};