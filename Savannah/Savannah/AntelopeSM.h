#pragma once

#include "StateMachineManager.h"

namespace StateMachine
{
	class AntelopeStateMachine : public StateMachineManager
	{
		using Super = StateMachineManager;
	public:
		AntelopeStateMachine(IScene *scene);
		virtual ~AntelopeStateMachine();
	};
}
