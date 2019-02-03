#include "stdafx.h"

#include "GridScene.h"
#include "Game.h"
#include "RenderSystem.h"
#include "GridEntity.h"
#include "MeshData.h"

#include "Spawner.h"

#include "AntelopeSM.h"
#include "LionSM.h"

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

GridScene::GridScene(const GridScene &scene)
:	Super(scene)
{
	m_Game = scene.m_Game;

	//m_AntelopeStateMachine = scene.m_AntelopeStateMachine; // should clone ?
	//m_LionStateMachine = scene.m_LionStateMachine;

	m_AntelopeStateMachine = new StateMachine::AntelopeStateMachine(this);
	m_LionStateMachine = new StateMachine::LionStateMachine(this);

	m_Flags[0] = static_cast<GridEntity*>(GetEntity("Lion Flag")); // ouch + error prone
	assert(m_Flags[0]);
	m_Flags[1] = static_cast<GridEntity*>(GetEntity("Antelope Flag")); // ouch + error prone
	assert(m_Flags[1]);

	m_GridEntity = static_cast<GridEntity*>(GetEntity("Grid")); // ouch + error prone
	assert(m_GridEntity);

	m_Spawners[0] = static_cast<GridSpawner*>(GetEntity("LionSpawner"));
	assert(m_Spawners[0]);
	m_Spawners[1] = static_cast<GridSpawner*>(GetEntity("AntelopeSpawner"));
	assert(m_Spawners[1]);

	m_FlagCollisionRadius = scene.m_FlagCollisionRadius;
}

//----------------------------------------------------------

void	GridScene::OnSceneStart()
{
	for (int i = 0; i < ETeam::_NONE; i++)
	{
		m_Spawners[i]->OnSceneStart(this);
	}
}

//----------------------------------------------------------

IScene	*GridScene::Clone()
{
	return new GridScene(*this);
}

//----------------------------------------------------------

IEntity		*GridScene::GetFlagsEntity(ETeam team)
{
	return m_Flags[team];
};

//----------------------------------------------------------

