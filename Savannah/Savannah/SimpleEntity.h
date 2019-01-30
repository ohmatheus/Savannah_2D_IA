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

	void				MoveForward(float dt);
	void				Rotate(bool clockwise, float dt);

	float				MovementSpeed() { return m_MovementSpeed; }
	float				RotationSpeed() { return m_RotationSpeed; }

protected:
	StateMachine::StateNode	*m_CurrentStateNode = nullptr;
	float					m_MovementSpeed = 2.5f;
	float					m_RotationSpeed = 25.f;
};

//----------------------------------------------------------