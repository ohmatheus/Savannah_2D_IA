#pragma once

#include <vector>

//----------------------------------------------------------

class	IScene;

//----------------------------------------------------------

namespace StateMachine
{
	class	StateNode;
	class	Transition;
	class	ICondition;

	enum EConditionParameter
	{
		EHealth,
		EHasFriendAlive,
		EEnnemyDistance,
		EFriendDistance,
		EMyFlagDistance,
		EEnemyFlagDistance
	};

	enum EConditionOperation
	{
		Inferior = 0 << 0,
		Superior = 0 << 1,
		Equal = 0 << 2,
		Not = 0 << 3
	};

	enum ELogicalCondition
	{
		And =	1 << 0,
		Or =	1 << 1
	};

	class StateMachineObject
	{
	public:
		virtual ~StateMachineObject() {}
	};

	class StateMachineManager
	{
		using Self = StateMachineManager;
	public:
		StateMachineManager(IScene *scene);
		virtual ~StateMachineManager();

		StateNode		*NewState();
		Transition		*NewTransition();
		template <typename _Type>
		ICondition		*NewCondition(EConditionParameter arg, EConditionOperation op, const _Type &controlValue);
		ICondition		*NewCondition(ICondition *conditionA, ELogicalCondition logOp, ICondition *conditionB);

		StateNode		*Root() { return m_Root; }
	
	protected:
		StateNode							*m_Root;
		std::vector<StateMachineObject*>	m_All;
		IScene								*m_Scene;
	};
}
//----------------------------------------------------------
