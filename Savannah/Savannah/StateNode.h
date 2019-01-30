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
		typedef std::function<void(IScene *scene, SimpleEntity *ent, float dt)> FuncPtr;

	public:
		StateNode(IScene *scene);
		virtual ~StateNode();

		virtual void				UpdateEntity(SimpleEntity *ent, float dt);
		void						SetFunc(const FuncPtr &func);

		void						AddTransition(Transition* transition);

	protected:
		std::vector<Transition*>	m_OutTransitions;
		FuncPtr						m_Func;
		IScene						*m_Scene;
	};
}

//----------------------------------------------------------
