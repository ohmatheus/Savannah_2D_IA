#pragma once

#include <vector>

//----------------------------------------------------------

class	IEntity;
class	RenderSystem;

//----------------------------------------------------------

class Scene final
{

public:
	Scene();
	~Scene();

	void		Update(float dt);
	void		Render(RenderSystem *renderSystem);

private:
	void		_PopulateDefaultScene();

	std::vector<IEntity*>	m_Entities;
};

//----------------------------------------------------------
