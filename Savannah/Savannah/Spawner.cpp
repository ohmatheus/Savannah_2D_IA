#include "stdafx.h"

#include "Spawner.h"
#include "GridEntity.h"

//----------------------------------------------------------

GridSpawner::GridSpawner(GridScene::ETeam team, GridScene *scene, int poolSize)
:	Super("", team, true)
,	m_Scene(scene)
,	m_PoolSize(poolSize)
{
	OnSceneStart();
	m_SpawnTimer = 0.f;
}

//----------------------------------------------------------

GridSpawner::~GridSpawner()
{
}

//----------------------------------------------------------

void	GridSpawner::OnSceneStart()
{
	m_EntityManager.reserve(m_PoolSize);
	for (int i = 0; i < m_PoolSize; ++i)
	{
		m_EntityManager.push_back(m_Scene->AddEntity(m_Team, glm::vec3(0.f, 0.f, 0.f), false));
	}
}

//----------------------------------------------------------

void	GridSpawner::Update(float dt)
{
	//Super::Update(dt);

	// manage spawn with a timer
	const float ratio = m_SpawnPerSecond / 1.f;
	m_SpawnTimer += dt;

	if (m_SpawnTimer >= ratio)
	{
		m_SpawnTimer = m_SpawnTimer - ratio;

		// Find an inactive entity to 'spawn'
		for (int i = 0; i < m_PoolSize; ++i)
		{
			if (!m_EntityManager[i]->IsActive())
			{
				m_EntityManager[i]->SetActive(true);
				m_EntityManager[i]->SetPosition(m_Position);
				break;
			}
		}
	}
}

//----------------------------------------------------------
