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

	virtual void		PreUpdate(float dt);
	virtual void		Update(float dt);
	virtual void		Render(RenderSystem *renderSystem);

	const std::vector<IEntity*>	&Entities() { return m_Entities; }

protected:
	std::vector<IEntity*>	m_Entities;
};

//----------------------------------------------------------
