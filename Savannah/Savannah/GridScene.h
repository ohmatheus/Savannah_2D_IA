#pragma once

#include "IScene.h"

//----------------------------------------------------------

class	Game;
class	GridEntity;
class	GridSpawner;
class	GridFlagEntity;

namespace StateMachine
{
	class	StateMachineManager;
	class	StateNode;
}

//----------------------------------------------------------

// 2 dimensional grid scene
class GridScene : public IScene
{
	using Super = IScene;
	using Self = GridScene;
public:
	GridScene(Game *game);
	virtual ~GridScene();

	GridScene(const GridScene &scene);

	enum ETeam
	{
		LION		= 0,
		ANTELOPE	= 1,
		_NONE		= 2
	};

	virtual IScene						*Clone();
	virtual void						OnSceneStart() override;
	IEntity								*GetFlagsEntity(ETeam team);
	GridEntity							*AddEntityToGrid(ETeam type, const glm::vec3 &position, bool isActive = true);
	GridEntity							*Flag(ETeam teamFlag) { return m_Flags[teamFlag]; }
	GridEntity							*EntityThatPosessFlag(ETeam teamFlag);
	GridSpawner							*Spawner(ETeam teamFlag) { return m_Spawners[teamFlag]; }
	virtual void						PreUpdate(float dt) override;
	StateMachine::StateNode				*GetStateMachineRoot(ETeam team);
	virtual	void						SetParameters(const SGameParameters &params) override;

protected:
	void								_CreateScene();
	void								_GenerateAndAddGrid(int xSubdiv, int ySubdiv); // call rendersystem to generate mesh
	void								_OnEntityGetFlag(GridEntity	*ent);
	void								_OnFlagLost(ETeam team);

	Game								*m_Game;
	GridEntity							*m_GridEntity;

	StateMachine::StateMachineManager	*m_AntelopeStateMachine = nullptr;
	StateMachine::StateMachineManager	*m_LionStateMachine = nullptr;

	GridSpawner							*m_Spawners[ETeam::_NONE];
	GridEntity							*m_Flags[ETeam::_NONE];
	float								m_FlagCollisionRadius;

	GridEntity							*m_LionPosessFlag = nullptr;
	GridEntity							*m_AntelopePosessFlag = nullptr;
};

//----------------------------------------------------------
