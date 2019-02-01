#pragma once

#include <vector>
#include "StateMachineHelper.h"
#include "Conditions.inl"

//----------------------------------------------------------

class	IScene;

//----------------------------------------------------------

namespace StateMachine
{
	class	StateNode;
	class	Transition;
	class	ICondition;

	class StateMachineManager
	{
		using Self = StateMachineManager;
	public:
		StateMachineManager(IScene *scene);
		virtual ~StateMachineManager();

		StateNode		*NewState();
		Transition		*NewTransition(StateNode *from, StateNode *to, ICondition *condition);

		template <typename _Type>
		ICondition		*NewCondition(EConditionParameter arg, int op, const _Type &controlValue)
		{
			ICondition *newCondition = new ValueCondition<_Type>(arg, static_cast<EConditionOperation>(op), controlValue);
			m_All.push_back(newCondition);
			return newCondition;
		}

		ICondition		*NewCondition(ICondition *conditionA, ELogicalCondition logOp, ICondition *conditionB);

		StateNode		*Root() { return m_Root; }
	
	protected:
		StateNode							*m_Root;
		std::vector<StateMachineObject*>	m_All;
		IScene								*m_Scene;
	};
}
//----------------------------------------------------------
