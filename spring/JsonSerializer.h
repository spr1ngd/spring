#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <typeinfo>
#include <vector>
#include "springengine.h"
#include "serializer.h"
#include "modelloader.h"


using namespace rapidjson;

namespace spring 
{
	class JsonSerializer
	{
	private:
		Document* document;
		std::vector<Value*> values;

		template<class T>
		Value& serialize(T& t) 
		{
			Value* value = nullptr;
			const char* typeName = typeid(T).name();
			if (typeName == typeid(Scene).name())
				value = toJson((Scene&)t);
			else if (typeName == typeid(Node).name())
				value = toJson((Node&)t);
			else if (typeName == typeid(Transform).name())
				value = toJson((Transform&)t);
			else if (typeName == typeid(Vector2).name())
				value = toJson((Vector2&)t);
			else if (typeName == typeid(Vector3).name())
				value = toJson((Vector3&)t);
			else if (typeName == typeid(Vector4).name())
				value = toJson((Vector4&)t);
			else if (typeName == typeid(Color).name())
				value = toJson((Color&)t);
			else if (typeName == typeid(Colorf).name())
				value = toJson((Colorf&)t);
			else
				PRINT_ERROR("invalid type %s", typeName);
			this->values.push_back(value);
			return *value;
		}

	public:
		JsonSerializer()
		{
			this->document = new Document();
			this->document->SetObject(); 
		}
		~JsonSerializer() 
		{
			for (auto item = this->values.begin(); item != this->values.end(); item++)
			{
				Value* value = *item;
				delete value;
			}
			this->values.clear();
			delete this->document;
		}

		template<class T>
		void Serialize(const T& t) 
		{
			Value& value = this->serialize(t);
			this->document->AddMember("scenes",value,this->document->GetAllocator());
		}
		void WriteTo(const char* filePath) 
		{
			StringBuffer stringBuffer;
			Writer<StringBuffer> writer(stringBuffer);
			this->document->Accept(writer);
			const char* buffer = stringBuffer.GetString();
			// TODO: FileIO::WriteFile(filePath, buffer);
		}
		
		template<class T>
		T* Deserialize() 
		{
			auto scenesMember = this->document->FindMember("scenes");
			Scene* scene = toScene(scenesMember->value);
			return scene;
		}
		void ReadFrom(const char* filePath) 
		{
			char* buffer = nullptr;// TODO: = FileIO::ReadFile(filePath);
			this->document->Parse(buffer);
			if (this->document->HasParseError()) 
			{
				auto errorCode = this->document->GetParseError();
				PRINT_ERROR("Parsing scene data error , error code : %d",errorCode);
				return;
			}
		}

		Value* toJson(Scene& scene);
		Value* toJson(Behaviour& behaviour);
		Value* toJson(Node& node);
		Value* toJson(Transform& transform);
		Value* toJson(MeshRenderer& meshrenderer);
		Value* toJson(Mesh& mesh);
		Value* toJson(Material& material);
		Value* toJson(Shader& shader);
		Value* toJson(Vector2& vec2);
		Value* toJson(Vector3& vec3);
		Value* toJson(Vector4& vec4);
		Value* toJson(Color& color);
		Value* toJson(Colorf& colorf);
		
		Scene* toScene(Value& value);
		Node* toNode(Value& value);
		Behaviour* toBehaviour(Value& value);
		MeshRenderer* toMeshRenderer(Value& value);
		Transform* toTransform(Value& value);
		Material* toMaterial(Value& value);
		Shader* toShader(Value& value);
		Mesh* toMesh(Value& value);
		Vector2 toVector2(Value& value);
		Vector3 toVector3(Value& value);
		Vector4 toVector4(Value& value);
		Color toColor(Value& value);
		Colorf toColorf(Value& value);
	};
}