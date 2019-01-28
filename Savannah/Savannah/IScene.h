#pragma once

#include <vector>

//----------------------------------------------------------

class	IEntity;
class	RenderSystem;

//----------------------------------------------------------

class IScene
{
public:
	IScene();
	virtual ~IScene();

	virtual void		Update(float dt);
	virtual void		Render(RenderSystem *renderSystem);

protected:
	std::vector<IEntity*>	m_Entities;
};

//----------------------------------------------------------
