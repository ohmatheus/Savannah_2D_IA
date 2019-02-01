#include "stdafx.h"

#include "StateNode.h"
#include "Transition.h"
#include "GridEntity.h"

namespace StateMachine
{
	StateNode::StateNode(IScene *scene)
	:	m_Scene(scene)
	{

	}

	//----------------------------------------------------------

	StateNode::~StateNode()
	{

	}

	//----------------------------------------------------------	

	void	StateNode::UpdateEntity(GridEntity *ent, float dt)
	{
		GridScene *gridScene = static_cast<GridScene*>(m_Scene); // Temporary
		for (int i = 0; i < m_OutTransitions.size(); i++)
		{
			if (m_OutTransitions[i]->TestCondition(gridScene, ent))
			{
				ent->ChangeStateNode(m_OutTransitions[i]->Get());
				return;
			}
		}
		assert(m_Scene != nullptr);
		m_Func(m_Scene, ent, dt);
	}

	//----------------------------------------------------------

	void	StateNode::SetFunc(const FuncPtr &func)
	{
		m_Func = func;
	}
}
//----------------------------------------------------------