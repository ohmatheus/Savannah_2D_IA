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

protected:
	StateMachine::StateNode	*m_CurrentStateNode = nullptr;
};

//----------------------------------------------------------