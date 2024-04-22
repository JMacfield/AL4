#pragma once

#pragma region standardInclude
#include <string>
#pragma endregion

#include <assimp/include/assimp/Importer.hpp>
#include <assimp/include/assimp/scene.h>
#include <assimp/include/assimp/postprocess.h>

#include "Enginebase/DirectXCommon.h"
#include "MyMath/MyMath.h"
#include "EngineBase/YTEngine.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineManager/Light/DirectionalLight.h"

class Model {
public:
	void Initialize( const std::string& directoryPath, const std::string& filename);
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection);
	void Finalize();

	static Model* CreateModelFromFile(const std::string& directoryPath, const std::string& filename);
	
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath,const std::string&filename);
	void SetColor(Vector4 color) { color_ = color; }

	Node ReadNode(aiNode* node);

	ModelData modelData_;
	ModelData LoadModelFile(const std::string& directoryPath, const std::string& filename);
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

private:
	TextureManager* textureManager_;
	DirectXCommon* directXCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	VertexData* vertexData_;

	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	
	Material* material_;
	YTEngine* engine_;
	uint32_t texture_;

	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	DirectionalLight* directionalLight_;
	
private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
};