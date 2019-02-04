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
		_Type	value = 0;
		if (!_GetValueToTest(m_ParameterToTest, sce, ent, value))
			return result;
		if (m_TestOperation & Inferior)
			result |= value < m_ControlValue;
		if (m_TestOperation & Superior)
			result |= value > m_ControlValue;
		if (m_TestOperation & Equal)
			result |= value == m_ControlValue;
		if (m_TestOperation & Not)
			result |= !value;
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
			outValue = ent->Health();
			return true;
		}
		case EConditionParameter::EHasFriendAlive:
		{
			outValue = ent->StateMachineAttr().m_NearestEnemy != nullptr;
			return true;
		}
		case EConditionParameter::EEnnemyDistance:
		{
			if (ent->StateMachineAttr().m_NearestEnemy == nullptr)
			{
				outValue = 0x7F800000; // inf
				return false;
			}
			assert(ent->StateMachineAttr().m_NearestEnemy->IsActive()); // otherwise means that PreUpdate went wrong
			const glm::vec3		&enemyPosition = ent->StateMachineAttr().m_NearestEnemy->Position();
			const glm::vec3		&myPosition = ent->Position();
			outValue = glm::length(enemyPosition - myPosition);
			return true;
		}
		case EConditionParameter::EFriendDistance:
		{
			if (ent->StateMachineAttr().m_NearestFriend == nullptr)
			{
				outValue = 0x7F800000; // inf
				return false;
			}
			assert(ent->StateMachineAttr().m_NearestFriend->IsActive()); // otherwise means that PreUpdate went wrong
			const glm::vec3		&friendPosition = ent->StateMachineAttr().m_NearestFriend->Position();
			const glm::vec3		&myPosition = ent->Position();
			outValue = glm::length(friendPosition - myPosition);
			return true;
		}
		case EConditionParameter::EDistanceFromMyFlag:
		{
			GridEntity			*entity = scene->EntityThatPosessFlag(ent->Team());
			if (entity != nullptr)
				outValue = glm::length(entity->Position() - ent->Position());
			else
			{
				GridEntity			*flag = scene->Flag(ent->Team());
				outValue = glm::length(flag->Position() - ent->Position());
			}
			return true;
		}
		case EConditionParameter::EDistanceFromEnemyFlag:
		{
			GridEntity			*entity = scene->EntityThatPosessFlag(ent->Team() == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION);
			if (entity != nullptr)
				outValue = glm::length(entity->Position() - ent->Position());
			else
			{
				GridEntity			*flag = scene->Flag(ent->Team());
				outValue = glm::length(flag->Position() - ent->Position());
			}
			return true;
		}
		case EConditionParameter::ENearFriendCount:
		{
			outValue = ent->StateMachineAttr().m_FriendsNextToMe;
			return true;
		}
		case EConditionParameter::EHasFlag:
		{
			outValue = scene->EntityThatPosessFlag(ent->Team()) == ent;
			return true;
		}
		case EConditionParameter::ETeamHasFlag:
		{
			outValue = scene->EntityThatPosessFlag(ent->Team()) != nullptr;
			return true;
		}
		case EConditionParameter::EEnemyTeamHasFlag:
		{
			outValue = scene->EntityThatPosessFlag(ent->Team() == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION) != nullptr;
			return true;
		}
		default: assert(false); break;
		}
		return false;
		outValue = 0;
	}
	//----------------------------------------------------------
}
