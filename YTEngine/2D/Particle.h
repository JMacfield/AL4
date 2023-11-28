#pragma once

#include "EngineBase/DirectXCommon.h"
#include "MyMath/MyMath.h"
#include "EngineBase/YTEngine.h"
#include "EngineManager/Light/DirectionalLight.h"
#include "EngineManager/Texture/TextureManager.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineBase/SrvDescriptorHeap.h"
#include <random>
#include <list>

class Particle {
public:
	void Initialize(uint32_t Drawparticle);
	void Update();
	void Draw(const ViewProjection& viewProjection, const Vector4& material, uint32_t index);
	
	void Finalize();
	void AddParticle(const Emitter& emitter, const int& count);

private:
	void SettingVertex();
	void SetColor();
	void TransformMatrix();
	void CreateSRV(uint32_t num);

private:
	TextureManager* textureManager_;
	SrvDescriptorHeap* srvHeap_;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	DirectXCommon* direct_;
	VertexData* vertexData_;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	Material* materialData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	
	Transformmatrix* wvpData_;
	DirectionalLight* directionalLight_;
	
	static	const uint32_t kNumMaxInstance_ = 100000;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> instancingResource_;
	ParticleForGPU* instancingData;
	std::list<ParticleData>particles_;
	
	uint32_t index_;
	int knumInstance_;
	uint32_t DrawInstanceNum_;
	int instanceCount;

private:
	ParticleData MakeNewParticle(const Emitter& emitter, std::mt19937& randomEngine);
};