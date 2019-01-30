#include "stdafx.h"

#include "AntelopeSM.h"
#include "StateNode.h"
#include "SimpleEntity.h"

namespace StateMachine
{
	AntelopeStateMachine::AntelopeStateMachine()
	{
		StateNode *idle = NewState();
		m_Root = idle;
		idle->SetFunc([](SimpleEntity *ent, float dt)
		{
			//ent->m_Yaw += 60.f * dt;
		});
	}

//----------------------------------------------------------

	AntelopeStateMachine::~AntelopeStateMachine()
	{}

//----------------------------------------------------------
}
