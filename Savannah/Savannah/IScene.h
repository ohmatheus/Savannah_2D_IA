#pragma once

#include "IGameController.h"

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

	virtual void				OnSceneStart() = 0;
	virtual IScene				*Clone() = 0;
	virtual void				PreUpdate(float dt);
	virtual void				Update(float dt);
	IEntity						*GetEntity(const std::string &name);
	virtual void				Render(RenderSystem *renderSystem);
	const std::vector<IEntity*>	&Entities() { return m_Entities; }
	virtual void				SetParameters(const SGameParameters &params) { m_Parameters = params; }
	const SGameParameters		&Parameters() { return m_Parameters; }

protected:
	std::vector<IEntity*>	m_Entities;
	SGameParameters			m_Parameters;
};

//----------------------------------------------------------
