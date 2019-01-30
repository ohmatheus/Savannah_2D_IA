#include "stdafx.h"

#include "StateNode.h"
#include "Transition.h"
#include "SimpleEntity.h"

namespace StateMachine
{
	StateNode::StateNode(IScene *scene)
	:	m_Scene(scene)
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
		assert(m_Scene != nullptr);
		m_Func(m_Scene, ent, dt);
	}

	void	StateNode::SetFunc(const FuncPtr &func)
	{
		m_Func = func;
	}
}
//----------------------------------------------------------