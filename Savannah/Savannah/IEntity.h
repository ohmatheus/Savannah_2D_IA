#pragma once

//----------------------------------------------------------

class Renderer;
class Behaviour; // TODO

//----------------------------------------------------------

class IEntity
{
public:
	IEntity();
	virtual ~IEntity();

	virtual void	Update() = 0;
	//virtual void	Render();

	glm::mat4		ModelMatrix();

protected:
	glm::vec3	m_Position;
	glm::vec3	m_Rotation;
	glm::vec3	m_Scale;

	Renderer	*m_Renderer;
	//Behaviour	*m_Behaviour; // TODO
};

//----------------------------------------------------------
