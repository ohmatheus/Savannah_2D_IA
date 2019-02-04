#include "stdafx.h"

#include "Spawner.h"
#include "GridEntity.h"

#include "IGameController.h"

#include <math.h>

//----------------------------------------------------------

GridSpawner::GridSpawner(GridScene::ETeam team, const std::string &name, int poolSize)
:	Super(name, team, true)
,	m_PoolSize(poolSize)
{
	m_SpawnTimer = 0.f;
	m_Scene = nullptr;
}

//----------------------------------------------------------

GridSpawner::~GridSpawner()
{
}

//----------------------------------------------------------

GridSpawner::GridSpawner(const GridSpawner &spawner)
:	Super(spawner)
{
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

	const int		xSubdiv = std::ceil(std::sqrtf(m_PoolSize));
	const int		ySubdiv = std::trunc(std::sqrtf(m_PoolSize));

	const float		cellSize = 1.5f;
	const glm::vec3 &position = Position();
	const float		xOffset = cellSize * xSubdiv * 0.5f;
	const float		yOffset = cellSize * ySubdiv * 0.5f;

	for (int i = 0; i < xSubdiv; i++)
	{
		for (int j = 0; j < ySubdiv + 1 && m_EntityManager.size() < m_PoolSize; j++)
		{
			GridEntity *entity = m_Scene->AddEntityToGrid(m_Team, glm::vec3(position.x - xOffset + i * cellSize, position.y + yOffset - j * cellSize, 0.f), true);
			m_EntityManager.push_back(entity);
			if (m_Team == GridScene::LION)
			{
				entity->SetMovementSpeed(scene->Parameters().m_LionVelocity);
				entity->SetRotationSpeed(scene->Parameters().m_LionRotationSpeed);
				entity->SetDps(scene->Parameters().m_LionDPS);
				entity->SetHealth(scene->Parameters().m_LionInitialHealth);
			}
			else
			{
				entity->SetMovementSpeed(scene->Parameters().m_AntelopeVelocity);
				entity->SetRotationSpeed(scene->Parameters().m_AntelopeRotationSpeed);
				entity->SetDps(scene->Parameters().m_AntelopeDPS);
				entity->SetHealth(scene->Parameters().m_AntelopeInitialHealth);
			}
		}
	}
}

//----------------------------------------------------------

void	GridSpawner::Update(float dt)
{
	const float ratio = m_SpawnPerSecond / 1.f;
	m_SpawnTimer += dt;
	Super::Update(dt);

	if (m_SpawnTimer >= ratio)
	{
		m_SpawnTimer = m_SpawnTimer - ratio;

		// Find an inactive entity to 'spawn'
		for (int i = 0; i < m_PoolSize; ++i)
		{
			if (!m_EntityManager[i]->IsActive())
			{
				GridEntity	*entity = m_EntityManager[i];
				assert(entity != nullptr);
				entity->SetActive(true);
				entity->SetPosition(m_Position + glm::vec3(0.f, 0.f, 0.1f));
				entity->Roll() = 0.f;
				entity->ChangeStateNode(m_Scene->GetStateMachineRoot(m_Team));
				if (m_Team == GridScene::LION)
				{
					entity->SetMovementSpeed(m_Scene->Parameters().m_LionVelocity);
					entity->SetRotationSpeed(m_Scene->Parameters().m_LionRotationSpeed);
					entity->SetDps(m_Scene->Parameters().m_LionDPS);
					entity->SetHealth(m_Scene->Parameters().m_LionInitialHealth);
				}
				else
				{
					entity->SetMovementSpeed(m_Scene->Parameters().m_AntelopeVelocity);
					entity->SetRotationSpeed(m_Scene->Parameters().m_AntelopeRotationSpeed);
					entity->SetDps(m_Scene->Parameters().m_AntelopeDPS);
					entity->SetHealth(m_Scene->Parameters().m_AntelopeInitialHealth);
				}
				break;
			}
		}
	}
}

//----------------------------------------------------------
