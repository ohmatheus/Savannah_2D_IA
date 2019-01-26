#pragma once

#include "IEntity.h"

//----------------------------------------------------------

class SimpleEntity : public IEntity
{
	using Super = IEntity;
	using Self = SimpleEntity;
public:
	SimpleEntity(const std::string &name);
	virtual ~SimpleEntity();

	virtual void		Update(float dt) override;
	virtual void		Render(RenderSystem *renderSystem) override;

protected:
};

//----------------------------------------------------------