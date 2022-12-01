//
//  Model.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#pragma once
#ifndef Model_hpp
#define Model_hpp

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IMeshRenderer.hpp"


class Model : public IMeshRendeer
{
public:
    // model data
    std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    
    Model(std::string const &path, bool gamma = false);
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }
    
    // Ovverides
    void FillMeshBuffer(std::vector<Mesh> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
    void DrawStyle() override;
    
private:
    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;
    void LoadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    void SetVertexBoneDataToDefault(Vertex& vertex);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile1(const char* path, const std::string& directory, bool gamma = false);
    
};

#endif /* Model_hpp */
