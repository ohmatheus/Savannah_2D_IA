#include "stdafx.h"

#include "IEntity.h"

//----------------------------------------------------------

IEntity::IEntity(const std::string &name)
{
	m_ShaderName = "DefaultShader";
	m_MeshName = "Triangle";
	m_Color = glm::vec4(1.f, 0.f, 1.f, 1.f);

	m_Position = glm::vec3(0.f);
	m_Rotation = glm::vec3(0.f);
	m_Scale = glm::vec3(1.f);

	m_Yaw = 0.f;
	m_Pitch = 0.f;
	m_Roll = 0.f;
}

//----------------------------------------------------------

IEntity::~IEntity()
{}

//----------------------------------------------------------

glm::mat4	IEntity::ModelMatrix()
{
	glm::mat4 result = glm::mat4(1.f);

	result = glm::translate(result, m_Position);
	result = glm::rotate(result, glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	result = glm::scale(result, m_Scale);
	// scale
	return result;
}

//----------------------------------------------------------
