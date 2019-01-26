#pragma once
#pragma once

#include "SimpleEntity.h"

//----------------------------------------------------------

class GridEntity : public SimpleEntity
{
	using Super = SimpleEntity;
	using Self = GridEntity;
public:
	GridEntity(const std::string &name);
	virtual ~GridEntity();
protected:
};

//----------------------------------------------------------