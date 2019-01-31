#include "stdafx.h"

#include "Transition.h"

namespace StateMachine
{
//----------------------------------------------------------

	Transition::Transition()
	{}

//----------------------------------------------------------

	Transition::~Transition()
	{}

//----------------------------------------------------------

	bool		Transition::TestCondition(GridEntity *ent)
	{
		return true;
	}

//----------------------------------------------------------
}