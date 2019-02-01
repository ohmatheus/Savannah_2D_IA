#include "stdafx.h"

#include "StateMachineManager.h"
#include "StateNode.h"
#include "Transition.h"
#include "Conditions.h"

//----------------------------------------------------------

namespace StateMachine
{
	StateMachineManager::StateMachineManager(IScene *scene)
	:	m_Scene(scene)
	{}

//----------------------------------------------------------

	StateMachineManager::~StateMachineManager()
	{
		for (int i = 0; i < m_All.size(); i++)
			delete m_All[i];
	}

//----------------------------------------------------------

	StateNode		*StateMachineManager::NewState()
	{
		StateNode *newNode = new StateNode(m_Scene);
		m_All.push_back(newNode);
		return newNode;
	}

//----------------------------------------------------------

	Transition		*StateMachineManager::NewTransition(StateNode *to, ICondition *condition)
	{
		Transition *newTransition = new Transition(to, condition);
		m_All.push_back(newTransition);
		return newTransition;
	}

//----------------------------------------------------------

	ICondition		*StateMachineManager::NewCondition(ICondition *conditionA, ELogicalCondition logOp, ICondition *conditionB)
	{
		ICondition *newCondition = new CombineCondition(conditionA, logOp, conditionB);
		m_All.push_back(newCondition);
		return newCondition;
	}

//----------------------------------------------------------
}