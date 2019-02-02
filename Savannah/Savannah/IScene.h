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
	IScene(const IScene &);

	virtual void		OnSceneStart() = 0;
	virtual IScene		*Clone() = 0;
	virtual void		PreUpdate(float dt);
	virtual void		Update(float dt);
	virtual void		Render(RenderSystem *renderSystem);

	IEntity				*GetEntity(const std::string &name);

	const std::vector<IEntity*>	&Entities() { return m_Entities; }

protected:
	std::vector<IEntity*>	m_Entities;
};

//----------------------------------------------------------
