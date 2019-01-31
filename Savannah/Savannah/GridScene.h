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
		_NONE		= 2
	};

	enum ESteeringBehaviour
	{
		ESeek,
		EFlee,
		EAvoid,
		EArrive
	};

	IEntity								*GetFlagsEntity(ETeam team);
	GridEntity							*AddEntity(ETeam type, const glm::vec3 &position, bool isActive = true, bool manageByScene = true);

	GridEntity							*Flag(ETeam teamFlag) { return m_Flags[teamFlag]; }

	virtual void						PreUpdate() override;

protected:
	void								_CreateScene();
	void								_GenerateAndAddGrid(int xSubdiv, int ySubdiv); // call rendersystem to generate mesh

	Game								*m_Game;
	GridEntity							*m_GridEntity;

	StateMachine::StateMachineManager	*m_AntelopeStateMachine = nullptr;
	StateMachine::StateMachineManager	*m_LionStateMachine = nullptr;

	GridSpawner							*m_Spawners[ETeam::_NONE];
	GridEntity							*m_Flags[ETeam::_NONE];



	//glm::vec4			m_AntelopeColor;
	//glm::vec4			m_LionColor;
};

//----------------------------------------------------------