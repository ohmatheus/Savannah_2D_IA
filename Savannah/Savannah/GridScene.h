#pragma once

#include "IScene.h"

//----------------------------------------------------------

class	Game;
class	SimpleEntity;
class	GridFlagEntity;

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
		ANTELOPE	= 1
	};

protected:
	void				_CreateScene();
	void				_GenerateAndAddGrid(int xSubdiv, int ySubdiv); // call rendersystem to generate mesh

	Game				*m_Game;
	SimpleEntity		*m_GridEntity;
	//GridFlagEntity		m_Flags[2];

};

//----------------------------------------------------------