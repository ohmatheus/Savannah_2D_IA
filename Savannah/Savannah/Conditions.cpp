#include "stdafx.h"

#include "Conditions.h"
#include "SimpleEntity.h"
#include "GridScene.h"

#include <vector>

//----------------------------------------------------------

namespace StateMachine
{
	ICondition::ICondition()
	{}

	ICondition::~ICondition()
	{}

//----------------------------------------------------------
//		ValueCondition
//----------------------------------------------------------

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
	bool		ValueCondition<_Type>::Test(SimpleEntity *ent)
	{
		return true;
	}

	//----------------------------------------------------------

	template <typename _Type>
	bool	ValueCondition<_Type>::_GetValueToTest(EConditionParameter arg, GridScene *scene, SimpleEntity *ent, _Type &outValue)
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
			const std::vector<IEntity*>	entities = scene->Entities();
			for (int i = 0; i < entities.size(); ++i)
			{
				SimpleEntity *gridEnt = dynamic_cast<SimpleEntity*>(entities[i]);
				if (gridEnt != nullptr)
				{
					if (gridEnt->Team() == ent->Team())
					{
						outValue = true;
						return true;
					}
				}
			}
			break;
		}
		case EConditionParameter::EEnnemyDistance:
		{
			const std::vector<IEntity*>	entities = scene->Entities();
			for (int i = 0; i < entities.size(); ++i)
			{
				SimpleEntity *gridEnt = dynamic_cast<SimpleEntity*>(entities[i]);
				if (gridEnt != nullptr)
				{
					if (gridEnt->Team() != ent->Team())
					{
						outValue = glm::length(gridEnt->Position() - ent->Position());
						return true;
					}
				}
			}
			break;
		}
		case EConditionParameter::EFriendDistance:
		{
			const std::vector<IEntity*>	entities = scene->Entities();
			for (int i = 0; i < entities.size(); ++i)
			{
				SimpleEntity *gridEnt = dynamic_cast<SimpleEntity*>(entities[i]);
				if (gridEnt != nullptr)
				{
					if (gridEnt->Team() == ent->Team())
					{
						outValue = glm::length(gridEnt->Position() - ent->Position());
						return true;
					}
				}
			}
			break;
		}
		case EConditionParameter::EMyFlagDistance:
		{
			SimpleEntity *flag = scene->Flag(ent->Team());
			outValue = glm::length(flag->Position() - ent->Position());
			return true;
			break;
		}
		case EConditionParameter::EEnemyFlagDistance:
		{
			SimpleEntity *flag = scene->Flag(ent->Team());
			outValue = glm::length(flag->Position() - ent->Position());
			return true;
			break;
		}
		default: assert(false); break;
		}
		return false;
		outValue = 0;
	}


//----------------------------------------------------------
//		CombineCondition
//----------------------------------------------------------

	CombineCondition::CombineCondition(ICondition *conditionA, ELogicalCondition logicalCondition, ICondition *conditionB)
	:	Super()
	,	m_FirstCondition(conditionA)
	,	m_SecondCondition(conditionB)
	,	m_LogicalCondition(logicalCondition)
	{}

//----------------------------------------------------------

	CombineCondition::~CombineCondition()
	{}

//----------------------------------------------------------

	bool		CombineCondition::Test(SimpleEntity *ent)
	{
		switch (m_LogicalCondition)
		{
		case ELogicalCondition::And:
			return m_FirstCondition->Test(ent) && m_SecondCondition->Test(ent);
		case ELogicalCondition::Or:
			return m_FirstCondition->Test(ent) || m_SecondCondition->Test(ent);
		default: assert(false); break;
		}
		return false;
	}
}
//----------------------------------------------------------
