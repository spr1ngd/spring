#include "modelloader.h"
#include "console.h"
#include "misc.h"
#include "texture.h"
#include "material.h"
#include "meshrenderer.h"
#include "gameobject.h"

using namespace spring;
using namespace std; 

map<const char*, Mesh*> ModelLoader::meshesMap;

ModelLoader::ModelLoader()
{

}

const char* ModelLoader::GetReference(Mesh* mesh) 
{
	for (std::map<const char*, Mesh*>::iterator item = meshesMap.begin(); item != meshesMap.end(); item++) 
	{
		Mesh* cache = item->second;
		if (cache == mesh)
		{
			PRINT_ERROR("======> get reference successfully = %s", item->first);
			return item->first;
		}
	}
	return "";
}

GameObject* ModelLoader::LoadGameObjectFromFile(const char* meshFileName,std::vector<Material*>& mats)
{
	GameObject* gameobject = new GameObject(meshFileName);
	const char* prefix = "res/model/";
	char* filePath = misc::strcat(prefix, meshFileName);

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		PRINT_ERROR("load model failed.");
	if (scene == nullptr)
		return nullptr;

	int childIndex = 0;
	ModelLoader loader;
	loader.processMaterial(scene, mats);
	loader.parseNode(scene->mRootNode, scene, gameobject, mats);
	delete[] filePath;
	return gameobject;
}

Mesh& ModelLoader::LoadMeshFromFile(const char* meshFilePath)
{
	Mesh* mesh = GetMesh(meshFilePath);
	if (nullptr != mesh)
		return *mesh;
	const char* prefix = "res/model/";
	char* filePath = misc::strcat(prefix, meshFilePath);
	ModelLoader loader;
	Mesh* meshObj = loader.LoadMesh(filePath);
	CacheMesh(meshFilePath, meshObj);
	delete[] filePath;
	return *meshObj;
}

Mesh* ModelLoader::LoadMesh(const char* filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
		PRINT_ERROR("load model failed.");
	if (scene == nullptr)
		return nullptr;
	string path = filePath;
	this->directory = path.substr(0, path.find_last_of('/'));
	Mesh* mesh = new Mesh();
	processNode(scene->mRootNode, scene, *mesh,false);
	return mesh;
}
void ModelLoader::parseNode(aiNode* node, const aiScene* scene, GameObject* parent, std::vector<Material*>& mats)
{
	GameObject* nodeGameObject = nullptr;
	if (node->mNumMeshes > 0)
	{		
		Mesh* nodeMesh = new Mesh();
		unsigned int materialIndex = scene->mMeshes[node->mMeshes[0]]->mMaterialIndex;
		for (unsigned int meshIndex = 0; meshIndex < node->mNumMeshes; meshIndex++)
		{
			unsigned int index = node->mMeshes[meshIndex];
			aiMesh* mesh = scene->mMeshes[index];
			if (mesh->mMaterialIndex != materialIndex)
				PRINT_ERROR("can not combine two mesh with different materials.");
			Mesh* subMesh = processMesh(mesh, scene);
			nodeMesh->Combine(*subMesh);
		}
		nodeGameObject = new GameObject();
		auto name = misc::strcat(node->mName.C_Str(), "");
		nodeGameObject->name = name;
		nodeGameObject->SetParent(parent);
		Vector3 scale, position;
		Quaternion rotation;
		this->decomposeTransformation(node->mTransformation, position, scale, rotation);
		nodeGameObject->transform->SetPosition(position);
		nodeGameObject->transform->SetLocalScale(scale);
		nodeGameObject->transform->SetLocalRotation(rotation);
		MeshRenderer* childMeshRenderer = nodeGameObject->AddNode<MeshRenderer>();
		childMeshRenderer->mesh = nodeMesh;
		Material* material = nullptr;

		const char* matName = scene->mMaterials[materialIndex]->GetName().C_Str();
		for (Material* mat : mats)
		{
			if (strcmp(mat->name, matName) == 0)
			{
				material = mat;
				break;
			}
		}
		if (nullptr == material)
			PRINT_ERROR("parse material failed.");
		childMeshRenderer->material = material;
	}

	for (unsigned int childIndex = 0; childIndex < node->mNumChildren; childIndex++)
	{
		aiNode* childNode = node->mChildren[childIndex];
		parseNode(childNode, scene, node->mNumMeshes > 0 ? nodeGameObject : parent ,mats);
	}
}

void ModelLoader::decomposeTransformation(const aiMatrix4x4& matrix, Vector3& position, Vector3& scale, Quaternion& rotation)
{ 
	aiVector3D aiScaling, aiPosition;
	aiQuaternion aiRotation;
	matrix.Decompose(aiScaling, aiRotation, aiPosition);
	position.x = aiPosition.x; position.y = aiPosition.y ; position.z = aiPosition.z ;
	scale.x = aiScaling.x; scale.y = aiScaling.y; scale.z = aiScaling.z;
	rotation.x = aiRotation.x; rotation.y = aiRotation.y; rotation.z = aiRotation.z; rotation.w = aiRotation.w;
} 

