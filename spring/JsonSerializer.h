#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <typeinfo>
#include "springengine.h"
#include "serializer.h"

using namespace rapidjson;

namespace spring 
{
	class JsonSerializer
	{
	private:
		Document* document;
		Document::AllocatorType* allocator;

		template<class T>
		Value& serialize(T* t) 
		{
			Value* value = new Value(kObjectType);
			const char* typeName = typeid(T).name();
			if (typeName == typeid(Scene).name())
			{
				Scene* scene = (Scene*)t;

				Value strValue = Value(kStringType);
				strValue.SetString(scene->name,strlen(scene->name));
				value->AddMember("scene_id", strValue, *this->allocator);
				for (auto item = scene->nodes.begin(); item != scene->nodes.end(); item++)
				{
					Node* node = item->second;
					Value& nodeValue = this->serialize<Node>(node);
					Value strValue = Value(kStringType);
					strValue.SetString(node->name,strlen(node->name));
					value->AddMember(strValue, nodeValue, *this->allocator);
				}
			}
			else if (typeName == typeid(Node).name())
			{
				Node* node = (Node*)t;

				Value nameValue = Value(kStringType);
				nameValue.SetString(node->name,strlen(node->name));
				value->AddMember("_name", nameValue, *this->allocator);
				value->AddMember("_visible", node->visible, *this->allocator);
				value->AddMember("_layer", node->layer, *this->allocator);

				Value& transform = this->serialize<Transform>(node->transform);
				value->AddMember("transform",transform,*this->allocator);

				Value childrenValue = Value(kArrayType);
				for (auto child : node->children)
				{
					Value& childNode = this->serialize<Node>(child);
					childrenValue.PushBack(childNode, *this->allocator);
				}
				value->AddMember("children", childrenValue, *this->allocator);
			}
			else if (typeName == typeid(Transform).name())
			{
				Transform* transform = (Transform*)t;
				Value& position = this->serialize<Vector3>(&transform->position);
				value->AddMember("position", position, *this->allocator);
				Value& eulerangle = this->serialize<Vector3>(&transform->eulerangle);
				value->AddMember("eulerangle", eulerangle, *this->allocator);
				Value& scale = this->serialize<Vector3>(&transform->scale);
				value->AddMember("scale", scale, *this->allocator);
				// this->serialize<Quaternion>(&transform->rotation);
			}
			else if (typeName == typeid(Quaternion).name())
			{
				Console::Log("serialize quaternion.");
				Quaternion* quaternion = (Quaternion*)t;

			}
			else if (typeName == typeid(Vector2).name())
			{

			}
			else if (typeName == typeid(Vector3).name())
			{
				Vector3* vec3 = (Vector3*)t;
				value = this->serializeVector3(*vec3, *this->allocator);
			}
			else if (typeName == typeid(Color).name())
			{

			}
			else if (typeName == typeid(Colorf).name())
			{

			}
			else
			{
				Console::ErrorFormat("invalid type %s", typeName);
			}
			return *value;
		}

	public:
		JsonSerializer() 
		{
			this->document = new Document();
			this->document->SetObject();
			this->allocator = &document->GetAllocator();
		}

		template<class T>
		void Serialize(T* t) 
		{
			Value& value = this->serialize(t);
			this->document->AddMember("scenes",value,*this->allocator);
		}
		
		template<class T>
		T* Deserialize() 
		{

		}

		void WriteTo(const char* filePath) 
		{
			StringBuffer stringBuffer;
			Writer<StringBuffer> writer(stringBuffer);
			this->document->Accept(writer);
			const char* buffer = stringBuffer.GetString();
			FileIO::WriteFile(filePath, buffer);
		}
		void ReadFrom(const char* filePath);

		// vector3 to json 
		Value* serializeVector3(Vector3 vec3, Document::AllocatorType& alloactor);
		// json to vector3
		Vector3 deserializeVector3(Value::MemberIterator vec3Member);
	};
}