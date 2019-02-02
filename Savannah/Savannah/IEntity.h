#pragma once

#include <memory>
#include <string>
#include <vector>

//----------------------------------------------------------

class RenderSystem;
class Behaviour; // TODO

//----------------------------------------------------------

class IEntity
{
public:
	IEntity(const std::string &name, bool isActive = true);
	virtual ~IEntity();
	IEntity(const IEntity &from);

	virtual	IEntity			*Clone() = 0;
	virtual void			Update(float dt) = 0;
	virtual void			Render(RenderSystem *renderSystem) = 0;

	glm::mat4				ModelMatrix(); // copy

	void					SetPosition(const glm::vec3 &position) { m_Position = position; }
	void					SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
	void					SetScale(const glm::vec3 &scale) { m_Scale = scale; }
	void					SetScale(float globalScale) { SetScale(glm::vec3(globalScale)); }
	void					SetColor(const glm::vec4 &color) { m_Color = color; }

	const glm::vec3			&Position() { return m_Position; }
	const glm::vec3			&Rotation() { return m_Rotation; }
	const glm::vec3			&Scale() { return m_Scale; }
	const glm::vec4			&Color() { return m_Color; }

	float					&Pitch() { return m_Pitch; }
	float					&Yaw() { return m_Yaw; }
	float					&Roll() { return m_Roll; }

	void					SetShaderName(const std::string &name) { m_ShaderName = name; }
	void					SetMeshName(const std::string &name) { m_MeshName = name; }

	void					AddChild(IEntity *ent);
	IEntity					*Parent() { return m_Parent; }

	bool					IsActive() { return m_IsActive; }
	void					SetActive(bool active) { m_IsActive = active; }
	virtual void			Die();

	const std::string		&Name() { return m_Name; }
	IEntity					*GetChild(const std::string &name);

protected:
	bool					m_IsActive;
	bool					m_HasFlag = false;

	float					m_Pitch;
	float					m_Yaw;
	float					m_Roll;

	glm::vec3				m_Position;
	glm::vec3				m_Rotation;
	glm::vec3				m_Scale;
	glm::vec4				m_Color;
	std::string				m_ShaderName; // TODO replace by an ID
	std::string				m_MeshName; // TODO replace by an ID
	std::string				m_Name;
	IEntity					*m_Parent = nullptr;
	std::vector<IEntity*>	m_Children;
	//Behaviour	*m_Behaviour; // TODO
};

//----------------------------------------------------------
