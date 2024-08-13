#pragma once

#include "Object.h"
#include "../Math/Transform.h"
//#include "../Renderer/Model.h"
#include "Components/Component.h"
//#include "../Math/Vector2.h"

#include<iostream>
#include <memory>
#include <vector>


class Model; 
class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{ transform } {}
	//Actor(const Transform& transform, Model* model) : 
	//	m_transform{ transform }, 
	//	//m_model{ model }
	//{}

	CLASS_DECLARATION(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);



	bool& GetDestroyed() { return destroyed; }

	
	


	friend class Scene; 
public:
	std::string tag;
	float lifespan = 0;
	bool destroyed = false;

	Transform transform;
	Scene* scene{ nullptr };

protected: 
	std::vector<std::unique_ptr<Component>> components;
};