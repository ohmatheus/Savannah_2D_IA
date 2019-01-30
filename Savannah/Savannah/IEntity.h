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
	IEntity(const std::string &name);
	virtual ~IEntity();

	virtual void			Update(float dt) = 0;
	virtual void			Render(RenderSystem *renderSystem) = 0;

	const glm::mat4			&ModelMatrix();

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

protected:
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
