#pragma once

#include "StateMachineManager.h"

#include <functional>

//----------------------------------------------------------

class GridEntity;
class Transition;

//----------------------------------------------------------

namespace StateMachine
{
	class StateNode : public StateMachineObject
	{
		using Self = StateNode;
		typedef std::function<void(IScene *scene, GridEntity *ent, float dt)> FuncPtr;

	public:
		StateNode(IScene *scene);
		virtual ~StateNode();

		virtual void				UpdateEntity(GridEntity *ent, float dt);
		void						SetFunc(const FuncPtr &func);

		void						AddTransition(Transition* transition) { m_OutTransitions.push_back(transition); }

	protected:
		std::vector<Transition*>	m_OutTransitions;
		FuncPtr						m_Func;
		IScene						*m_Scene;
	};
}

//----------------------------------------------------------
