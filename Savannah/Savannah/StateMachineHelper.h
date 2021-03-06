#pragma once

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
		EDistanceFromMyFlag,
		EDistanceFromEnemyFlag,
		ENearFriendCount,

		EHasFlag,
		ETeamHasFlag,
		EEnemyTeamHasFlag
	};

	enum EConditionOperation
	{
		Inferior = 1 << 0,
		Superior = 1 << 1,
		Equal = 1 << 2,
		Not = 1 << 3,
	};

	enum ELogicalCondition
	{
		And = 1 << 0,
		Or = 1 << 1
	};

	class StateMachineObject
	{
	public:
		virtual ~StateMachineObject() {}
	};
}