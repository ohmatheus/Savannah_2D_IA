#pragma once

#include "GridScene.h"
#include "GridEntity.h"

//----------------------------------------------------------

class GridSpawner : public GridEntity
{
	using Super = GridEntity;
	using Self = GridSpawner;
public:
	GridSpawner(GridScene::ETeam team, const std::string &name, int poolSize);
	virtual		~GridSpawner();
	GridSpawner(const GridSpawner &spawner);

	virtual GridSpawner				*Clone() override;
	void							OnSceneStart(GridScene *scene);
	virtual	void					Update(float dt) override;
	const std::vector<GridEntity*>	&Entities() { return m_EntityManager; }
	void							SetDps(float dps) { m_Dps = dps; }
	void							SetPoolSize(float poolSize) { m_PoolSize = poolSize; }

protected:
	GridScene						*m_Scene;
	int								m_PoolSize = 10;
	std::vector<GridEntity*>		m_EntityManager; // juste manage life and spawn, but memory is still handled by the scene
	float							m_SpawnTimer;
	float							m_SpawnPerSecond = 1.f;
	float							m_Dps = 100.f;
};

//----------------------------------------------------------