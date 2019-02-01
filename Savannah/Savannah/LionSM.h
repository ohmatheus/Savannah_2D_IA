#pragma once

#include "StateMachineManager.h"

namespace StateMachine
{
	class LionStateMachine : public StateMachineManager
	{
		using Super = StateMachineManager;
	public:
		LionStateMachine(IScene *scene);
		virtual ~LionStateMachine();
	};
}
