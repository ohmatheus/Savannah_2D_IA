#pragma once
#pragma once

#include "IEntity.h"

//----------------------------------------------------------

class SOAEntity : public IEntity
{
	using Super = IEntity;
	using Self = SOAEntity;
public:
	SOAEntity(const std::string &name);
	virtual ~SOAEntity();
protected:
};

//----------------------------------------------------------