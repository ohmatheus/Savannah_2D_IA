#pragma once

#include "StateMachineManager.h"

#include <functional>

//----------------------------------------------------------

class SimpleEntity;
class Transition;

//----------------------------------------------------------

namespace StateMachine
{
	class StateNode : public StateMachineObject
	{
		using Self = StateNode;
	public:
		StateNode();
		virtual ~StateNode();

		virtual void				UpdateEntity(SimpleEntity *ent, float dt);
		void						SetFunc(const std::function<void(SimpleEntity *ent, float dt)> &func);

		void						AddTransition(Transition* transition);

	protected:
		std::vector<Transition*>							m_OutTransitions;
		std::function<void(SimpleEntity *ent, float dt)>	m_Func;
	};
}

//----------------------------------------------------------
