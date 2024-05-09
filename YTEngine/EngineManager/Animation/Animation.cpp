//#include "EngineManager/Animation/Animation.h"
//
//Animation AnimationManager::LoadAnimationFile(const std::string& directoryPath, const std::string& fileName) {
//	Animation animation;
//	Assimp::Importer importer;
//
//	std::string filePath = directoryPath + "/" + fileName;
//
//	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);
//	assert(scene->mNumAnimations != 0);
//
//	aiAnimation* animationAssimp = scene->mAnimations[0];
//	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);
//
//	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex) {
//		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];
//		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];
//
//		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex) {
//			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];
//			KeyframeVector3 keyframe;
//			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyframe.value = { -keyAssimp.mValue.x, keyAssimp.mValue.y, keyAssimp.mValue.z };
//			nodeAnimation.translate.keyframes.push_back(keyframe);
//		}
//
//		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex) {
//			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];
//			KeyframeQuaternion keyframe;
//			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyframe.value = { keyAssimp.mValue.x, -keyAssimp.mValue.y, -keyAssimp.mValue.z, keyAssimp.mValue.w };
//			//nodeAnimation.rotate.keyframes.push_back(keyframe);
//		}
//
//		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; ++keyIndex) {
//			aiVectorKey& keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];
//			KeyframeVector3 keyframe;
//			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
//			keyframe.value = { keyframe.value.x, keyframe.value.y , keyframe.value.z };
//			nodeAnimation.scale.keyframes.push_back(keyframe);
//		}
//	}
//
//	return animation;
//}