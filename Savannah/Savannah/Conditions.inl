#pragma once

#include "Conditions.h"

namespace StateMachine
{
	template <typename _Type>
	ValueCondition<_Type>::ValueCondition(EConditionParameter testArg, EConditionOperation testOp, const _Type &controlValue)
	:	Super()
	,	m_ControlValue(controlValue)
	,	m_ParameterToTest(testArg)
	,	m_TestOperation(testOp)
	{}

	//----------------------------------------------------------

	template <typename _Type>
	ValueCondition<_Type>::~ValueCondition()
	{}

	//----------------------------------------------------------

	template <typename _Type>
	bool		ValueCondition<_Type>::Test(GridScene *sce, GridEntity *ent)
	{
		bool result = false;
		if (m_TestOperation & Inferior)
		{
			_Type	value = 0;
			_GetValueToTest(m_ParameterToTest, sce, ent, value);
			result |= value < m_ControlValue;
		}
		if (m_TestOperation & Superior)
		{
			_Type	value = 0;
			_GetValueToTest(m_ParameterToTest, sce, ent, value);
			result |= value > m_ControlValue;
		}
		if (m_TestOperation & Equal)
		{
			_Type	value = 0;
			_GetValueToTest(m_ParameterToTest, sce, ent, value);
			result |= value == m_ControlValue;
		}
		if (m_TestOperation & Not)
		{
			_Type	value = 0;
			_GetValueToTest(m_ParameterToTest, sce, ent, value);
			result |= !value;
		}
		return result;
	}

	//----------------------------------------------------------

	template <typename _Type>
	bool	ValueCondition<_Type>::_GetValueToTest(EConditionParameter arg, GridScene *scene, GridEntity *ent, _Type &outValue)
	{
		switch (arg)
		{
		case EConditionParameter::EHealth:
		{
			// ???
			break;
		}
		case EConditionParameter::EHasFriendAlive:
		{
			outValue = ent->m_StateMachineAttr.m_NearestEnemy != nullptr;
			return true;
		}
		case EConditionParameter::EEnnemyDistance:
		{
			if (ent->m_StateMachineAttr.m_NearestEnemy == nullptr)
			{
				outValue = 0x7F800000; // inf
				return false;
			}
			assert(ent->m_StateMachineAttr.m_NearestEnemy->IsActive()); // otherwise means that PreUpdate went wrong
			const glm::vec3		&enemyPosition = ent->m_StateMachineAttr.m_NearestEnemy->Position();
			const glm::vec3		&myPosition = ent->Position();
			outValue = glm::length(enemyPosition - myPosition);
			return true;
		}
		case EConditionParameter::EFriendDistance:
		{
			if (ent->m_StateMachineAttr.m_NearestFriend == nullptr)
			{
				outValue = 0x7F800000; // inf
				return false;
			}
			assert(ent->m_StateMachineAttr.m_NearestFriend->IsActive()); // otherwise means that PreUpdate went wrong
			const glm::vec3		&friendPosition = ent->m_StateMachineAttr.m_NearestFriend->Position();
			const glm::vec3		&myPosition = ent->Position();
			outValue = glm::length(friendPosition - myPosition);
			return true;
		}
		case EConditionParameter::EMyFlagDistance:
		{
			GridEntity		*flag = scene->Flag(ent->Team());
			outValue = glm::length(flag->Position() - ent->Position());
			return true;
		}
		case EConditionParameter::EEnemyFlagDistance:
		{
			GridScene::ETeam myTeam = ent->Team();
			GridEntity *flag = scene->Flag(myTeam == GridScene::LION ? GridScene::ANTELOPE : myTeam);
			outValue = glm::length(flag->Position() - ent->Position());
			return true;
		}
		case EConditionParameter::ENearFriendCount:
		{
			outValue = ent->m_StateMachineAttr.m_FriendsNextToMe;
			return true;
		}
		default: assert(false); break;
		}
		return false;
		outValue = 0;
	}
	//----------------------------------------------------------
}
