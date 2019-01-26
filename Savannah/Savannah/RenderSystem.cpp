#include "stdafx.h"

#include "RenderSystem.h"

#include "Game.h"
#include "GLShader.h"
#include "MeshData.h"

//----------------------------------------------------------

RenderSystem::RenderSystem(Game *game)
:	m_Game(game)
{
	_InitDefaultShader();
	_InitTriangleMeshData();
}

//----------------------------------------------------------

RenderSystem::~RenderSystem()
{
	for (std::map<std::string, GLShader*>::iterator it = m_ShaderBank.begin(); it != m_ShaderBank.end(); it++)
		delete it->second;
	m_ShaderBank.clear();

	for (std::map<std::string, MeshData*>::iterator it = m_MeshBank.begin(); it != m_MeshBank.end(); it++)
		delete it->second;
	m_MeshBank.clear();
}

//----------------------------------------------------------

void	RenderSystem::PreRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//----------------------------------------------------------

bool	RenderSystem::RegisterShader(std::string const &shaderName, GLShader *shader)
{
	if (m_ShaderBank[shaderName] != nullptr)
		return false;
	m_ShaderBank[shaderName] = shader;
	return true;
}

//----------------------------------------------------------

bool	RenderSystem::RegisterMesh(std::string const &meshName, MeshData *mesh)
{
	if (m_MeshBank[meshName] != nullptr)
		return false;
	m_MeshBank[meshName] = mesh;
	return true;
}

//----------------------------------------------------------

void	RenderSystem::_InitDefaultShader()
{
	GLShader *shader = new GLShader();

	char *vertexShader =
		"#version 410 core												\n"
		"layout(location = 0) in vec3 aPos;								\n"
		"uniform mat4 viewProj;											\n"
		"uniform mat4 modelTransform;									\n"
		"void main()													\n"
		"{																\n"
		"	gl_Position = viewProj * modelTransform * vec4(aPos, 1.0f);	\n"
		"}																\n"
		;

	char *fragShader =
		"#version 410 core												\n"
		"out vec4		FragColor;										\n"
		"uniform vec4	uColor;											\n"
		"void main()													\n"
		"{																\n"
		"	FragColor = uColor;											\n"
		"}																\n"
		;

	shader->LoadShader(GLShader::VERTEX_SHADER, vertexShader);
	shader->LoadShader(GLShader::FRAGMENT_SHADER, fragShader);
	shader->CreateAndLink();
	shader->Bind();
	{
		shader->AddUniform("uColor");
		shader->AddUniform("modelTransform");
		shader->AddUniform("viewProj");
	}
	shader->Unbind();

	GL_CHECK_ERRORS

	shader->m_name = "DefaultShader";
	RegisterShader("DefaultShader", shader);
}

//----------------------------------------------------------

void	RenderSystem::_InitTriangleMeshData()
{
	MeshData *mesh = new MeshData;

	float vertices[] =
	{
		-0.5f,	-0.5f,	-2.5f,
		0.5f,	-0.5f,	-2.5f,
		0.0f,	0.5f,	-2.5f
	};

	mesh->SetVertices(vertices, ARRAY_COUNT(vertices) * sizeof(float), 3, 3 * sizeof(float), GL_TRIANGLES);

	RegisterMesh("Triangle", mesh);
}

//----------------------------------------------------------
