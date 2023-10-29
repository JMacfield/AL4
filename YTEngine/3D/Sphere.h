#pragma once

#include "EngineBase/DirectXCommon.h"
#include "MyMath/MyMath.h"
#include "EngineBase/YTEngine.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineManager/Light/DirectionalLight.h"

class Sphere {
public:
	void Initialize();
	void Draw(const Vector4& material, const WorldTransform& transform, uint32_t texIndex, const ViewProjection& viewProjection);
	
	void Finalize();

private:
	TextureManager* textureManager_;
	DirectionalLight* directionalLight_; 
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	VertexData* vertexData_;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	
	Material* materialData_;
	YTEngine* engine_;
	
	const float pi = 3.14159265358979f;
	
	uint32_t kSubDivision;
	uint32_t vertexCount;
	
private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
};