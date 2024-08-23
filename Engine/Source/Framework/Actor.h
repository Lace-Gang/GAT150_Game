#pragma once

#include "Object.h"
#include "../Math/Transform.h"
//#include "../Renderer/Model.h"
#include "Components/Component.h"
//#include "../Math/Vector2.h"

#include<iostream>
#include <memory>
#include <vector>
#include <functional>


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

	Actor(const Actor& other);

	CLASS_DECLARATION(Actor)
	CLASS_PROTOTYPE(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	void Draw(Renderer& renderer);

	std::function<void(Actor*)> OnCollisionEnter;
	std::function<void(Actor*)> OnCollisionExit;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();
	template<typename T>
	std::vector<T*> GetComponents();
	//vector cause don't know how many, and no plans to delete any


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



template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;
	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}

	return results;
}
