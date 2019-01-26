#pragma once

#include <memory>
#include <string>

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

	glm::mat4				ModelMatrix();

	void					SetPosition(const glm::vec3 &position) { m_Position = position; }
	void					SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
	void					SetScale(const glm::vec3 &scale) { m_Scale = scale; }
	void					SetColor(const glm::vec4 &color) { m_Color = color; }

	glm::vec3				Position() { return m_Position; }
	glm::vec3				Rotation() { return m_Rotation; }
	glm::vec3				Scale() { return m_Scale; }
	glm::vec4				Color() { return m_Color; }

	void					SetShaderName(const std::string &name) { m_ShaderName; }
	void					SetMeshName(const std::string &name) { m_MeshName; }

protected:
	float					m_Yaw;
	float					m_Pitch;
	float					m_Roll;

	glm::vec3				m_Position;
	glm::vec3				m_Rotation;
	glm::vec3				m_Scale;
	glm::vec4				m_Color;
	std::string				m_ShaderName; // TODO replace by an ID
	std::string				m_MeshName; // TODO replace by an ID
	std::string				m_Name;
	//Behaviour	*m_Behaviour; // TODO
};

//----------------------------------------------------------
