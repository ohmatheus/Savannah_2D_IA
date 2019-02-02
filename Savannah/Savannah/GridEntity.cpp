#include "stdafx.h"

#include "GridEntity.h"
#include "StateNode.h"
#include "RenderSystem.h"
#include "GLShader.h"
#include "MeshData.h"
#include "Game.h"
#include "Steering.h"

//----------------------------------------------------------

GridEntity::GridEntity(const std::string &name, GridScene::ETeam team, bool isActive)
:	Super(name, isActive)
,	m_Team(team)
{
}

//----------------------------------------------------------

GridEntity::~GridEntity()
{}

//----------------------------------------------------------

GridEntity::GridEntity(const GridEntity &from)
:	Super(from)
{
	m_CurrentStateNode = nullptr; // given by the scene at AddEntity

	m_MovementSpeed = from.m_MovementSpeed;
	m_RotationSpeed = from.m_RotationSpeed;
	m_Team = from.m_Team;
	m_Health = from.m_Health;
	m_Dps = from.m_Dps;
}

//----------------------------------------------------------

GridEntity	*GridEntity::Clone()
{
	return new GridEntity(*this);
}

//----------------------------------------------------------

void		GridEntity::Update(float dt)
{
	if (m_IsActive)
	{
		if (m_CurrentStateNode != nullptr)
			m_CurrentStateNode->UpdateEntity(this, dt);
	}
	Super::Update(dt);
}

//----------------------------------------------------------

const glm::vec3		GridEntity::Forward()
{
	const glm::mat4		model = ModelMatrix();
	const glm::vec3		&position = Position();
	glm::vec3			forward = model * glm::vec4(0.f, 1.f, 0.f, 0.f);
	return glm::normalize(forward);
}

//----------------------------------------------------------

void		GridEntity::Render(RenderSystem *renderSystem)
{
	if (!m_IsActive)
		return;
	GLShader			*shader = renderSystem->GetShader(m_ShaderName);
	MeshData			*mesh = renderSystem->GetMesh(m_MeshName);
	const glm::mat4		modelW = ModelMatrix(); // do not recompute each frame for each entity, keep in class and modify directly TODO

	assert(shader != nullptr);
	assert(mesh != nullptr);

	shader->Bind();
	glUniformMatrix4fv(shader->Uniform("model"), 1, GL_FALSE, glm::value_ptr(modelW));
	glUniformMatrix4fv(shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(renderSystem->GetGame()->View()));
	glUniformMatrix4fv(shader->Uniform("proj"), 1, GL_FALSE, glm::value_ptr(renderSystem->GetGame()->Proj()));
	glUniform4fv(shader->Uniform("uColor"), 1, glm::value_ptr(m_Color));
	glBindVertexArray(mesh->VAO());
	glDrawArrays(mesh->Mode(), 0, mesh->VerticesNbr());
	//shader->Unbind();

	Super::Render(renderSystem);
}

//----------------------------------------------------------

void	GridEntity::Die()
{
	Super::Die();
	m_Health = -0.1f;
	m_StateMachineAttr.Clear();
}

//----------------------------------------------------------
