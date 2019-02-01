#include "stdafx.h"

#include "GridScene.h"
#include "Game.h"
#include "RenderSystem.h"
#include "GridEntity.h"
#include "MeshData.h"

#include "Spawner.h"

#include "AntelopeSM.h"

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
{
	if (m_LionStateMachine != nullptr)
		delete m_LionStateMachine;
	if (m_AntelopeStateMachine != nullptr)
		delete m_AntelopeStateMachine;
}

//----------------------------------------------------------

IEntity		*GridScene::GetFlagsEntity(ETeam team)
{
	return m_Flags[team];
};

//----------------------------------------------------------

void		GridScene::PreUpdate()
{
	// Here precompute one time every each needed information for state machine

	const std::vector<GridEntity*>	&lions = m_Spawners[LION]->Entities();
	const std::vector<GridEntity*>	&antelopes = m_Spawners[ANTELOPE]->Entities();

	// each antelope
	for (int i = 0; i < antelopes.size(); i++)
	{
		float	lastDistance = 0x7F800000; // infinity
		// each antelope - antelope
		GridEntity		*antelopeA = antelopes[i];
		const glm::vec3	&positionA = antelopeA->Position();

		for (int j = i + 1; j < antelopes.size(); j++)
		{
			// find the nearest friend
			GridEntity	*antelopeB = antelopes[j];

			const glm::vec3	&positionB = antelopeB->Position();
			float localDistance = glm::length(positionA - positionB);

			if (localDistance < lastDistance)
			{
				float oldNearest = 0x7F800000; // infinity
				if (antelopeA->m_StateMachineAttr.m_NearestFriend != nullptr)
				{
					const glm::vec3	&positionC = antelopeA->m_StateMachineAttr.m_NearestFriend->Position();
					oldNearest = glm::length(positionA - positionC);
				}

				if (localDistance < oldNearest)
				{
					lastDistance = localDistance;
					antelopeA->m_StateMachineAttr.m_NearestFriend = antelopeB;
					antelopeB->m_StateMachineAttr.m_NearestFriend = antelopeA;
				}
			}
		}

		lastDistance = 0x7F800000; // infinity

		for (int j = 0; j < lions.size(); j++)
		{
			// find the nearest ennemy
			GridEntity		*lionB = lions[j];
			const glm::vec3	&positionB = lionB->Position();
			float localDistance = glm::length(positionA - positionB);

			if (localDistance < lastDistance)
			{
				float oldNearest = 0x7F800000; // infinity
				if (antelopeA->m_StateMachineAttr.m_NearestEnemy != nullptr)
				{
					const glm::vec3	&positionC = antelopeA->m_StateMachineAttr.m_NearestEnemy->Position();
					oldNearest = glm::length(positionA - positionC);
				}

				if (localDistance < oldNearest)
				{
					lastDistance = localDistance;
					antelopeA->m_StateMachineAttr.m_NearestEnemy = lionB;
					lionB->m_StateMachineAttr.m_NearestEnemy = antelopeA;
				}
			}
		}
	}

	for (int i = 0; i < lions.size(); i++)
	{
		float	lastDistance = 0x7F800000; // infinity

		GridEntity		*lionA = lions[i];
		const glm::vec3	&positionA = lionA->Position();

		for (int j = 0; j < lions.size(); j++)
		{
			// find the nearest friend
			GridEntity		*lionB = lions[j];
			const glm::vec3	&positionB = lionB->Position();
			float localDistance = glm::length(positionA - positionB);

			if (localDistance < lastDistance)
			{
				float oldNearest = 0x7F800000; // infinity
				if (lionA->m_StateMachineAttr.m_NearestFriend != nullptr)
				{
					const glm::vec3	&positionC = antelopes[i]->m_StateMachineAttr.m_NearestFriend->Position();
					oldNearest = glm::length(positionA - positionC);
				}

				if (localDistance < oldNearest)
				{
					lastDistance = localDistance;
					lionA->m_StateMachineAttr.m_NearestFriend = lionB;
					lionB->m_StateMachineAttr.m_NearestFriend = lionA;
				}
			}
		}
	}
}

//----------------------------------------------------------

GridEntity	*GridScene::AddEntity(ETeam type, const glm::vec3 &position, bool isActive)
{
	glm::vec4	lionColor = glm::vec4(0.8f, 0.5f, 0.f, 1.f);
	glm::vec4	antelopeColor = glm::vec4(0.8f, 0.25f, 0.f, 1.f);

	GridEntity	*entity = new GridEntity("Default name", type, isActive);
	entity->SetColor(type == LION ? lionColor : antelopeColor);
	entity->SetMeshName(type == LION ? "Rectangle" : "Triangle");
	entity->SetShaderName("DefaultShader");
	entity->SetPosition(position + glm::vec3(0.f, 0.f, 0.1f));

	entity->ChangeStateNode(type == LION ? m_AntelopeStateMachine->Root() : m_AntelopeStateMachine->Root());
	m_GridEntity->AddChild(entity);

	m_Entities.push_back(entity);

	return entity;
}

//----------------------------------------------------------

void	GridScene::_CreateScene()
{
	m_AntelopeStateMachine = new StateMachine::AntelopeStateMachine(this);

	_GenerateAndAddGrid(100, 60);

	AddEntity(ANTELOPE, glm::vec3(1.f, 1.f, 0.f));
	AddEntity(LION, glm::vec3(-1.f, -1.f, 0.f));

	// flags
	{
		GridEntity	*entity = new GridEntity("Lion Flag", LION);
		entity->SetColor(glm::vec4(0.f, 1.f, 0.7f, 1.f));
		entity->SetMeshName("Diamond");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(-40.f, 20.f, 0.1f));

		m_GridEntity->AddChild(entity);
		m_Entities.push_back(entity);
		m_Flags[LION] = entity;
	}
	{
		GridEntity	*entity = new GridEntity("Antelope Flag", ANTELOPE);
		entity->SetColor(glm::vec4(1.f, 0.f, 0.f, 1.f));
		entity->SetMeshName("Diamond");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(40.f, -20.f, 0.1f));

		m_GridEntity->AddChild(entity);
		m_Entities.push_back(entity);
		m_Flags[ANTELOPE] = entity;
	}

	for (int i = 0; i < ETeam::_NONE; i++)
	{
		m_Spawners[i] = new GridSpawner((ETeam)i, this, 10);
		m_Entities.push_back(m_Spawners[i]);
		m_GridEntity->AddChild(m_Spawners[i]);

		m_Spawners[i]->SetColor((ETeam)i == LION ? glm::vec4(0.f, 0.7f, 0.1f, 1.f) : glm::vec4(0.5f, 0.f, 0.7f, 1.f));
		m_Spawners[i]->SetMeshName("Rectangle");
		m_Spawners[i]->SetShaderName("DefaultShader");
		m_Spawners[i]->SetPosition((ETeam)i == LION ? glm::vec3(-40.f, 20.f, 0.1f) : glm::vec3(40.f, -20.f, 0.1f));
		m_Spawners[i]->SetScale(3.f);
	}
}

//----------------------------------------------------------

void	GridScene::_GenerateAndAddGrid(int xSubdiv, int ySubdiv)
{
	RenderSystem	*renderSystem = m_Game->GetRenderSystem();
	assert(renderSystem != nullptr);

	const std::string meshName = renderSystem->GenrateGridMesh(1.f, xSubdiv, ySubdiv);

	GridEntity *entity = new GridEntity("Grid", _NONE);
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
