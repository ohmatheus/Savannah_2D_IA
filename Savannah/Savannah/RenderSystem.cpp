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
		"uniform mat4 model;											\n"
		"uniform mat4 view;												\n"
		"uniform mat4 proj;												\n"
		"void main()													\n"
		"{																\n"
		//"	gl_Position = view * model * vec4(aPos, 1.0f);		\n"
		"	gl_Position = proj * view * model * vec4(aPos, 1.0f);		\n"
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
		shader->AddUniform("model");
		shader->AddUniform("view");
		shader->AddUniform("proj");
	}
	shader->Unbind();

	GL_CHECK_ERRORS

	shader->m_name = "DefaultShader";
	RegisterShader("DefaultShader", shader);
}

//----------------------------------------------------------

void	RenderSystem::_InitTriangleMeshData()
{
	{
		MeshData *mesh = new MeshData;
		float vertices[] =
		{
			-0.5f,	-0.5f,	0.f,
			0.5f,	-0.5f,	0.f,
			0.0f,	0.5f,	0.f
		};
		mesh->SetVertices(vertices, ARRAY_COUNT(vertices), 3, 3 * sizeof(float), GL_TRIANGLES);
		RegisterMesh("Triangle", mesh);
	}

	{
		MeshData *mesh = new MeshData;
		float vertices[] =
		{
			-0.5f,	-0.5f,	0.f,
			0.5f,	-0.5f,	0.f,
			-0.5f,	0.5f,	0.f,
			0.5f,	0.5f,	0.f
		};
		mesh->SetVertices(vertices, ARRAY_COUNT(vertices), 3, 3 * sizeof(float), GL_TRIANGLE_STRIP);
		RegisterMesh("Rectangle", mesh);
	}

	// grid
	{
		MeshData *mesh = new MeshData;

		const int	xSubdiv = 100;
		const int	ySubdiv = 100;
		const int	verticeNbr = (xSubdiv + 1) * 2 * 2 + (ySubdiv + 1) * 2 * 2; // 2 * 2 vertex per subdiv

		const float top = 0.5f;
		const float left = -0.5f;

		const uint	offsetForSubdiv = 3 * 2;
		float		*components = (float*)malloc(verticeNbr * sizeof(float) * 3);

		for (int i = 0; i <= xSubdiv; i++)
		{
			double hRatio = lerp(left, -left, double(i) / double(xSubdiv));

			components[offsetForSubdiv * i + 0] = hRatio;	// X1
			components[offsetForSubdiv * i + 1] = top;		// Y1
			components[offsetForSubdiv * i + 2] = 0.f;		// Z1

			components[offsetForSubdiv * i + 3] = hRatio;	// X2
			components[offsetForSubdiv * i + 4] = -top;		// Y2
			components[offsetForSubdiv * i + 5] = 0.f;		// Z2
		}

		for (int i = 0; i <= ySubdiv; i++)
		{
			double vRatio = lerp(top, -top, double(i) / double(ySubdiv));

			components[offsetForSubdiv * (i + xSubdiv + 1) + 0] = left;		// X1
			components[offsetForSubdiv * (i + xSubdiv + 1) + 1] = vRatio;	// Y1
			components[offsetForSubdiv * (i + xSubdiv + 1) + 2] = 0.f;		// Z1

			components[offsetForSubdiv * (i + xSubdiv + 1) + 3] = -left;	// X2
			components[offsetForSubdiv * (i + xSubdiv + 1) + 4] = vRatio;	// Y2
			components[offsetForSubdiv * (i + xSubdiv + 1) + 5] = 0.f;		// Z2
		}


		mesh->SetVertices(components, verticeNbr * 3, 3, 3 * sizeof(float), GL_LINES);

		RegisterMesh("Grid", mesh);
		delete components;
	}
}

//----------------------------------------------------------
