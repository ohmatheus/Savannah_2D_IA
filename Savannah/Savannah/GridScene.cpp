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
	_GenerateAndAddGrid(100, 100);
}

//----------------------------------------------------------

void	GridScene::_GenerateAndAddGrid(int xSubdiv, int ySubdiv)
{
	RenderSystem	*renderSystem = m_Game->GetRenderSystem();
	assert(renderSystem != nullptr);

	const std::string meshName = renderSystem->GenrateGridMesh(5.f, xSubdiv, ySubdiv);

	SimpleEntity *entity = new SimpleEntity("Grid");
	entity->SetColor(glm::vec4(1.f, 0.f, 1.f, 1.f));
	entity->SetMeshName(meshName);
	entity->SetShaderName("DefaultShader");
	entity->SetPosition(glm::vec3(0.f, 0.f, 0.f));
	//entity->SetScale(10.f);
	m_Entities.push_back(entity);

	//entity->AddChild(planeTest);
}

//----------------------------------------------------------
