#include "modelloader.h"
#include "console.h"

using namespace spring;
using namespace std; 

ModelLoader::ModelLoader()
{

}

void ModelLoader::processNode(aiNode* node, const aiScene* scene) 
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh,scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) 
		processNode(node->mChildren[i], scene);
}

vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial*mateiral,aiTextureType textureType,string typeName) 
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mateiral->GetTextureCount(textureType); i++) 
	{
		aiString str;
		mateiral->GetTexture(textureType,i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < this->loadedTextures.size(); j++)
		{
			if (std::strcmp(this->loadedTextures[j].textureName, str.C_Str()) == 0) 
			{
				textures.push_back(this->loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (skip == false) 
		{
			Texture tex;
			tex.textureType = typeName.c_str();
			tex.textureName = str.C_Str();
			PRINT_LOG("[ModelLoader] : load texture : %s",tex.textureName);
			string filePath = directory + '/' + str.C_Str();
			tex.Load(filePath.c_str());
		}
	}
	return textures;
}

Mesh ModelLoader::processMesh( aiMesh*mesh,const aiScene*scene )
{
	// transfer aiMesh to spring::Mesh
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

#pragma region parse for model vertices

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		Vertex vertex;
		// vertex position
		if (mesh->HasPositions()) 
		{
			vertex.vertex.x = mesh->mVertices[i].x;
			vertex.vertex.y = mesh->mVertices[i].y;
			vertex.vertex.z = mesh->mVertices[i].z;
		}
		// vertex normal
		if (mesh->HasNormals())
		{
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
		}
		// vertex texcoord
		if (mesh->HasTextureCoords(0))
		{
			vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		// tangent and bitangent
		if (mesh->HasTangentsAndBitangents()) 
		{
			vertex.tangent.x = mesh->mTangents[i].x;
			vertex.tangent.y = mesh->mTangents[i].y;
			vertex.tangent.z = mesh->mTangents[i].z;

			vertex.bitangent.x = mesh->mBitangents[i].x;
			vertex.bitangent.y = mesh->mBitangents[i].y;
			vertex.bitangent.z = mesh->mBitangents[i].z;
		}
		// vertex color
		if (mesh->HasVertexColors(0)) 
		{
			unsigned char r = (unsigned char)mesh->mColors[i]->r;
			unsigned char g = (unsigned char)mesh->mColors[i]->g;
			unsigned char b = (unsigned char)mesh->mColors[i]->b;
			unsigned char a = (unsigned char)mesh->mColors[i]->a;
			Color color = Color(r,g,b,a);
			vertex.color = color;
		}
		vertices.push_back(vertex);
	}

#pragma endregion

#pragma region parse for model indices

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) 
		{
			indices.push_back(face.mIndices[j]);
		}
	}

#pragma endregion

#pragma region parse for model textures

	if (scene->HasMaterials())
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseTextures = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		vector<Texture> specularTexturess = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		vector<Texture> normalTextures = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		vector<Texture> heightTextures = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());
		textures.insert(textures.end(), specularTexturess.begin(), specularTexturess.end());
		textures.insert(textures.end(), normalTextures.begin(), normalTextures.end());
		textures.insert(textures.end(), heightTextures.begin(), heightTextures.end());
	}

#pragma endregion

	PRINT_LOG("[ModelLoader] : load mesh %s load textures %d ",mesh->mName.C_Str(),textures.size());
	return Mesh(vertices, indices, textures);
}

void ModelLoader::Load(const string filePath) 
{
	// todo : load model from file.
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
		PRINT_ERROR("load model failed.");
	directory = filePath.substr(0, filePath.find_last_of('/'));
	if( scene )
		processNode(scene->mRootNode, scene);
}