#include "stdafx.h"

#include "IEntity.h"

//----------------------------------------------------------

IEntity::IEntity(const std::string &name, bool isActive)
:	m_HasFlag(false)
,	m_IsActive(isActive)
,	m_Name(name)
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
{
	for (int i = 0; i < m_Children.size(); i++)
		delete m_Children[i];
}

//----------------------------------------------------------

void	IEntity::Update(float dt)
{
	for (int i = 0; i < m_Children.size(); i++)
		m_Children[i]->Update(dt);
}

//----------------------------------------------------------

void	IEntity::Render(RenderSystem *renderSystem)
{
	for (int i = 0; i < m_Children.size(); i++)
		m_Children[i]->Render(renderSystem);
}

//----------------------------------------------------------

IEntity::IEntity(const IEntity &from)
{
	m_Position = from.m_Position;
	m_Rotation = from.m_Rotation;
	m_Scale = from.m_Scale;
	m_Color = from.m_Color;
	m_ShaderName = from.m_ShaderName;
	m_MeshName = from.m_MeshName;
	m_Name = from.m_Name;

	m_Pitch = from.m_Pitch;
	m_Yaw = from.m_Yaw;
	m_Roll = from.m_Roll;

	for (int i = 0; i < from.m_Children.size(); i++)
	{
		m_Children.push_back(from.m_Children[i]->Clone());
		m_Children[i]->m_Parent = this;
	}
}

//----------------------------------------------------------

glm::mat4	IEntity::ModelMatrix(bool worldspace)
{
	glm::mat4 result = glm::mat4(1.f);

	result = glm::translate(result, m_Position);
	result = glm::rotate(result, glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	result = glm::rotate(result, glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	result = glm::rotate(result, glm::radians(m_Roll), glm::vec3(0.0f, 0.0f, 1.0f));
	result = glm::scale(result, m_Scale);
	
	if (m_Parent != nullptr && worldspace)
		return m_Parent->ModelMatrix(worldspace) * result;
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

IEntity		*IEntity::GetChild(const std::string &name)
{
	for (int i = 0; i < m_Children.size(); ++i)
	{
		if (m_Children[i]->Name() == name)
			return m_Children[i];
		else
		{
			IEntity	*found = m_Children[i]->GetChild(name);
			if (found != nullptr)
				return found;
		}
	}
	return nullptr;
}

//----------------------------------------------------------

void	IEntity::SetParent(IEntity *newParent)
{
	if (m_Parent != nullptr)
		m_Parent->RemoveChild(this);
	m_Parent = nullptr;
	newParent->AddChild(this);
	assert(m_Parent == newParent);
}

//----------------------------------------------------------

bool	IEntity::RemoveChild(IEntity *childToRemove)
{
	for (int i = 0; i < m_Children.size(); ++i)
	{
		if (m_Children[i] == childToRemove)
		{
			m_Children.erase(m_Children.begin() + i);
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------
