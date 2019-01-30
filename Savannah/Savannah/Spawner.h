#pragma once

#include "GridScene.h"
#include "IEntity.h"

//----------------------------------------------------------



//----------------------------------------------------------

class GridSpawner : public IEntity
{
	using Super = IEntity;
	using Self = GridSpawner;
public:
	GridSpawner(GridScene::ETeam team, GridScene *scence, int poolSize);
	virtual		~GridSpawner();

	void			OnSceneStart();
	virtual	void	Update(float dt) override;

protected:
	GridScene::ETeam			m_Team;
	GridScene					*m_Scene;
	int							m_PoolSize = 10;
	std::vector<SimpleEntity*>	m_EntityManager; // juste manage life and spawn, but memory is still handled by the scene
	float						m_SpawnTimer;
	float						m_SpawnPerSecond = 1.f;
};

//----------------------------------------------------------