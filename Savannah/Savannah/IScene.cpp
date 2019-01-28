#include "stdafx.h"

#include "IScene.h"
#include "IEntity.h"
#include "SimpleEntity.h"

//----------------------------------------------------------

IScene::IScene()
{
}

//----------------------------------------------------------

IScene::~IScene()
{
	for (int i = 0; i < m_Entities.size(); ++i)
		delete m_Entities[i];
	m_Entities.clear();
}

//----------------------------------------------------------

void		IScene::Update(float dt)
{
	for (int i = 0; i < m_Entities.size(); ++i)
		m_Entities[i]->Update(dt);
}

//----------------------------------------------------------

void		IScene::Render(RenderSystem *renderSystem)
{
	for (int i = 0; i < m_Entities.size(); ++i)
		m_Entities[i]->Render(renderSystem);
}

//----------------------------------------------------------
