#include "stdafx.h"

#include "IEntity.h"

//----------------------------------------------------------

IEntity::IEntity(const std::string &name, bool isActive)
:	m_HasFlag(false)
,	m_IsActive(isActive)
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
	result = glm::rotate(result, glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	result = glm::rotate(result, glm::radians(m_Roll), glm::vec3(0.0f, 0.0f, 1.0f));
	result = glm::scale(result, m_Scale);
	
	if (m_Parent != nullptr)
		return m_Parent->ModelMatrix() * result;
	else
		return result;
}

//----------------------------------------------------------

void	IEntity::AddChild(IEntity *ent)
{
	assert(ent->Parent() == nullptr);
	ent->m_Parent = this;
	m_Children.push_back(ent);
}

//----------------------------------------------------------

void	IEntity::Die()
{
	SetActive(false);
}

//----------------------------------------------------------
