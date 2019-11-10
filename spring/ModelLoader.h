#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assetloader.h"
#include <string>
#include "mesh.h"

#pragma comment (lib,"assimp-vc142-mt.lib")

using namespace std;

namespace spring 
{
	class ModelLoader :public AssetLoader
	{
	private:
		string directory;
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void processNode(aiNode* node, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mateiral, aiTextureType textureType, string typeName);
	public:
		vector<Texture> loadedTextures;
		vector<Mesh> meshes;
		ModelLoader();
		void Load(const std::string filePath);

	public:
		// static void Load();
	};
}
