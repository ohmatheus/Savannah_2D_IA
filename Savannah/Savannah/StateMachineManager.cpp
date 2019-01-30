#include "stdafx.h"

#include "StateMachineManager.h"
#include "StateNode.h"
#include "Transition.h"
#include "Conditions.h"

//----------------------------------------------------------

namespace StateMachine
{
	StateMachineManager::StateMachineManager()
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
		StateNode *newNode = new StateNode();
		m_All.push_back(newNode);
		return newNode;
	}

//----------------------------------------------------------

	Transition		*StateMachineManager::NewTransition()
	{
		Transition *newTransition = new Transition();
		m_All.push_back(newTransition);
		return newTransition;
	}

//----------------------------------------------------------

	template <typename _Type>
	ICondition		*StateMachineManager::NewCondition(EConditionParameter arg, EConditionOperation op, const _Type &controlValue)
	{
		ICondition *newCondition = new ValueCondition<_Type>(arg, op, controlValue);
		m_All.push_back(newCondition);
		return newCondition;
	}

//----------------------------------------------------------

	ICondition		*StateMachineManager::NewCondition(ICondition *conditionA, ELogicalCondition logOp, ICondition *conditionB)
	{
		ICondition *newCondition = new CombineCondition(conditionA, logOp, conditionB);
		m_All.push_back(newCondition);
		return newCondition;
	}
}