void		GridScene::PreUpdate(float dt)
{
	// Here precompute one time every each needed information for state machine
	// Saves a huge amount of time regarding state machine's conditions that do not need to recalculate this.

	const std::vector<GridEntity*>	&lions = m_Spawners[LION]->Entities();
	const std::vector<GridEntity*>	&antelopes = m_Spawners[ANTELOPE]->Entities();

	IEntity							*lionFlag = GetFlagsEntity(LION);
	IEntity							*antelopeFlag = GetFlagsEntity(ANTELOPE);

	// pre-pre-update to know if one needs to die
	for (int i = 0; i < antelopes.size(); i++)
	{
		antelopes[i]->m_StateMachineAttr.m_FriendsNextToMe = 0;
		if (antelopes[i]->Health() <= 0.f)
		{
			antelopes[i]->Die();
			if (m_AntelopePosessFlag == antelopes[i])
				_OnFlagLost(ANTELOPE);
			continue;
		}

		if (m_AntelopePosessFlag == nullptr)
		{
			float	distanceFromFlag = glm::length(antelopes[i]->Position() - antelopeFlag->Position());
			if (distanceFromFlag < m_FlagCollisionRadius)
				_OnEntityGetFlag(antelopes[i]);
		}
	}

	for (int i = 0; i < lions.size(); i++)
	{
		lions[i]->m_StateMachineAttr.m_FriendsNextToMe = 0;
		if (lions[i]->Health() <= 0.f)
		{
			lions[i]->Die();
			if (m_LionPosessFlag == lions[i])
				_OnFlagLost(LION);
			continue;
		}

		if (m_LionPosessFlag == nullptr)
		{
			float	distanceFromFlag = glm::length(lions[i]->Position() - lionFlag->Position());
			if (distanceFromFlag < m_FlagCollisionRadius)
				_OnEntityGetFlag(lions[i]);
		}
	}

	for (int i = 0; i < antelopes.size(); i++)
	{
		GridEntity				*antelopeA = antelopes[i];

		if (!antelopeA->IsActive())
			continue;
		const glm::vec3			&positionA = antelopeA->Position();

		for (int j = i + 1; j < antelopes.size(); j++)
		{
			// find the nearest friend
			GridEntity			*antelopeB = antelopes[j];
			if (!antelopeB->IsActive())
				continue;

			const glm::vec3		&positionB = antelopeB->Position();
			float				localDistance = glm::length(positionA - positionB);

			if (localDistance < m_Parameters.m_AntelopeFriendCountRadius) // friends next to me
			{
				antelopeA->m_StateMachineAttr.m_FriendsNextToMe++;
				antelopeB->m_StateMachineAttr.m_FriendsNextToMe++;
			}

			if (localDistance < 0.2f) // special event to avoid entities overlap
			{
				const glm::vec3 arbitraryAntiOverlapVector = glm::vec3(0.5f, 0.5f, 0.f);
				antelopeB->SetPosition(positionB + arbitraryAntiOverlapVector * dt);
				antelopeA->SetPosition(positionA - arbitraryAntiOverlapVector * dt);
			}

			GridEntity			*antelopeAC = antelopeA->m_StateMachineAttr.m_NearestFriend;
			if (antelopeAC != nullptr)
			{
				const float		distanceOldNearest = glm::length(positionA - antelopeAC->Position());
				if (localDistance < distanceOldNearest || !antelopeAC->IsActive())
					antelopeA->m_StateMachineAttr.m_NearestFriend = antelopeB;
				else
					antelopeA->m_StateMachineAttr.m_NearestFriend = antelopeAC;
			}
			else
				antelopeA->m_StateMachineAttr.m_NearestFriend = antelopeB;

			GridEntity			*antelopeBD = antelopeB->m_StateMachineAttr.m_NearestFriend;
			if (antelopeBD != nullptr)
			{
				const float		distanceOldNearest = glm::length(positionB - antelopeBD->Position());
				if (localDistance < distanceOldNearest || !antelopeBD->IsActive())
					antelopeB->m_StateMachineAttr.m_NearestFriend = antelopeA;
				else 
					antelopeB->m_StateMachineAttr.m_NearestFriend = antelopeBD;
			}
			else
				antelopeB->m_StateMachineAttr.m_NearestFriend = antelopeA;
		}

		for (int j = 0; j < lions.size(); j++)
		{
			// find the nearest ennemy
			GridEntity			*lionB = lions[j];

			if (!lionB->IsActive())
				continue;

			const glm::vec3		&positionB = lionB->Position();
			float				localDistance = glm::length(positionA - positionB);

			assert(antelopeA->IsActive());
			if (localDistance < m_Parameters.m_AntelopeAttackRadius)
				lionB->Hit(antelopeA->Dps() * dt);
			if (localDistance < m_Parameters.m_LionAttackRadius)
				antelopeA->Hit(lionB->Dps() * dt);
			// die at next frame

			GridEntity			*lionAC = antelopeA->m_StateMachineAttr.m_NearestEnemy;
			if (lionAC != nullptr)
			{
				const float distanceOldNearest = glm::length(positionA - lionAC->Position());
				if (localDistance < distanceOldNearest || !lionAC->IsActive())
					antelopeA->m_StateMachineAttr.m_NearestEnemy = lionB;
				else
					antelopeA->m_StateMachineAttr.m_NearestEnemy = lionAC;
			}
			else
				antelopeA->m_StateMachineAttr.m_NearestEnemy = lionB;

			GridEntity			*antelopeBD = lionB->m_StateMachineAttr.m_NearestEnemy;
			if (antelopeBD != nullptr)
			{
				const float		distanceOldNearest = glm::length(positionB - antelopeBD->Position());
				if (localDistance < distanceOldNearest || !antelopeBD->IsActive())
					lionB->m_StateMachineAttr.m_NearestEnemy = antelopeA;
				else
					lionB->m_StateMachineAttr.m_NearestEnemy = antelopeBD;
			}
			else
				lionB->m_StateMachineAttr.m_NearestEnemy = antelopeA;
		}
	}

	for (int i = 0; i < lions.size(); i++)
	{
		GridEntity				*lionA = lions[i];
		const glm::vec3			&positionA = lionA->Position();

		if (!lionA->IsActive())
			continue;

		for (int j = 0; j < lions.size(); j++)
		{
			// find the nearest friend
			GridEntity			*lionB = lions[j];
			if (!lionB->IsActive())
				continue;

			const glm::vec3		&positionB = lionB->Position();
			float				localDistance = glm::length(positionA - positionB);

			if (localDistance < 5.f) // friends next to me
			{
				lionA->m_StateMachineAttr.m_FriendsNextToMe++;
				lionB->m_StateMachineAttr.m_FriendsNextToMe++;
			}

			GridEntity	*lionAC = lionA->m_StateMachineAttr.m_NearestFriend;
			if (lionAC != nullptr)
			{
				const float distanceOldNearest = glm::length(positionA - lionAC->Position());
				if (localDistance < distanceOldNearest || !lionAC->IsActive())
					lionA->m_StateMachineAttr.m_NearestFriend = lionB;
				else
					lionA->m_StateMachineAttr.m_NearestFriend = lionAC;
			}
			else
				lionA->m_StateMachineAttr.m_NearestFriend = lionB;

			GridEntity			*lionBD = lionB->m_StateMachineAttr.m_NearestFriend;
			if (lionBD != nullptr)
			{
				const float		distanceOldNearest = glm::length(positionB - lionBD->Position());
				if (localDistance < distanceOldNearest || !lionBD->IsActive())
					lionB->m_StateMachineAttr.m_NearestFriend = lionA;
				else
					lionB->m_StateMachineAttr.m_NearestFriend = lionBD;
			}
			else
				lionB->m_StateMachineAttr.m_NearestFriend = lionA;
		}
	}
}

