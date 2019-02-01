#include "stdafx.h"

#include "Conditions.inl"
#include "GridEntity.h"
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

	bool		CombineCondition::Test(GridScene *sce, GridEntity *ent)
	{
		switch (m_LogicalCondition)
		{
		case ELogicalCondition::And:
			return m_FirstCondition->Test(sce, ent) && m_SecondCondition->Test(sce, ent);
		case ELogicalCondition::Or:
			return m_FirstCondition->Test(sce, ent) || m_SecondCondition->Test(sce, ent);
		default: assert(false); break;
		}
		return false;
	}
}
//----------------------------------------------------------
