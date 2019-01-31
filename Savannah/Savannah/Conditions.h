#pragma once

#include "StateMachineManager.h"

//----------------------------------------------------------

class	SimpleEntity;
class	GridScene;

//----------------------------------------------------------

namespace StateMachine
{
	class ICondition : public StateMachineObject
	{
		using Self = ICondition;
	public:
		ICondition();
		virtual ~ICondition();

		virtual bool	Test(SimpleEntity *ent) = 0;
	};

	//----------------------------------------------------------

	template <typename _Type>
	class ValueCondition : public ICondition
	{
		using Self = ValueCondition;
		using Super = ICondition;
	public:
		ValueCondition() = delete;
		ValueCondition(const ValueCondition&) = delete;
		ValueCondition operator=(const ValueCondition&) = delete;
		ValueCondition(EConditionParameter, EConditionOperation, const _Type &controlValue);
		virtual ~ValueCondition();

		virtual bool		Test(SimpleEntity *ent) override;

	private:
		bool				_GetValueToTest(EConditionParameter arg, GridScene *scene, SimpleEntity *ent, _Type &outValue);

		_Type				m_ControlValue;
		EConditionParameter	m_ParameterToTest;
		EConditionOperation	m_TestOperation;
	};

	//----------------------------------------------------------

	class CombineCondition : public ICondition
	{
		using Self = CombineCondition;
		using Super = ICondition;
	public:
		CombineCondition() = delete;
		CombineCondition(const CombineCondition&) = delete;
		CombineCondition operator=(const CombineCondition&) = delete;
		CombineCondition(ICondition *conditionA, ELogicalCondition logicalCondition, ICondition *conditionB);
		virtual ~CombineCondition();

		virtual bool		Test(SimpleEntity *ent) override;
	private:
		ICondition			*m_FirstCondition;
		ICondition			*m_SecondCondition;
		ELogicalCondition	m_LogicalCondition;
	};
}

//----------------------------------------------------------
