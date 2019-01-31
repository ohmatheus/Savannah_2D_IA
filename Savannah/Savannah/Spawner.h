#pragma once

#include "GridScene.h"
#include "GridEntity.h"

//----------------------------------------------------------



//----------------------------------------------------------

class GridSpawner : public GridEntity
{
	using Super = GridEntity;
	using Self = GridSpawner;
public:
	GridSpawner(GridScene::ETeam team, GridScene *scence, int poolSize);
	virtual		~GridSpawner();

	void			OnSceneStart();
	virtual	void	Update(float dt) override;

protected:
	GridScene					*m_Scene;
	int							m_PoolSize = 10;
	std::vector<GridEntity*>	m_EntityManager; // juste manage life and spawn, but memory is still handled by the scene
	float						m_SpawnTimer;
	float						m_SpawnPerSecond = 1.f;
};

//----------------------------------------------------------