//----------------------------------------------------------

GridEntity	*GridScene::AddEntityToGrid(ETeam type, const glm::vec3 &position, bool isActive)
{
	glm::vec4	lionColor = glm::vec4(0.8f, 0.5f, 0.f, 1.f);
	glm::vec4	antelopeColor = glm::vec4(0.8f, 0.25f, 0.f, 1.f);

	GridEntity	*entity = new GridEntity("Default name", type, isActive);
	entity->SetColor(type == LION ? lionColor : antelopeColor);
	entity->SetMeshName(type == LION ? "Rectangle" : "Triangle");
	entity->SetShaderName("DefaultShader");
	entity->SetPosition(position + glm::vec3(0.f, 0.f, 0.1f));

	entity->ChangeStateNode(type == LION ? m_LionStateMachine->Root() : m_AntelopeStateMachine->Root());
	m_GridEntity->AddChild(entity);

	//m_Entities.push_back(entity);

	return entity;
}

//----------------------------------------------------------

void	GridScene::_CreateScene()
{
	m_AntelopeStateMachine = new StateMachine::AntelopeStateMachine(this);
	m_LionStateMachine = new StateMachine::LionStateMachine(this);

	// should be done by reflection + save as file, but well...
	{
		m_Parameters.m_AntelopeSpawnCount = 300;
		m_Parameters.m_LionSpawnCount = 75;

		m_Parameters.m_LionVelocity = 2.5f;
		m_Parameters.m_AntelopeVelocity = 4.f;

		m_Parameters.m_LionRotationSpeed = 50.f;
		m_Parameters.m_AntelopeRotationSpeed = 50.f;

		m_Parameters.m_LionInitialHealth = 10.f;
		m_Parameters.m_AntelopeInitialHealth = 10.f;

		m_Parameters.m_LionAttackRadius = 2.5f;
		m_Parameters.m_AntelopeAttackRadius = 2.5f;

		m_Parameters.m_LionDPS = 10.f;
		m_Parameters.m_AntelopeDPS = 2.6f; // i'm such a romantic.

		m_Parameters.m_AntelopeFleeRadius = 5.f;
		m_Parameters.m_AntelopeFriendCountToAttack = 4;
		m_Parameters.m_AntelopeFriendCountRadius = 5.f;
		m_Parameters.m_AntelopeLonelinessRadius = 1.f;
	}

	m_FlagCollisionRadius = 0.7f;

	_GenerateAndAddGrid(100, 60);

	// flags
	{
		GridEntity	*entity = new GridEntity("Lion Flag", LION);
		entity->SetColor(glm::vec4(1.f, 0.f, 0.f, 1.f));
		entity->SetMeshName("Diamond");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(40.f, 20.f, 0.1f));

		m_GridEntity->AddChild(entity);
		//m_Entities.push_back(entity);
		m_Flags[LION] = entity;
	}
	{
		GridEntity	*entity = new GridEntity("Antelope Flag", ANTELOPE);
		entity->SetColor(glm::vec4(0.f, 1.f, 0.7f, 1.f));
		entity->SetMeshName("Diamond");
		entity->SetShaderName("DefaultShader");
		entity->SetPosition(glm::vec3(-40.f, 20.f, 0.1f));

		m_GridEntity->AddChild(entity);
		//m_Entities.push_back(entity);
		m_Flags[ANTELOPE] = entity;
	}

	for (int i = 0; i < ETeam::_NONE; i++)
	{
		std::string spawnerName = ((ETeam)i == LION ? "Lion" : "Antelope"); // TODO find a way to STRIGIFY an enum
		spawnerName += "Spawner";
		m_Spawners[i] = new GridSpawner((ETeam)i, spawnerName, (ETeam)i == LION ? m_Parameters.m_LionSpawnCount : m_Parameters.m_AntelopeSpawnCount);
		//m_Entities.push_back(m_Spawners[i]);
		m_GridEntity->AddChild(m_Spawners[i]);

		m_Spawners[i]->SetColor((ETeam)i == LION ? glm::vec4(0.f, 0.7f, 0.1f, 1.f) : glm::vec4(0.5f, 0.f, 0.7f, 1.f));
		m_Spawners[i]->SetMeshName("Rectangle");
		m_Spawners[i]->SetShaderName("DefaultShader");
		m_Spawners[i]->SetPosition((ETeam)i == LION ? glm::vec3(-40.f, -20.f, 0.1f) : glm::vec3(40.f, -20.f, 0.1f));
		m_Spawners[i]->SetScale(3.f);
	}
}

