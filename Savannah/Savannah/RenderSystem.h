#pragma once

#include <map>

//----------------------------------------------------------

class	Game;
class	GLShader;
class	MeshData;
class	Scene;

//----------------------------------------------------------

class RenderSystem final
{
public:
	RenderSystem(Game *game);
	~RenderSystem();

	void	Render(Scene *scene);

	bool	RegisterShader(std::string const &shaderName, GLShader*	shader);
	bool	RegisterMesh(std::string const &meshName, MeshData*	mesh);

private:
	void	_InitDefaultShader();
	void	_InitTriangleMeshData();

	Game								*m_Game;
	std::map<std::string, GLShader*>	m_ShaderBank;
	std::map<std::string, MeshData*>	m_MeshBank;
};

//----------------------------------------------------------
