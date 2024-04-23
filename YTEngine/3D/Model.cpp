#include "Model.h"

#include<fstream>
#include<sstream>

void Model::Initialize( const std::string& directoryPath, const std::string& filename) {
    directXCommon_ = DirectXCommon::GetInstance();
	engine_ = YTEngine::GetInstance();
    
    textureManager_ = TextureManager::GetInstance();
    modelData_ = LoadModelFile(directoryPath, filename);
    //modelData_ = LoadObjFile(directoryPath, filename);
    
    texture_ = textureManager_->Load(modelData_.material.textureFilePath);
    
    directionalLight_ = DirectionalLight::GetInstance();
	
    CreateVartexData();
	SetColor();

    material_->enableLighting = true;
}

void Model::Draw(const WorldTransform& transform, const ViewProjection& viewProjection) {
    Transform uvTransform = { { 1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
    //Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale_, transform.rotation_, transform.translation_);
    //Matrix4x4 projectionmatrix = MakeOrthographicMatrix(0.0f, 0.0f, (float)directXCommon_->GetWin()->kClientWidth, (float)directXCommon_->GetWin()->kClientHeight, 0.0f, 100.0f);

    Matrix4x4 uvtransformMtrix = MakeScaleMatrix(uvTransform.scale);
    uvtransformMtrix = Multiply(uvtransformMtrix, MakeRotateZMatrix(uvTransform.rotate.z));
    uvtransformMtrix = Multiply(uvtransformMtrix, MakeTranslateMatrix(uvTransform.translate));

    //wvpData_->WVP = Multiply(modelData_.rootNode.localMatrix, Multiply(worldMatrix, projectionmatrix));
    //wvpData_->World = Multiply(modelData_.rootNode.localMatrix, worldMatrix);

    *material_ = { color_,true };
    material_->uvTransform = uvtransformMtrix;
  
    directXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView); 
    //形状を設定。PS0にせっていしているものとはまた別。同じものを設定すると考えておけばいい
    directXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //material
    directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
    //worldTransform
    directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_->GetGPUVirtualAddress());
    //viewProjection
    directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
    //Light
    directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLight_->GetResource()->GetGPUVirtualAddress());
    //texture
    directXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(texture_));
    //Draw
    directXCommon_->GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
}

void Model::Finalize() {
   
}

Model* Model::CreateModelFromFile(const std::string& directoryPath, const std::string& filename) {
    Model* model = new Model();
    model->Initialize(directoryPath, filename);

    return model;
}

