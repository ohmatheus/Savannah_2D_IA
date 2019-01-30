#include "stdafx.h"

#include "StateNode.h"
#include "Transition.h"
#include "SimpleEntity.h"

namespace StateMachine
{
	StateNode::StateNode()
	{

	}

	StateNode::~StateNode()
	{

	}

	void	StateNode::UpdateEntity(SimpleEntity *ent, float dt)
	{
		for (int i = 0; i < m_OutTransitions.size(); i++)
		{
			if (m_OutTransitions[i]->TestCondition(ent))
			{
				ent->ChangeStateNode(m_OutTransitions[i]->Get());
				return;
			}
		}
		m_Func(ent, dt);
	}

	void	StateNode::SetFunc(const std::function<void(SimpleEntity *ent, float dt)> &func)
	{
		m_Func = func;
	}
}
//----------------------------------------------------------