void ModelLoader::processNode(aiNode* node, const aiScene* scene, Mesh& parentNode ,bool isSubMesh)
{
	if (node->mNumMeshes > 1)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++) 
		{
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		}

		// todo : we should create a new empty root for those kind of models
		return;
	}
	for (unsigned int i = 0; i < node->mNumMeshes; i++) 
	{
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		std::vector<Texture*> texs;
		Mesh* mesh = processMesh(aimesh,scene);
		if (isSubMesh)
			parentNode.SetSubMesh(mesh);
		else 
			parentNode = *mesh;
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) 
		processNode(node->mChildren[i], scene, parentNode, parentNode.vertices.size() != 0);
}
Mesh* ModelLoader::processMesh( aiMesh*mesh,const aiScene*scene )
{ 
	vector<Vertex> vertices;
	vector<unsigned int> indices; 

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
			unsigned char r = (unsigned char)mesh->mColors[0]->r;
			unsigned char g = (unsigned char)mesh->mColors[0]->g;
			unsigned char b = (unsigned char)mesh->mColors[0]->b;
			unsigned char a = (unsigned char)mesh->mColors[0]->a;
			Color color = Color(r,g,b,a);
			vertex.color = color;
		}
		vertices.push_back(vertex);
	} 

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) 
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(vertices, indices);
}

void ModelLoader::processMaterial(const aiScene* scene, std::vector<Material*>& mats)
{
	if (!scene->HasMaterials())
		return;
	for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++) 
	{
		aiMaterial* material = scene->mMaterials[materialIndex];
		// load material properties 

		int twoSide = 0;
		material->Get(AI_MATKEY_TWOSIDED, twoSide);

		float isOpacity = 1.0f;
		material->Get(AI_MATKEY_OPACITY, isOpacity);

		float shininess = 0.0f;
		material->Get(AI_MATKEY_SHININESS, shininess);

		aiColor4D diffuseColor(0.0f,0.0f,0.0f,1.0f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);

		aiColor4D ambientColor(0.0f, 0.0f, 0.0f, 1.0f);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);

		aiColor4D emissionColor(0.0f, 0.0f, 0.0f, 1.0f);
		material->Get(AI_MATKEY_COLOR_EMISSIVE, emissionColor);

		aiColor4D specularColor(0.0f, 0.0f, 0.0f, 1.0f);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);

		// load textures
		Texture* albedoTex = processTexture(material, aiTextureType_DIFFUSE, PBR_TEXTURE_ALBEDO);
		Texture* specularTex = processTexture(material, aiTextureType_SPECULAR, PBR_TEXTURE_SPECULAR);
		Texture* normalTex = processTexture(material, aiTextureType_NORMALS, PBR_TEXTURE_NORMAL);
		Texture* heightTex = processTexture(material, aiTextureType_HEIGHT, PBR_TEXTURE_HEIGHT);
		Texture* ambientTex = processTexture(material, aiTextureType_AMBIENT, PBR_TEXTURE_AMBIENT);

		Material* mat = new Material(Shader::Load("pbs/pbs.vs", "pbs/pbs(ibl).fs"));
		const char* matName = material->GetName().C_Str();
		char* key = new char[strlen(matName)];
		strcpy_s(key, strlen(matName) + 1, matName);
		mat->name = key;

		mat->SetFloat(PBR_FLOAT_ROUGHNESS, shininess);

		mat->SetColor(PBR_COLOR_ALBEDO, Colorf(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
		mat->SetColor(PBR_COLOR_EMISSION, Colorf(emissionColor.r, emissionColor.g, emissionColor.b, emissionColor.a));
		mat->SetColor(PBR_COLOR_SPECULAR, Colorf(specularColor.r, specularColor.g, specularColor.b, specularColor.a));
		mat->SetColor(PBR_COLOR_AMBIENTOCCLUSION, Colorf(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));

		mat->SetTexture(PBR_TEXTURE_ALBEDO, albedoTex);
		mat->SetTexture(PBR_TEXTURE_AMBIENT, ambientTex);
		mat->SetTexture(PBR_TEXTURE_NORMAL, normalTex);
		mat->SetTexture(PBR_TEXTURE_SPECULAR, specularTex);
		mat->SetTexture(PBR_TEXTURE_HEIGHT, heightTex);

		mats.push_back(mat);
	}
}

Texture* ModelLoader::processTexture(aiMaterial* material, aiTextureType textureType, string typeName)
{ 
	unsigned int textureCount = material->GetTextureCount(textureType);
	if (textureCount <= 0)
		return nullptr;
	if (textureCount > 1)
		PRINT_ERROR("Contain the same textures on one material.");
	aiString str;
	material->GetTexture(textureType, 0, &str);
	string filePath = directory + '/' + str.C_Str();
	Texture* tex = TextureLoader::Load(filePath.c_str());
	tex->textureType = typeName.c_str();
	tex->textureName = str.C_Str();
	return tex;
}

void ModelLoader::CacheMesh(const char* resName, Mesh* mesh) 
{
	meshesMap.insert(std::pair<const char*,Mesh*>(resName, mesh));
}
void ModelLoader::ReleaseMesh(const char* resName) 
{
	std::map<const char*,Mesh*>::iterator pair = meshesMap.find(resName);
	if (pair != meshesMap.end())
	{
		delete pair->second;
		meshesMap.erase(pair);
	}
}
Mesh* ModelLoader::GetMesh(const char* resName) 
{
	std::map<const char*, Mesh*>::iterator pair = meshesMap.find(resName);
	if (pair != meshesMap.end())
		return pair->second;
	return nullptr;
}