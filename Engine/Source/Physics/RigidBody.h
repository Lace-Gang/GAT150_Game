#pragma once
#include "Math/Transform.h"
#include <box2d/box2d.h>

class RigidBody
{
public:
	struct def_t
	{
		// body
		float gravityScale = 1;
		float damping = 0;
		float angularDamping = 0;
		bool  constrainAngle = false; //(makes the object not rotate when it falls or anything)
		bool  isDynamic = true;

		// shape
		float friction = 0.0f;
		float restitution = 0.0f; //how much energy is conserved after bouncing (how bouncy it is)
		float density = 1.0f;
		bool isSensor = false; //sensors do not have collision

		//bool innitialSensor = false;

		class Actor* actor{ nullptr };
	};

public:
	RigidBody(const Transform& transform, const Vector2& size, const def_t& def, const class Physics& physics);
	~RigidBody();

	void SetTransform(const Vector2& position, float rotation);
	Vector2 GetPosition();

	float GetAngle();

	void ApplyForce(const Vector2& force);
	void SetVelocity(const Vector2& velocity);
	Vector2 GetVelocity();

	void ApplyTorque(float torque);
	void SetAngularVelocity(float velocity);

	void EnableCollision();
	void DisableCollision();


private:
	b2BodyId m_bodyId{ b2_nullBodyId };
};