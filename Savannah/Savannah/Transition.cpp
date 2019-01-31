#include "stdafx.h"

#include "Transition.h"
#include "GridScene.h"
#include "Conditions.h"

namespace StateMachine
{
//----------------------------------------------------------

	Transition::Transition(StateNode *to, ICondition *condition)
	:	m_NextNode(to)
	,	m_Condition(condition)
	{}

//----------------------------------------------------------

	Transition::~Transition()
	{}

//----------------------------------------------------------

	bool		Transition::TestCondition(GridScene *sce, GridEntity *ent)
	{
		return m_Condition->Test(sce, ent);
	}

//----------------------------------------------------------
}