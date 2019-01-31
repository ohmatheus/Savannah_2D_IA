#pragma once

#include "IEntity.h"
#include "GridScene.h"

//----------------------------------------------------------

namespace StateMachine
{
	class StateNode;
}

//----------------------------------------------------------

class GridEntity : public IEntity
{
	using Super = IEntity;
	using Self = GridEntity;
public:

	struct StateMachineAttributes
	{
		GridEntity	*m_NearestFriend = nullptr;
		GridEntity	*m_NearestEnemy = nullptr;

		//float	m_DistanceFromNearestFriend;
		//float	m_DistanceFromNearestFriend;
	};

	GridEntity(const std::string &name, GridScene::ETeam team, bool isActive = true);
	virtual ~GridEntity();

	virtual void		Update(float dt) override;
	virtual void		Render(RenderSystem *rs) override;
	void				ChangeStateNode(StateMachine::StateNode *node) { m_CurrentStateNode = node; }
	const glm::vec3		Forward();
	float				MovementSpeed() { return m_MovementSpeed; }
	float				RotationSpeed() { return m_RotationSpeed; }
	GridScene::ETeam	Team() { return m_Team; }

	void				MoveForward(float dt) //inlined
	{
		m_Position += Forward() * dt * m_MovementSpeed;
	}
	void				Rotate(float angle, float dt) // inlined
	{
		m_Roll += clamp(angle, -m_RotationSpeed, m_RotationSpeed) * dt * 5;
	}

	StateMachineAttributes	m_StateMachineAttr;
protected:
	StateMachine::StateNode	*m_CurrentStateNode = nullptr;
	float					m_MovementSpeed = 2.5f;
	float					m_RotationSpeed = 50.f;
	GridScene::ETeam		m_Team;
};

//----------------------------------------------------------