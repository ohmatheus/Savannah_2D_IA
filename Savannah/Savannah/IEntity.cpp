#include "stdafx.h"

#include "IEntity.h"

//----------------------------------------------------------

IEntity::IEntity(const std::string &name)
{
	m_ShaderName = "DefaultShader";
	m_MeshName = "Triangle";

	m_Position = glm::vec3(0.f);
	m_Rotation = glm::vec3(0.f);
	m_Scale = glm::vec3(0.f);
}

//----------------------------------------------------------

IEntity::~IEntity()
{}

//----------------------------------------------------------

glm::mat4	IEntity::ModelMatrix()
{
	glm::mat4 result = glm::mat4(1.f);

	result = glm::translate(result, m_Position);
	// rotatee
	// scale
	return result;
}

//----------------------------------------------------------
