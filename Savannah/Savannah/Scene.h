#pragma once

#include <vector>

//----------------------------------------------------------

class	IEntity;
class	RenderSystem;

//----------------------------------------------------------

class Scene
{

public:
	Scene();
	virtual ~Scene();

	// add copy construct

	virtual void		Update(float dt);
	virtual void		Render(RenderSystem *renderSystem);

protected:
	void		_PopulateDefaultScene();

	std::vector<IEntity*>	m_Entities;
};

//----------------------------------------------------------
