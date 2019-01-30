#include "stdafx.h"

#include "Conditions.h"

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
//		CombineCondition
//----------------------------------------------------------

	CombineCondition::CombineCondition(ICondition *conditionA, ELogicalCondition logicalCondition, ICondition *conditionB)
	:	Super()
	,	m_FirstCondition(conditionA)
	,	m_SecondCondition(conditionB)
	,	m_LogicalCondition(logicalCondition)
	{

	}

//----------------------------------------------------------

	CombineCondition::~CombineCondition()
	{}

//----------------------------------------------------------

	bool		CombineCondition::Test(SimpleEntity *ent)
	{
		return true;
	}
}
//----------------------------------------------------------
