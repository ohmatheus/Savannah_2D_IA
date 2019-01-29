#pragma once

#include <vector>

//----------------------------------------------------------

class	StateMachineManager;
class	FSM_StateNode;
class	FSM_Transition;
class	FSM_Condition;

//----------------------------------------------------------

class StateMachineManager
{
	using Self = StateMachineManager;
public:
	StateMachineManager();
	virtual ~StateMachineManager();

protected:
	FSM_StateNode				*m_Root;
	std::vector<FSM_StateNode*>	m_AllNodes;
};

//----------------------------------------------------------

class FSM_StateNode
{
	using Self = FSM_StateNode;
public:
	FSM_StateNode();
	virtual ~FSM_StateNode();

protected:
};

//----------------------------------------------------------

class FSM_Transition
{
	using Self = FSM_Transition;
public:
	FSM_Transition();
	virtual ~FSM_Transition();

protected:
	FSM_StateNode	*m_NextNode;
	FSM_Condition	*m_Condition;
};

//----------------------------------------------------------

class FSM_Condition
{
	using Self = FSM_Condition;
public:
	FSM_Condition();
	virtual ~FSM_Condition();

protected:
};

//----------------------------------------------------------

