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

	public:
		static Mesh& Load(const char* meshFilePath);
		static const char* GetReference(Mesh* mesh);
	};
}
