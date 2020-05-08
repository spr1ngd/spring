#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <map>
#include <vector>
#include <string>
#include "assetloader.h"
#include "mesh.h"

using namespace std;

namespace spring 
{
	class Quaternion;
	class GameObject;
	class Texture;
	class ModelLoader :public AssetLoader
	{
	private:
		static std::map<const char*, Mesh*> meshesMap;

		static void CacheMesh(const char* resName, Mesh* mesh);
		static void ReleaseMesh(const char* resName);
		static Mesh* GetMesh(const char* resName);

		Mesh* LoadMesh(const char* filePath);
		void processNode(aiNode* node, const aiScene* scene, Mesh& parentNode,bool isSubMesh);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture*> loadMaterialTextures(aiMaterial* mateiral, aiTextureType textureType, string typeName);

		string directory;
		ModelLoader();

		void parseNode(aiNode* node, const aiScene* scene , GameObject* parent);
		void decomposeTransformation(const aiMatrix4x4& matrix ,Vector3& position,Vector3& scale,Quaternion& rotation);

	public:
		static Mesh& LoadMeshFromFile(const char* meshFilePath);

		static GameObject* LoadGameObjectFromFile(const char* meshFilePath);
		static const char* GetReference(Mesh* mesh);
	};
}
