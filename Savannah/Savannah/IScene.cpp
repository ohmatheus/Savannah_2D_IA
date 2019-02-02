#include "stdafx.h"

#include "IScene.h"
#include "IEntity.h"
#include "GridEntity.h"

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

IScene::IScene(const IScene &from)
{
	for (int i = 0; i < from.m_Entities.size(); i++)
		m_Entities.push_back(from.m_Entities[i]->Clone());
}

//----------------------------------------------------------

void		IScene::PreUpdate(float dt)
{
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

IEntity		*IScene::GetEntity(const std::string &name)
{
	for (int i = 0; i < m_Entities.size(); ++i)
	{
		if (m_Entities[i]->Name() == name)
			return m_Entities[i];
		else
		{
			IEntity	*found = m_Entities[i]->GetChild(name);
			if (found != nullptr)
				return found;
		}
	}
	return nullptr;
}

//----------------------------------------------------------
