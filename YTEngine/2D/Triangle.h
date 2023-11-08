#pragma once

#include "EngineBase/DirectXCommon.h"
#include "MyMath/MyMath.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineManager/Light/DirectionalLight.h"

class YTEngine;

class Triangle {
public:
	void Initialize(  );
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const Vector4& material);
	void Finalize();
	
private:
	void SettingVertex();
	void SetColor();
	void TransformMatrix();
	
private:
	TextureManager* textureManager_;
	YTEngine* engine_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	DirectXCommon* directXCommon_;
	VertexData* vertexData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	Material *materialData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	DirectionalLight* directionalLight_;
};