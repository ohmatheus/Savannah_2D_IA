#pragma once

#include "IEntity.h"
#include "GridScene.h"

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
	SimpleEntity(const std::string &name, GridScene::ETeam team, bool isActive = true);
	virtual ~SimpleEntity();

	virtual void		Update(float dt) override;

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

	GridScene::ETeam	Team() { return m_Team; }

protected:
	StateMachine::StateNode	*m_CurrentStateNode = nullptr;
	float					m_MovementSpeed = 2.5f;
	float					m_RotationSpeed = 50.f;
	GridScene::ETeam		m_Team;
};

//----------------------------------------------------------