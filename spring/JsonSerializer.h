#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <typeinfo>
#include <vector>
#include "springengine.h"
#include "serializer.h"

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
		void ReadFrom(const char* filePath) 
		{

		}

		Value* toJson(Scene& scene) 
		{
			Value* value = new Value(kObjectType);
			Value strValue = Value(kStringType);
			strValue.SetString(scene.name, strlen(scene.name));
			value->AddMember("scene_id", strValue, this->document->GetAllocator());
			for (auto item = scene.nodes.begin(); item != scene.nodes.end(); item++)
			{
				Node* node = *item;
				Value* nodeValue = toJson(*node);
				Value strValue = Value(kStringType);
				strValue.SetString(node->name, strlen(node->name));
				value->AddMember(strValue, *nodeValue, this->document->GetAllocator());
			}
			return value;
		}
		Value* toJson(Node& node) 
		{
			Value* value = new Value(kObjectType);

			// basic information
			Value nameValue = Value(kStringType);
			nameValue.SetString(node.name, strlen(node.name));
			value->AddMember("_name", nameValue, this->document->GetAllocator());
			value->AddMember("_visible", node.visible, this->document->GetAllocator());
			value->AddMember("_layer", node.layer, this->document->GetAllocator());

			// transform information
			Value* transform = toJson(*node.transform);
			value->AddMember("transform", *transform, this->document->GetAllocator());

			// additional nodes
			Value nodesValue = Value(kArrayType);
			for (auto com : node.nodes) 
			{
				Value* componentValue = toJson(*com);
				nodesValue.PushBack(*componentValue, this->document->GetAllocator());
			}
			value->AddMember("nodes",nodesValue,this->document->GetAllocator());

			// child nodes
			Value childrenValue = Value(kArrayType);
			for (auto child : node.children)
			{
				Value* childNode = toJson(*child);
				childrenValue.PushBack(*childNode, this->document->GetAllocator());
			}
			value->AddMember("children", childrenValue, this->document->GetAllocator());

			// transfer to mesh renderer.
			try
			{
				MeshRenderer& meshrenderer = dynamic_cast<MeshRenderer&>(node);
				PRINT_LOG("[JsonSerializer] : transfer node to mesh renderer.");
				Value* meshRendererValue = toJson(meshrenderer);
				value->AddMember("_meshrenderer",*meshRendererValue,this->document->GetAllocator());
			}
			catch (bad_cast)
			{
				PRINT_ERROR("[JsonSerializer] : can not cast node to mesh renderer.");
			}
			return value;
		}
		Value* toJson(Transform& transform) 
		{
			Value* value = new Value(kObjectType);
			Value* position = toJson(transform.position);
			value->AddMember("position", *position, this->document->GetAllocator());
			Value* eulerangle = toJson(transform.eulerangle);
			value->AddMember("eulerangle", *eulerangle, this->document->GetAllocator());
			Value* scale = toJson(transform.scale);
			value->AddMember("scale", *scale, this->document->GetAllocator());
			return value;
		}
		Value* toJson(MeshRenderer& meshrenderer) 
		{
			Value* value = new Value(kObjectType);
			// 导出mateiral参数
			Material* material = meshrenderer.material;
			Value* materialParamtersValue = toJson(*material);
			value->AddMember("_parameters", *materialParamtersValue, this->document->GetAllocator());
			// 导出material.shader引用/参数
			Shader* shader = material->shader;
			Value* shaderParameters = toJson(*shader);
			value->AddMember("_shader",*shaderParameters,this->document->GetAllocator());
			// 导出mesh引用
			return value;
		}
		Value* toJson(Material& material) 
		{
			Value* value = new Value(kObjectType);
			Document::AllocatorType& allocator = this->document->GetAllocator();
			// const char* name;
			// Value nameValue = Value(kStringType);
			// nameValue.SetString(material.name,allocator);
			// value->AddMember("_name", nameValue,allocator);
			value->AddMember("_rendermode", material.renderMode, allocator);
			value->AddMember("_enable_gpu_instanceing",material.enableGPUInstanced,allocator);
			value->AddMember("_enable_alphatest",material.alphaTest,allocator);
			value->AddMember("_alphafunc",material.alphaFunc,allocator);
			value->AddMember("_alpharef",material.alphaRef,allocator);
			value->AddMember("_enable_blend",material.blend,allocator);
			value->AddMember("_src_factor", material.srcFactor, allocator);
			value->AddMember("_dst_factor",material.dstFactor,allocator);
			value->AddMember("_enable_depthtest", material.depthTest, allocator);
			value->AddMember("_enable_depthwrite",material.depthWrite,allocator);
			value->AddMember("_depthfunc",material.depthFunc,allocator);
			value->AddMember("_enable_stecialtest", material.stencilTest, allocator);
			value->AddMember("_enbale_cullface", material.cullface, allocator);
			value->AddMember("_cullfacefunc", material.cullfaceFunc, allocator);
			return value;
		}
		Value* toJson(Shader& shader)
		{
			Document::AllocatorType& allocator = this->document->GetAllocator();
			Value* value = new Value(kObjectType);
			// vertex shader
			Value vertexShaderValue = Value(kStringType);
			vertexShaderValue.SetString(shader.vertexShaderName, allocator);
			value->AddMember("_vs",vertexShaderValue, allocator);
			// fragment shader
			Value fragmentShaderValue = Value(kStringType);
			fragmentShaderValue.SetString(shader.fragmentShaderName, allocator);
			value->AddMember("_fs",fragmentShaderValue, allocator);
			// uniform values
			Value parameters = Value(kObjectType);
			for (auto pair = shader.ints.begin(); pair != shader.ints.end(); pair++) 
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first),allocator);
				parameters.AddMember(keyValue,pair->second, allocator);
			}
			for (auto pair = shader.bools.begin(); pair != shader.bools.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				parameters.AddMember(keyValue, pair->second, allocator);
			}
			for (auto pair = shader.floats.begin(); pair != shader.floats.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				parameters.AddMember(keyValue, pair->second, allocator);
			}
			for (auto pair = shader.vec2Map.begin(); pair != shader.vec2Map.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				Value* vec2 = toJson(pair->second);
				parameters.AddMember(keyValue, *vec2, allocator);
			}
			for (auto pair = shader.vec3Map.begin(); pair != shader.vec3Map.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				Value* vec3 = toJson(pair->second);
				parameters.AddMember(keyValue, *vec3, allocator);
			}
			for (auto pair = shader.vec4Map.begin(); pair != shader.vec4Map.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				Value* vec4 = toJson(pair->second);
				parameters.AddMember(keyValue, *vec4, allocator);
			}
			for (auto pair = shader.colors.begin(); pair != shader.colors.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				Value* vec4 = toJson(pair->second);
				parameters.AddMember(keyValue, *vec4, allocator);
			}
			for (auto pair = shader.textures.begin(); pair != shader.textures.end(); pair++)
			{
				Value keyValue = Value(kStringType);
				keyValue.SetString(shader.getUniformName(pair->first), allocator);
				parameters.AddMember(keyValue, pair->second.texture, allocator);
			}
			value->AddMember("_parameters",parameters,allocator);
			return value;
		}
		Value* toJson(Vector3& vec3) 
		{
			Value* value = new Value(kObjectType);
			value->AddMember("x", vec3.x, this->document->GetAllocator());
			value->AddMember("y", vec3.y, this->document->GetAllocator());
			value->AddMember("z", vec3.z, this->document->GetAllocator());
			return value;
		}
		Value* toJson(Vector4& vec4)
		{
			Value* value = new Value(kObjectType);
			value->AddMember("x", vec4.x, this->document->GetAllocator());
			value->AddMember("y", vec4.y, this->document->GetAllocator());
			value->AddMember("z", vec4.z, this->document->GetAllocator());
			value->AddMember("w", vec4.w, this->document->GetAllocator());
			return value;
		}
		Value* toJson(Vector2& vec2) 
		{
			Value* value = new Value(kObjectType);
			value->AddMember("x", vec2.x, this->document->GetAllocator());
			value->AddMember("y", vec2.y, this->document->GetAllocator());
			return value;
		}
		Value* toJson(Color& color) 
		{
			Value* value = new Value(kObjectType);
			value->AddMember("r", color.r, this->document->GetAllocator());
			value->AddMember("g", color.g, this->document->GetAllocator());
			value->AddMember("b", color.b, this->document->GetAllocator());
			value->AddMember("a", color.a, this->document->GetAllocator());
			return value;
		}
		Value* toJson(Colorf& colorf) 
		{
			Value* value = new Value(kObjectType);
			value->AddMember("r", colorf.r, this->document->GetAllocator());
			value->AddMember("g", colorf.g, this->document->GetAllocator());
			value->AddMember("b", colorf.b, this->document->GetAllocator());
			value->AddMember("a", colorf.a, this->document->GetAllocator());
			return value;
		}
		

		Vector3 toObject(Value& value) 
		{
			return Vector3::zero;
		}
	};
}