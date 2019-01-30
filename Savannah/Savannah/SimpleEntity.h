#pragma once

#include "IEntity.h"

//----------------------------------------------------------

namespace StateMachine
{
	class StateNode;
}

//----------------------------------------------------------

class SimpleEntity : public IEntity
{
	using Super = IEntity;
	using Self = SimpleEntity;
public:
	SimpleEntity(const std::string &name);
	virtual ~SimpleEntity();

	virtual void		Update(float dt) override;
	virtual void		Render(RenderSystem *renderSystem) override;

	void				ChangeStateNode(StateMachine::StateNode *node) { m_CurrentStateNode = node; }

	void				MoveForward(float dt) //inlined
	{
		const glm::mat4	&model = ModelMatrix();
		glm::vec3		directionVector = model * glm::vec4(0.f, 1.f, 0.f, 0.f); // yes, in this world, forward is Y, easier to manipulate.
		m_Position += glm::normalize(directionVector) * dt * m_MovementSpeed;
	}
	void				Rotate(float angle, float dt) // inlined
	{
		m_Roll += clamp(angle, -m_RotationSpeed, m_RotationSpeed) * dt;
	}

	float				MovementSpeed() { return m_MovementSpeed; }
	float				RotationSpeed() { return m_RotationSpeed; }

protected:
	StateMachine::StateNode	*m_CurrentStateNode = nullptr;
	float					m_MovementSpeed = 2.5f;
	float					m_RotationSpeed = 25.f;
};

//----------------------------------------------------------