#include "stdafx.h"

#include "IScene.h"
#include "IEntity.h"
#include "SimpleEntity.h"

//----------------------------------------------------------

IScene::IScene()
{
	// scene name
	_PopulateDefaultScene();
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

void		IScene::_PopulateDefaultScene()
{
	{
		SimpleEntity *entity = new SimpleEntity("Green Triangle");
		entity->SetColor(glm::vec4(0.f, 1.f, 0.f, 1.f));
		entity->SetMeshName("Triangle");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(0.f, 0.f, 0.f));
		m_Entities.push_back(entity);
	}
	SimpleEntity *planeTest = new SimpleEntity("Plane");
	planeTest->SetColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
	planeTest->SetMeshName("Rectangle");
	planeTest->SetShaderName("DefaultShader");
	planeTest->SetPosition(glm::vec3(2.f, 0.f, 0.f));
	m_Entities.push_back(planeTest);
	{
		SimpleEntity *entity = new SimpleEntity("toto");
		entity->SetColor(glm::vec4(0.f, 1.f, 1.f, 1.f));
		entity->SetMeshName("Triangle");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(-2.f, 0.f, 0.f));
		m_Entities.push_back(entity);
	}
	{
	}
}

//----------------------------------------------------------