ModelData Model::LoadModelFile(const std::string& directoryPath, const std::string& filename) {
    ModelData modelData;
    
    Assimp::Importer importer;
    std::string filePath = directoryPath + "/" + filename;
   
    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
    
    assert(scene->HasMeshes());

    for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
        aiMesh* mesh = scene->mMeshes[meshIndex];

        assert(mesh->HasNormals());
        assert(mesh->HasTextureCoords(0));

        for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
            aiFace& face = mesh->mFaces[faceIndex];

            assert(face.mNumIndices == 3);

            for (uint32_t element = 0; element < face.mNumIndices; ++element) {
                uint32_t vertexIndex = face.mIndices[element];

                aiVector3D& position = mesh->mVertices[vertexIndex];
                aiVector3D& normal = mesh->mNormals[vertexIndex];
                aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];

                VertexData vertex = {};

                vertex.position = { position.x,position.y,position.z,1.0f };
                vertex.position.x *= -1.0f;	vertex.normal = { normal.x,normal.y,normal.z };
                vertex.texcoord = { texcoord.x,texcoord.y };

                vertex.position.x *= -1.0f;
                vertex.normal.x *= -1.0f;
                modelData.vertices.push_back(vertex);
            }
        }
    }

    for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
        aiMaterial* material = scene->mMaterials[materialIndex];

        if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
            aiString textureFilePath;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
            modelData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
        }
    }

    modelData.rootNode = ReadNode(scene->mRootNode);

    return modelData;
}

ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename) {
    ModelData modelData;//構築するモデルデータ
    std::vector<Vector4> positions;//位置
    std::vector<Vector3> normals;//法線
    std::vector<Vector2> texcoords;//テクスチャ座標
    std::string line;//ファイルから読んだ一行を格納する

    std::ifstream file(directoryPath + "/" + filename);
    assert(file.is_open());

    while (std::getline(file, line)) {
        std::string identifier;
        std::istringstream s(line);
        s >> identifier;//先頭の識別子を読む

        //identifierに応じた処理
        if (identifier == "v") {
            Vector4 position;
            s >> position.x >> position.y >> position.z;
            position.z *= -1.0f;
            position.w = 1.0f;
            positions.push_back(position);
        }
        else if (identifier == "vt") {
            Vector2 texcoord;
            s >> texcoord.x >> texcoord.y;
            texcoord.y = 1.0f - texcoord.y;
            texcoords.push_back(texcoord);
        }
        else if (identifier == "vn") {
            Vector3 normal;
            s >> normal.x >> normal.y >> normal.z;
            normal.z *= -1.0f;
            normals.push_back(normal);
        }
        else if (identifier == "f") {
            VertexData triangle[3];
            //面は三角形限定 その他は未対応
            for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
                std::string vertexDefinition;
                s >> vertexDefinition;
                
                //頂点の要素へのIndexは[位置/UV/法線]で格納されているので、分解してIndexを取得する
                std::istringstream v(vertexDefinition);
                uint32_t elementIndeices[3];
                
                for (int32_t element = 0; element < 3; ++element) {
                    std::string index;
                    std::getline(v, index, '/');//  /区切りでIndexを積んでいく
                    elementIndeices[element] = std::stoi(index);
                }
                
                //要素へのIndexから、実際の要素の値を取得して、頂点を構築する
                Vector4 position = positions[elementIndeices[0] - 1];
                Vector2 texcoord = texcoords[elementIndeices[1] - 1];
                Vector3 normal = normals[elementIndeices[2] - 1];
                VertexData vertex = { position,texcoord,normal };
                modelData.vertices.push_back(vertex);
                triangle[faceVertex] = { position,texcoord,normal };
            }

            modelData.vertices.push_back(triangle[2]);
            modelData.vertices.push_back(triangle[1]);
            modelData.vertices.push_back(triangle[0]);
        }
        else if (identifier == "mtllib") {
            //materialTemplateLibraryファイルの名前を取得
            std::string materialFilname;
            s >> materialFilname;
            //基本的にobjファイルと同一階層にmtlは存在させるから、ディレクトリ名とファイル名を渡す
            modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilname);
        }
    }

    return modelData;
}

MaterialData Model::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
    MaterialData materialData;//構築するマテリアルデータ
    std::string line;
    std::ifstream file(directoryPath + "/" + filename);
    assert(file.is_open());
    while (std::getline(file,line))
    {
        std::string identifier;
        std::istringstream s(line);
        s >> identifier;
        //identifierに応じた処理
        if (identifier == "map_Kd") {
            std::string textureFilname;
            s >> textureFilname;
            //連結してファイルパスにする
            materialData.textureFilePath = directoryPath + "/" + textureFilname;
        }
    }
    return materialData;
}

void Model::CreateVartexData() {
	vertexResource = directXCommon_->CreateBufferResource(directXCommon_->GetDevice().Get(), sizeof(VertexData) * modelData_.vertices.size());

	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();

	vertexBufferView.SizeInBytes = sizeof(VertexData) *(UINT) modelData_.vertices.size();

	vertexBufferView.StrideInBytes = sizeof(VertexData);

	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	std::memcpy(vertexData_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());
}

void Model::SetColor() {
	materialResource_ = DirectXCommon::CreateBufferResource(directXCommon_->GetDevice().Get(), sizeof(Material));

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&material_));
	material_->uvTransform = MakeIdentity4x4();
}

void Model::TransformMatrix() {
	wvpResource_ = DirectXCommon::CreateBufferResource(directXCommon_->GetDevice().Get(), sizeof(Transformmatrix));
	wvpResource_->Map(0, NULL, reinterpret_cast<void**>(&wvpData_));
	wvpData_->WVP = MakeIdentity4x4();
}

Node Model::ReadNode(aiNode* node) {
    Node result;
    
    aiMatrix4x4 aiLocalMatrix = node->mTransformation;
    aiLocalMatrix.Transpose();

    result.localMatrix.m[0][0] = aiLocalMatrix[0][0];

    result.name = node->mName.C_Str();
    result.children.resize(node->mNumChildren);

    for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex) {
        result.children[childIndex] = ReadNode(node->mChildren[childIndex]);
    }

    return result;
}