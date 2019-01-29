#pragma once

#include <vector>

//----------------------------------------------------------

class	StateMachineManager;
class	FSM_StateNode;
class	FSM_Transition;
class	FSM_Condition;
class	IEntity;

//----------------------------------------------------------

namespace StateMachine
{
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
	
		virtual	FSM_StateNode			*GetNextState_IFN();
		virtual void					UpdateEntity(IEntity *ent, float dt) = 0;
	
	protected:
		std::vector<FSM_Transition*>	m_OutTransitions;
	};
	
	//----------------------------------------------------------
	
	class FSM_Transition
	{
		using Self = FSM_Transition;
	public:
		FSM_Transition();
		virtual ~FSM_Transition();
	
		bool			TestCondition(IEntity *ent);
		FSM_StateNode	*Get();
	
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
	
		virtual bool	Test(IEntity *ent) = 0;
	};
	
	//----------------------------------------------------------
	
	template <typename _Type>
	class FSM_ValueCondition : public FSM_Condition
	{
		using Self = FSM_ValueCondition;
		using Super = FSM_Condition;
	public:
		FSM_ValueCondition(EConditionParameter, EConditionOperation, const _Type &controlValue);
		virtual ~FSM_ValueCondition();

		enum EConditionParameter
		{
			EHealth,
			EEnnemyDistance,
			EFriendDistance,
			EFlagDistance
		};
	
		enum EConditionOperation
		{
			Inferior	= 0 << 1,
			Superior	= 0 << 2,
			Equal		= 0 << 3,
			Not			= 0 << 4
		};
	
		virtual bool		Test(IEntity *ent) override;
	
	private:
		_Type				m_ControlValue;
		EConditionParameter	m_ParameterToTest;
		EConditionOperation	m_TestOperation;
	};
	
	//----------------------------------------------------------
	
	class FSM_CombineCondition : public FSM_Condition
	{
		using Self = FSM_CombineCondition;
		using Super = FSM_Condition;
	public:
		FSM_CombineCondition();
		virtual ~FSM_CombineCondition();
	
		virtual bool		Test(IEntity *ent) override;
	private:
		FSM_Condition *m_FirstCondition;
		FSM_Condition *m_SecondCondition;
	};
}

//----------------------------------------------------------

