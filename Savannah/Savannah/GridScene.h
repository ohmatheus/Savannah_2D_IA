#pragma once

#include "IScene.h"

//----------------------------------------------------------

class	Game;
class	SimpleEntity;
class	GridSpawner;
class	GridFlagEntity;

namespace StateMachine
{
	class	StateMachineManager;
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

	enum ETeam
	{
		LION		= 0,
		ANTELOPE	= 1,
		_MAX		= 2
	};

	IEntity								*GetFlagsEntity(ETeam team);
	SimpleEntity						*AddEntity(ETeam type, const glm::vec3 &position, bool isActive = true);

	SimpleEntity						*Flag(ETeam teamFlag) { return m_Flags[teamFlag]; }

protected:
	void								_CreateScene();
	void								_GenerateAndAddGrid(int xSubdiv, int ySubdiv); // call rendersystem to generate mesh

	Game								*m_Game;
	SimpleEntity						*m_GridEntity;

	StateMachine::StateMachineManager	*m_AntelopeStateMachine = nullptr;
	StateMachine::StateMachineManager	*m_LionStateMachine = nullptr;

	GridSpawner							*m_Spawners[ETeam::_MAX];
	SimpleEntity						*m_Flags[ETeam::_MAX];
	//glm::vec4			m_AntelopeColor;
	//glm::vec4			m_LionColor;
};

//----------------------------------------------------------