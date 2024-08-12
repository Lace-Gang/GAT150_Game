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
	Actor(const Transform& transform) : m_transform{ transform } {}
	//Actor(const Transform& transform, Model* model) : 
	//	m_transform{ transform }, 
	//	//m_model{ model }
	//{}

	CLASS_DECLARATION(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	void SetDamping(float damping) { m_damping = damping; }

	const Transform& GetTransform() { return m_transform; }
	void SetTransform(Transform& transform) { m_transform = transform; }


	bool& GetDestroyed() { return m_destroyed; }

	
	virtual void OnCollision(Actor* actor) {} //changed that to be not pure virtual (from "= 0"
	//float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
	float GetRadius() { return 0; }


	friend class Scene; 
public:
	std::string tag;
	float lifespan = 0;

protected: 
	bool m_destroyed = false;
	
	Transform m_transform;
	Vector2 m_velocity{ 0,0 };
	float m_damping{ 0 };

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
};