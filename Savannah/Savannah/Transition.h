#pragma once

#include "StateMachineManager.h"

//----------------------------------------------------------

class StateNode;
class GridEntity;
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

		bool		TestCondition(GridEntity *ent);
		StateNode	*Get() { return m_NextNode; }
		void		SetCondition(ICondition *condition) { m_Condition = condition; }

	protected:
		StateNode	*m_NextNode;
		ICondition	*m_Condition;
	};
}

//----------------------------------------------------------