//----------------------------------------------------------

StateMachine::StateNode		*GridScene::GetStateMachineRoot(ETeam team)
{
	if (team == LION)
		return m_LionStateMachine->Root();
	else
		return m_AntelopeStateMachine->Root();
}

//----------------------------------------------------------

void	GridScene::SetParameters(const SGameParameters &params)
{
	Super::SetParameters(params);

	m_Spawners[LION]->SetPoolSize(m_Parameters.m_LionSpawnCount);
	m_Spawners[ANTELOPE]->SetPoolSize(m_Parameters.m_AntelopeSpawnCount);
	// update the all scene;
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
	m_Entities.push_back(entity);
	m_GridEntity = entity;
	m_GridEntity->Pitch() = -50;
}

//----------------------------------------------------------

void	GridScene::_OnEntityGetFlag(GridEntity	*ent)
{
	ETeam	team = ent->Team();
	if (team == LION)
	{
		m_LionPosessFlag = ent;
		m_Flags[team]->SetParent(ent);
		m_Flags[team]->SetPosition(glm::vec3(0));
	}
	else
	{
		assert(team == ANTELOPE);
		m_AntelopePosessFlag = ent;
		m_Flags[team]->SetParent(ent);
		m_Flags[team]->SetPosition(glm::vec3(0));
	}
}

//----------------------------------------------------------

void	GridScene::_OnFlagLost(ETeam team)
{
	if (team == LION)
		m_LionPosessFlag = nullptr;
	else
		m_AntelopePosessFlag = nullptr;

	m_Flags[team]->SetParent(m_GridEntity);
	m_Flags[team]->SetPosition(glm::vec3(-20, 40, 0.0));

	// reset parent to grid
	// reset position
}

//----------------------------------------------------------
