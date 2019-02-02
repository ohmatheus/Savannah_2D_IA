#include "stdafx.h"

#include "Spawner.h"
#include "GridEntity.h"

#include <math.h>

//----------------------------------------------------------

GridSpawner::GridSpawner(GridScene::ETeam team, const std::string &name, int poolSize)
:	Super(name, team, true)
,	m_PoolSize(poolSize)
{
	m_SpawnTimer = 0.f;
}

//----------------------------------------------------------

GridSpawner::~GridSpawner()
{
}

//----------------------------------------------------------

GridSpawner::GridSpawner(const GridSpawner &spawner)
:	Super(spawner)
{
	//m_Scene = ???;

	m_PoolSize = spawner.m_PoolSize;
	//m_EntityManager; // created at OnSceneStart
	m_SpawnTimer = spawner.m_SpawnTimer;
	m_SpawnPerSecond = spawner.m_SpawnPerSecond;
	m_Dps = spawner.m_Dps;
}

//----------------------------------------------------------

GridSpawner				*GridSpawner::Clone()
{
	return new GridSpawner(*this);
}

//----------------------------------------------------------

void	GridSpawner::OnSceneStart(GridScene *scene)
{
	m_Scene = scene;

	m_EntityManager.reserve(m_PoolSize);

	const float xSubdiv = std::ceil(std::sqrtf(m_PoolSize));
	const float ySubdiv = std::trunc(std::sqrtf(m_PoolSize));

	const float		cellSize = 1.5f;
	const glm::vec3 &position = Position();
	const float		xOffset = cellSize * xSubdiv * 0.5f;
	const float		yOffset = cellSize * ySubdiv * 0.5f;

	for (int i = 0; i <= xSubdiv; i++)
	{
		for (int j = 0; j <= ySubdiv; j++)
		{
			GridEntity *entity = m_Scene->AddEntity(m_Team, glm::vec3(position.x - xOffset + i * cellSize, position.y + yOffset - j * cellSize, 0.f), true);
			m_EntityManager.push_back(entity);
			entity->SetDps(m_Dps);
		}
	}
}

//----------------------------------------------------------

void	GridSpawner::Update(float dt)
{
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
				m_EntityManager[i]->SetHealth(10.f);
				m_EntityManager[i]->SetPosition(m_Position);
				m_EntityManager[i]->Roll() = 0.f;
				m_EntityManager[i]->ChangeStateNode(m_Scene->GetStateMachineRoot(m_Team));
				break;
			}
		}
	}
}

//----------------------------------------------------------
