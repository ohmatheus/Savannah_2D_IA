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

	Transition		*StateMachineManager::NewTransition(StateNode *from, StateNode *to, ICondition *condition)
	{
		assert(from != nullptr);
		assert(to != nullptr);
		Transition *newTransition = new Transition(to, condition);
		from->AddTransition(newTransition);
		m_All.push_back(newTransition);
		return newTransition;
	}

//----------------------------------------------------------

	ICondition		*StateMachineManager::NewCondition(ICondition *conditionA, ELogicalCondition logOp, ICondition *conditionB)
	{
		assert(conditionA != nullptr);
		assert(conditionB != nullptr);
		ICondition *newCondition = new CombineCondition(conditionA, logOp, conditionB);
		m_All.push_back(newCondition);
		return newCondition;
	}

//----------------------------------------------------------
}