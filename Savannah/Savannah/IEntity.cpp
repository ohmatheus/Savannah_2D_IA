#include "stdafx.h"

#include "IEntity.h"

//----------------------------------------------------------

IEntity::IEntity()
{
}

//----------------------------------------------------------

IEntity::~IEntity()
{}

//----------------------------------------------------------

glm::mat4	IEntity::ModelMatrix()
{
	glm::mat4 result = glm::mat4(1.f);

	result = glm::translate(result, m_Position);
	// rotate
	// scale
	return result;
}

//----------------------------------------------------------
