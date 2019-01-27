#include "stdafx.h"

#include "Scene.h"
#include "IEntity.h"
#include "SimpleEntity.h"

//----------------------------------------------------------

Scene::Scene()
{
	// scene name
	_PopulateDefaultScene();
}

//----------------------------------------------------------

Scene::~Scene()
{
	for (int i = 0; i < m_Entities.size(); ++i)
		delete m_Entities[i];
	m_Entities.clear();
}

//----------------------------------------------------------

void		Scene::Update(float dt)
{
	for (int i = 0; i < m_Entities.size(); ++i)
		m_Entities[i]->Update(dt);
}

//----------------------------------------------------------

void		Scene::Render(RenderSystem *renderSystem)
{
	for (int i = 0; i < m_Entities.size(); ++i)
		m_Entities[i]->Render(renderSystem);
}

//----------------------------------------------------------

void		Scene::_PopulateDefaultScene()
{
	{
		SimpleEntity *entity = new SimpleEntity("Green Triangle");
		entity->SetColor(glm::vec4(0.f, 1.f, 0.f, 1.f));
		entity->SetMeshName("Triangle");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(0.f, 0.f, 0.f));
		m_Entities.push_back(entity);
	}
	{
		SimpleEntity *entity = new SimpleEntity("Plane");
		entity->SetColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
		entity->SetMeshName("Rectangle");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(2.f, 0.f, 0.f));
		m_Entities.push_back(entity);
	}
	{
		SimpleEntity *entity = new SimpleEntity("Grid");
		entity->SetColor(glm::vec4(1.f, 0.f, 1.f, 1.f));
		entity->SetMeshName("Grid");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(0.f, 0.f, 0.f));
		entity->SetScale(10.f);
		m_Entities.push_back(entity);
	}
}

//----------------------------------------------------------
