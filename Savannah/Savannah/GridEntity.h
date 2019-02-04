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
		GridEntity					*m_NearestFriend = nullptr;
		GridEntity					*m_NearestEnemy = nullptr;
		int							m_FriendsNextToMe = 0;

		void Clear()
		{
			m_NearestFriend = nullptr;
			m_NearestEnemy = nullptr;
			m_FriendsNextToMe = 0;
		}
	};

	GridEntity(const std::string &name, GridScene::ETeam team, bool isActive = true);
	virtual ~GridEntity();
	GridEntity(const GridEntity &from);

	virtual GridEntity				*Clone() override;
	virtual void					Update(float dt) override;
	virtual void					Render(RenderSystem *rs) override;
	void							ChangeStateNode(StateMachine::StateNode *node) { m_CurrentStateNode = node; }
	const glm::vec3					Forward(bool worldSpace = false);
	void							SetMovementSpeed(float mov) { m_MovementSpeed = mov; }
	float							MovementSpeed() { return m_MovementSpeed; }
	void							SetRotationSpeed(float rot) { m_RotationSpeed = rot; }
	float							RotationSpeed() { return m_RotationSpeed; }
	GridScene::ETeam				Team() { return m_Team; }
	virtual void					Die() override;
	float							Health() { return m_Health; }
	void							SetHealth(float health) { m_Health = health; }
	float							Dps() { return m_Dps; }
	void							SetDps(float dps) { m_Dps = dps; }
	void							Hit(float dmg) { m_Health -= dmg; }
	void							Seek(glm::vec3 position, float dt);
	void							Flee(glm::vec3 position, float dt);
	StateMachineAttributes			&StateMachineAttr() { return m_StateMachineAttr; }

	void							MoveForward(float dt) // inlined
	{
		m_Position += Forward() * dt * m_MovementSpeed;
	}

	void							Rotate(float angle, float dt) // inlined
	{
		m_Roll += clamp(angle, -m_RotationSpeed, m_RotationSpeed) * dt * 5;
	}

protected:
	StateMachine::StateNode			*m_CurrentStateNode = nullptr;
	float							m_MovementSpeed = 2.5f;
	float							m_RotationSpeed = 50.f;
	GridScene::ETeam				m_Team;
	float							m_Health = 10.f;
	float							m_Dps = 10.f;
	StateMachineAttributes			m_StateMachineAttr;
};

//----------------------------------------------------------