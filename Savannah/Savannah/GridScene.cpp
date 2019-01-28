#include "stdafx.h"

#include "GridScene.h"
#include "Game.h"
#include "RenderSystem.h"
#include "SimpleEntity.h"
#include "MeshData.h"

//----------------------------------------------------------

GridScene::GridScene(Game *game)
:	Super()
,	m_Game(game)
,	m_GridEntity(nullptr)
{
	_CreateScene();
}

//----------------------------------------------------------

GridScene::~GridScene()
{}

//----------------------------------------------------------

void	GridScene::_CreateScene()
{
	_GenerateAndAddGrid(100, 60);

	_AddEntity(ANTELOPE, glm::vec3(1.f, 1.f, 0.f));
	_AddEntity(LION, glm::vec3(-1.f, -1.f, 0.f));
}

//----------------------------------------------------------

void	GridScene::_GenerateAndAddGrid(int xSubdiv, int ySubdiv)
{
	RenderSystem	*renderSystem = m_Game->GetRenderSystem();
	assert(renderSystem != nullptr);

	const std::string meshName = renderSystem->GenrateGridMesh(1.f, xSubdiv, ySubdiv);

	SimpleEntity *entity = new SimpleEntity("Grid");
	entity->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
	entity->SetMeshName(meshName);
	entity->SetShaderName("DefaultShader");
	entity->SetPosition(glm::vec3(0.f, 0.f, 0.f));
	//entity->SetScale(10.f);
	m_Entities.push_back(entity);
	m_GridEntity = entity;
	//entity->AddChild(planeTest);
}

//----------------------------------------------------------

void	GridScene::_AddEntity(ETeam type, const glm::vec3 &position)
{
	glm::vec4	lionColor = glm::vec4(0.8f, 0.5f, 0.f, 1.f);
	glm::vec4	antelopeColor = glm::vec4(0.8f, 0.25f, 0.f, 1.f);

	SimpleEntity	*entity = new SimpleEntity("Default name");
	entity->SetColor(type == LION ? lionColor : antelopeColor);
	entity->SetMeshName(type == LION ? "Rectangle" : "Triangle");
	entity->SetShaderName("DefaultShader");
	entity->SetPosition(position + glm::vec3(0.f, 0.f, 0.1f));

	m_GridEntity->AddChild(entity);

	m_Entities.push_back(entity);
}

//----------------------------------------------------------
