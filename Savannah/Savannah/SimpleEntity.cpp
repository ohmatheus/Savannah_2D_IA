#include "stdafx.h"

#include "SimpleEntity.h"
#include "RenderSystem.h"
#include "GLShader.h"
#include "MeshData.h"
#include "Game.h"

//----------------------------------------------------------

SimpleEntity::SimpleEntity(const std::string &name)
:	Super(name)
{
}

//----------------------------------------------------------

SimpleEntity::~SimpleEntity()
{}

//----------------------------------------------------------

void		SimpleEntity::Update(float dt)
{
	// ???
	m_Yaw += dt * 50.f;
}

//----------------------------------------------------------

void		SimpleEntity::Render(RenderSystem *renderSystem)
{
	GLShader	*shader = renderSystem->GetShader(m_ShaderName);
	MeshData	*mesh = renderSystem->GetMesh(m_MeshName);

	glm::mat4	modelW = ModelMatrix(); // do not recompute each frame, keep in class and modify directly TODO

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
}

//----------------------------------------------------------
