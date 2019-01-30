#pragma once

#include "StateMachineManager.h"

//----------------------------------------------------------

class StateNode;
class SimpleEntity;
class ICondition;

//----------------------------------------------------------

namespace StateMachine
{
	class Transition : public StateMachineObject
	{
		using Self = Transition;
	public:
		Transition();
		virtual ~Transition();

		bool		TestCondition(SimpleEntity *ent);
		StateNode	*Get() { return m_NextNode; }
		void		SetCondition(ICondition *condition) { m_Condition = condition; }

	protected:
		StateNode	*m_NextNode;
		ICondition	*m_Condition;
	};
}

//----------------------------------------------------------
