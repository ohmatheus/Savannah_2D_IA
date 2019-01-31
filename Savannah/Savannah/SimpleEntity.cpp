#include "stdafx.h"

#include "SimpleEntity.h"
#include "StateNode.h"
#include "Game.h"

//----------------------------------------------------------

SimpleEntity::SimpleEntity(const std::string &name, GridScene::ETeam team, bool isActive)
:	Super(name, isActive)
,	m_Team(team)
{
}

//----------------------------------------------------------

SimpleEntity::~SimpleEntity()
{}

//----------------------------------------------------------

void		SimpleEntity::Update(float dt)
{
	if (!m_IsActive)
		return;
	if (m_CurrentStateNode != nullptr)
		m_CurrentStateNode->UpdateEntity(this, dt);
}

//----------------------------------------------------------
