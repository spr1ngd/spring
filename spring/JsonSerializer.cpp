#include "jsonserializer.h"
#include "scene.h"

#include "gameapp.h"

using namespace spring;

Value* JsonSerializer::toJson(Scene& scene)
{
	Value* value = new Value(kObjectType);
	Value strValue = Value(kStringType);
	strValue.SetString(scene.name, strlen(scene.name));
	value->AddMember("scene_id", strValue, this->document->GetAllocator());

	Value hierarchyValue = Value(kObjectType);
	for (auto item = scene.nodes.begin(); item != scene.nodes.end(); item++)
	{
		Node* node = *item;
		// only nodes that are marked as static can be exported ==> static meaning is created in editor scene.
		if( node->flags != NodeFlags::Static )
			continue;

		// try to cast to behaviour type.
		Value strValue = Value(kStringType);
		strValue.SetString(node->name, strlen(node->name));
		try
		{
			Behaviour* behaviour = dynamic_cast<Behaviour*>(node);
			Value* hehaviourValue = toJson(*behaviour);
			hierarchyValue.AddMember(strValue, *hehaviourValue, this->document->GetAllocator());
		}
		catch (bad_cast)
		{
			Value* nodeValue = toJson(*node);
			hierarchyValue.AddMember(strValue, *nodeValue, this->document->GetAllocator());
		}
	}
	value->AddMember("hierarchy", hierarchyValue, this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Behaviour& behaviour) 
{
	Value* value = toJson((Node&)behaviour);
	value->AddMember("_type","behaviour",this->document->GetAllocator());
	const char* scriptName = nullptr;
	try 
	{
		auto gameApp = dynamic_cast<GameApp&>(behaviour);
		scriptName = "class::spring::GameApp";
	}
	catch (bad_cast) 
	{

	}
	Value scriptNameValue = Value(kStringType);
	scriptNameValue.SetString(scriptName,strlen(scriptName));
	value->AddMember("_behaviourType",scriptNameValue,this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Node& node)
{
	Value* value = new Value(kObjectType);

	// basic information
	Value nameValue = Value(kStringType);
	nameValue.SetString(node.name, strlen(node.name));
	value->AddMember("_name", nameValue, this->document->GetAllocator());
	// todo : move visible property from node to gameobject
	// value->AddMember("_visible", node.visible, this->document->GetAllocator());
	value->AddMember("_layer", node.gameobject->layer, this->document->GetAllocator());

	// transform information
	Value* transform = toJson(*node.transform);
	value->AddMember("transform", *transform, this->document->GetAllocator());

	// additional nodes
	// todo : replaced by gameobject's nodes
	// Value nodesValue = Value(kObjectType);
	// for (auto com : node.nodes)
	// {
	// 	Value* componentValue = toJson(*com);
	// 	Value comName = Value(kStringType);
	// 	comName.SetString(node.name, strlen(com->name));
	// 	nodesValue.AddMember(comName, *componentValue, this->document->GetAllocator());
	// }
	// value->AddMember("nodes", nodesValue, this->document->GetAllocator());

	// child nodes
	// todo : replaced by gameobject's children
	// Value childrenValue = Value(kObjectType);
	// for (auto child : node.children)
	// {
	// 	Value* childNode = toJson(*child);
	// 	Value childName = Value(kStringType);
	// 	childName.SetString(child->name, strlen(child->name));
	// 	childrenValue.AddMember(childName, *childNode, this->document->GetAllocator());
	// }
	// value->AddMember("children", childrenValue, this->document->GetAllocator());

	// transfer to mesh renderer.
	try
	{
		MeshRenderer& meshrenderer = dynamic_cast<MeshRenderer&>(node);
		PRINT_LOG("[JsonSerializer] : transfer node to mesh renderer.");
		Value* meshRendererValue = toJson(meshrenderer);
		value->AddMember("_meshrenderer", *meshRendererValue, this->document->GetAllocator());
	}
	catch (bad_cast)
	{
		PRINT_ERROR("[JsonSerializer] : can not cast node to mesh renderer.");
	}
	return value;
}
Value* JsonSerializer::toJson(Transform& transform)
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
Value* JsonSerializer::toJson(MeshRenderer& meshrenderer)
{
	Value* value = new Value(kObjectType);
	// 导出mateiral参数
	Material* material = meshrenderer.material;
	Value* materialParamtersValue = toJson(*material);
	value->AddMember("_parameters", *materialParamtersValue, this->document->GetAllocator());
	// 导出material.shader引用/参数
	Shader* shader = material->shader;
	Value* shaderParameters = toJson(*shader);
	value->AddMember("_shader", *shaderParameters, this->document->GetAllocator());
	// 导出mesh引用
	Mesh* mesh = meshrenderer.mesh;
	if (nullptr != mesh)
	{
		Value* meshParamters = toJson(*mesh);
		value->AddMember("_mesh", *meshParamters, this->document->GetAllocator());
	}
	return value;
}
Value* JsonSerializer::toJson(Mesh& mesh)
{
	Document::AllocatorType& allocator = this->document->GetAllocator();
	Value* value = new Value(kObjectType);
	// model resource path.
	const char* reference = ModelLoader::GetReference(&mesh);

	Value resValue = Value(kStringType);
	resValue.SetString(reference, strlen(reference));
	value->AddMember("_res", resValue, allocator);
	value->AddMember("_draw_type", mesh.drawType, allocator);
	value->AddMember("_mesh_mode", mesh.mode, allocator);
	return value;
}
Value* JsonSerializer::toJson(Material& material)
{
	Value* value = new Value(kObjectType);
	Document::AllocatorType& allocator = this->document->GetAllocator();
	// const char* name;
	// Value nameValue = Value(kStringType);
	// nameValue.SetString(material.name,allocator);
	// value->AddMember("_name", nameValue,allocator);
	value->AddMember("_rendermode", material.renderMode, allocator);
	value->AddMember("_enable_gpu_instanceing", material.enableGPUInstanced, allocator);
	value->AddMember("_enable_alphatest", material.alphaTest, allocator);
	value->AddMember("_alphafunc", material.alphaFunc, allocator);
	value->AddMember("_alpharef", material.alphaRef, allocator);
	value->AddMember("_enable_blend", material.blend, allocator);
	value->AddMember("_src_factor", material.srcFactor, allocator);
	value->AddMember("_dst_factor", material.dstFactor, allocator);
	value->AddMember("_enable_depthtest", material.depthTest, allocator);
	value->AddMember("_enable_depthwrite", material.depthWrite, allocator);
	value->AddMember("_depthfunc", material.depthFunc, allocator);
	value->AddMember("_enable_stecialtest", material.stencilTest, allocator);
	value->AddMember("_enbale_cullface", material.cullface, allocator);
	value->AddMember("_cullfacefunc", material.cullfaceFunc, allocator);
	return value;
}
Value* JsonSerializer::toJson(Shader& shader)
{
	Document::AllocatorType& allocator = this->document->GetAllocator();
	Value* value = new Value(kObjectType);
	// vertex shader
	Value vertexShaderValue = Value(kStringType);
	vertexShaderValue.SetString(shader.vertexShaderName, allocator);
	value->AddMember("_vs", vertexShaderValue, allocator);
	// fragment shader
	Value fragmentShaderValue = Value(kStringType);
	fragmentShaderValue.SetString(shader.fragmentShaderName, allocator);
	value->AddMember("_fs", fragmentShaderValue, allocator);
	// uniform values
	Value parameters = Value(kObjectType);
	for (auto pair = shader.ints.begin(); pair != shader.ints.end(); pair++)
	{
		Value keyValue = Value(kStringType);
		keyValue.SetString(shader.getUniformName(pair->first), allocator);
		parameters.AddMember(keyValue, pair->second, allocator);
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
	value->AddMember("_parameters", parameters, allocator);
	return value;
}
Value* JsonSerializer::toJson(Vector3& vec3)
{
	Value* value = new Value(kObjectType);
	value->AddMember("_dataType", "vector3",this->document->GetAllocator());
	value->AddMember("x", vec3.x, this->document->GetAllocator());
	value->AddMember("y", vec3.y, this->document->GetAllocator());
	value->AddMember("z", vec3.z, this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Vector4& vec4)
{
	Value* value = new Value(kObjectType);
	value->AddMember("_dataType", "vector4", this->document->GetAllocator());
	value->AddMember("x", vec4.x, this->document->GetAllocator());
	value->AddMember("y", vec4.y, this->document->GetAllocator());
	value->AddMember("z", vec4.z, this->document->GetAllocator());
	value->AddMember("w", vec4.w, this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Vector2& vec2)
{
	Value* value = new Value(kObjectType);
	value->AddMember("_dataType", "vector2", this->document->GetAllocator());
	value->AddMember("x", vec2.x, this->document->GetAllocator());
	value->AddMember("y", vec2.y, this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Color& color)
{
	Value* value = new Value(kObjectType);
	value->AddMember("_dataType", "color", this->document->GetAllocator());
	value->AddMember("r", color.r, this->document->GetAllocator());
	value->AddMember("g", color.g, this->document->GetAllocator());
	value->AddMember("b", color.b, this->document->GetAllocator());
	value->AddMember("a", color.a, this->document->GetAllocator());
	return value;
}
Value* JsonSerializer::toJson(Colorf& colorf)
{
	Value* value = new Value(kObjectType);
	value->AddMember("_dataType", "colorf", this->document->GetAllocator());
	value->AddMember("r", colorf.r, this->document->GetAllocator());
	value->AddMember("g", colorf.g, this->document->GetAllocator());
	value->AddMember("b", colorf.b, this->document->GetAllocator());
	value->AddMember("a", colorf.a, this->document->GetAllocator());
	return value;
}

Scene* JsonSerializer::toScene(Value& value)
{
	Value::MemberIterator  sceneIdMemeber = value.FindMember("scene_id");
	const char* sceneName = sceneIdMemeber->value.GetString();
	Scene* scene = new Scene(sceneName);
	Scene::current = scene;

	Value::MemberIterator hierarchyMember = value.FindMember("hierarchy");
	for (auto member = hierarchyMember->value.MemberBegin(); member != hierarchyMember->value.MemberEnd(); member++)
	{
		Node* node = toNode(member->value);
		if (nullptr == node)
			continue;
	}
	return scene;
}
Node* JsonSerializer::toNode(Value& value)
{
	Node* node = nullptr;
	if (value.HasMember("_type"))
	{
		auto nodeType = value.FindMember("_type")->value.GetString();
		if (strcmp(nodeType,"behaviour") == 0) 
		{
			Behaviour* behaviour = toBehaviour(value);
			node = dynamic_cast<Node*>(behaviour);
		}
		else if (strcmp(nodeType,"meshRenderer") == 0)
		{
			auto meshrendererMember = value.FindMember("_meshrenderer");
			MeshRenderer* meshrenderer = toMeshRenderer(meshrendererMember->value);
			node = dynamic_cast<Node*>(meshrenderer);
		}
		else 
		{
			PRINT_ERROR("does not support to deserialize type=[%s].",nodeType);
		}
	}
	else
	{
		node = new Node();
	}
	auto nameMember = value.FindMember("_name");
	const char* nodeName = nameMember->value.GetString();
	node->name = nodeName;
	PRINT_LOG("Retrieve node = [%s] from scene data", node->name);

	// todo : move visible property from node to gameobject
	// auto visibleMember = value.FindMember("_visible");
	// bool visible = visibleMember->value.GetBool();
	// node->visible = visible;

	// todo : retrieve layer to gameobject.
	// auto layerMember = value.FindMember("_layer");
	// int layer = layerMember->value.GetInt();
	// node->gameobject->layer = spring::Layer(layer);

	auto transformMember = value.FindMember("transform");
	Transform* transform = toTransform(transformMember->value);
	node->transform = transform;
	
	// todo : replaced by game object's nodes
	// auto nodesMember = value.FindMember("nodes");
	// for (auto comMember = nodesMember->value.MemberBegin(); comMember != nodesMember->value.MemberEnd(); comMember++)
	// {
	// 	Node* comNode = toNode(comMember->value);
	// 	PRINT_ERROR("does not support additional component node.");
	// }
	// todo : replaced by game object's children
	// auto childrenMember = value.FindMember("children");
	// for (auto childMember = childrenMember->value.MemberBegin(); childMember != childrenMember->value.MemberEnd(); childMember++)
	// {
	// 	Node* child = toNode(childMember->value);
	// 	child->SetParent(node);
	// }
	return node;
}
Behaviour* JsonSerializer::toBehaviour(Value& value) 
{
	Behaviour* hehaviour = nullptr;
	auto behaviourType = value.FindMember("_behaviourType")->value.GetString();
	if (strcmp(behaviourType,"class::spring::GameApp") == 0)
		hehaviour = new GameApp();
	return hehaviour;
}
MeshRenderer* JsonSerializer::toMeshRenderer(Value& value)
{
	auto materialValue = value.FindMember("_parameters");
	auto shaderValue = value.FindMember("_shader");
	auto meshValue = value.FindMember("_mesh");

	Material* material = toMaterial(materialValue->value);
	Shader* shader = toShader(shaderValue->value);
	Mesh* mesh = toMesh(meshValue->value);
	material->shader = shader;
	MeshRenderer* meshrenderer = new MeshRenderer(material);
	meshrenderer->mesh = mesh;
	meshrenderer->Initialize();
	return meshrenderer;
}
Transform* JsonSerializer::toTransform(Value& value)
{
	auto positionMember = value.FindMember("position");
	auto eulerangleMember = value.FindMember("eulerangle");
	auto scaleMember = value.FindMember("scale");
	Vector3 position = toVector3(positionMember->value);
	Vector3 eulerangle = toVector3(eulerangleMember->value);
	Vector3 scale = toVector3(scaleMember->value);
	Transform* transform = new Transform();
	transform->position = position;
	transform->eulerangle = eulerangle;
	transform->scale = scale;
	return transform;
}
Material* JsonSerializer::toMaterial(Value& value)
{
	Material* material = new Material();

	auto renderMode = value.FindMember("_rendermode")->value.GetInt();
	material->renderMode = Material::RenderMode(renderMode);

	auto enableGPUInstancing = value.FindMember("_enable_gpu_instanceing")->value.GetBool();
	material->enableGPUInstanced = enableGPUInstancing;

	auto enableAlphaTest = value.FindMember("_enable_alphatest")->value.GetBool();
	material->alphaTest = enableAlphaTest;

	auto _alphafunc = value.FindMember("_alphafunc")->value.GetInt();
	material->alphaFunc = _alphafunc;

	auto _alpharef = value.FindMember("_alpharef")->value.GetFloat();
	material->alphaRef = _alpharef;

	auto _enable_blend = value.FindMember("_enable_blend")->value.GetBool();
	material->blend = _enable_blend;

	auto _src_factor = value.FindMember("_src_factor")->value.GetInt();
	material->srcFactor = _src_factor;

	auto _dst_factor = value.FindMember("_dst_factor")->value.GetInt();
	material->dstFactor = _dst_factor;

	auto _enable_depthtest = value.FindMember("_enable_depthtest")->value.GetBool();
	material->depthTest = _enable_depthtest;

	auto _enable_depthwrite = value.FindMember("_enable_depthwrite")->value.GetBool();
	material->depthWrite = _enable_depthwrite;

	auto _depthfunc = value.FindMember("_depthfunc")->value.GetInt();
	material->depthFunc = _depthfunc;

	auto _enable_stecialtest = value.FindMember("_enable_stecialtest")->value.GetBool();
	material->stencilTest = _enable_stecialtest;

	auto _enbale_cullface = value.FindMember("_enbale_cullface")->value.GetBool();
	material->cullface = _enbale_cullface;

	auto _cullfacefunc = value.FindMember("_cullfacefunc")->value.GetInt();
	material->cullfaceFunc = _cullfacefunc;

	return material;
}
Shader* JsonSerializer::toShader(Value& value)
{
	auto vsValue = value.FindMember("_vs");
	auto fsValue = value.FindMember("_fs");
	const char* vs = vsValue->value.GetString();
	const char* fs = fsValue->value.GetString();
	Value::MemberIterator parametersValue = value.FindMember("_parameters");

	Shader* shader = Shader::Load(vs, fs);
	for (auto parameterMember = parametersValue->value.MemberBegin(); parameterMember != parametersValue->value.MemberEnd(); parameterMember++)
	{
		const char* parameterName = parameterMember->name.GetString();
		Value* pValue = &parameterMember->value;
		if (pValue->IsInt())  // contains textures
		{
			int intValue = pValue->GetInt();
			shader->setInt(parameterName, intValue);
		}
		else if (pValue->IsBool())
		{
			bool boolValue = pValue->GetBool();
			shader->setBool(parameterName, boolValue);
		}
		else if (pValue->IsFloat())
		{
			bool floatValue = pValue->GetFloat();
			shader->setFloat(parameterName, floatValue);
		}
		else if (pValue->IsObject())
		{
			if (!pValue->HasMember("_dataType"))
				continue;
			auto dataTypeValue = pValue->FindMember("_dataType");
			const char* dataType = dataTypeValue->value.GetString();
			if (strcmp(dataType, "vector3") == 0)
			{
				Vector3 vec3 = toVector3(*pValue);
				shader->setVec3(parameterName, vec3);
			}
			else if (strcmp(dataType, "colorf") == 0)
			{
				Colorf colorf = toColorf(*pValue);
				shader->setColor(parameterName, colorf);
			}
			else if (strcmp(dataType, "vector2") == 0)
			{
				Vector2 vec2 = toVector2(*pValue);
				shader->setVec2(parameterName, vec2);
			}
			else if (strcmp(dataType, "vector4") == 0)
			{
				Vector4 vec4 = toVector4(*pValue);
				shader->setVec4(parameterName, vec4);
			}
			else if (strcmp(dataType, "color") == 0)
			{
				Color color = toColor(*pValue);
				shader->setColor(parameterName, color);
			}
			else
			{
				PRINT_ERROR("can not deserialize unkown data type [%s]", dataType);
			}
		}
	}
	return shader;
}
Mesh* JsonSerializer::toMesh(Value& value)
{
	auto meshResValue = value.FindMember("_res");
	auto drawTypeValue = value.FindMember("_draw_type");
	auto meshModeValue = value.FindMember("_mesh_mode");
	Mesh* mesh = &ModelLoader::LoadMeshFromFile(meshResValue->value.GetString());
	mesh->drawType = Mesh::DrawType(drawTypeValue->value.GetInt());
	mesh->mode = Mesh::Mode(meshModeValue->value.GetInt());
	return mesh;
}
Vector2 JsonSerializer::toVector2(Value& value)
{
	auto xValue = value.FindMember("x");
	float x = xValue->value.GetFloat();
	auto yValue = value.FindMember("y");
	float y = yValue->value.GetFloat();
	return Vector2(x, y);
}
Vector3 JsonSerializer::toVector3(Value& value)
{
	auto xValue = value.FindMember("x");
	float x = xValue->value.GetFloat();
	auto yValue = value.FindMember("y");
	float y = yValue->value.GetFloat();
	auto zValue = value.FindMember("z");
	float z = zValue->value.GetFloat();
	return Vector3(x, y, z);
}
Vector4 JsonSerializer::toVector4(Value& value)
{
	auto xValue = value.FindMember("x");
	float x = xValue->value.GetFloat();
	auto yValue = value.FindMember("y");
	float y = yValue->value.GetFloat();
	auto zValue = value.FindMember("z");
	float z = zValue->value.GetFloat();
	auto wValue = value.FindMember("w");
	float w = wValue->value.GetFloat();
	return Vector4(x, y, z, w);
}
Color JsonSerializer::toColor(Value& value)
{
	auto rValue = value.FindMember("r");
	unsigned char r = rValue->value.GetInt();
	auto gValue = value.FindMember("g");
	unsigned char g = gValue->value.GetInt();
	auto bValue = value.FindMember("b");
	unsigned char b = bValue->value.GetInt();
	auto aValue = value.FindMember("a");
	unsigned char a = aValue->value.GetInt();
	return Color(r, g, b, a);
}
Colorf JsonSerializer::toColorf(Value& value)
{
	auto rValue = value.FindMember("r");
	float r = rValue->value.GetFloat();
	auto gValue = value.FindMember("g");
	float g = gValue->value.GetFloat();
	auto bValue = value.FindMember("b");
	float b = bValue->value.GetFloat();
	auto aValue = value.FindMember("a");
	float a = aValue->value.GetFloat();
	return Colorf(r, g, b, a);
}