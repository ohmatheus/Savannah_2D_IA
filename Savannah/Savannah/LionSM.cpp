#include "stdafx.h"

#include "LionSM.h"
#include "StateNode.h"
#include "Transition.h"
#include "GridEntity.h"
#include "GridScene.h"
#include "Steering.h"
#include "Spawner.h"

namespace StateMachine
{
	LionStateMachine::LionStateMachine(IScene *scene)
	: Super(scene)
	{
		GridScene	*gridScene = static_cast<GridScene*>(scene);

		StateNode *idle = NewState();
		m_Root = idle;
		idle->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			// do nothing
		});

		StateNode	*goForFlag = NewState();
		goForFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(type);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(type)->Position();

			ent->Seek(targetPosition, dt);
		});

		StateNode	*protectFlag = NewState();
		protectFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(type);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(type)->Position();

			ent->Seek(targetPosition, dt);
		});

		StateNode	*goForBase = NewState();
		goForBase->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			GridSpawner			*spawner = gridScene->Spawner(type);
			glm::vec3			targetPosition = targetPosition = spawner->Position();
			ent->Seek(targetPosition, dt);
		});

		StateNode	*makeFriends = NewState();
		makeFriends->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			GridEntity			*nearestFriend = ent->StateMachineAttr().m_NearestFriend;

			glm::vec3			targetPosition;
			if (nearestFriend != nullptr)
				targetPosition = nearestFriend->Position();
			else
				return;

			ent->Seek(targetPosition, dt);
		});

		StateNode	*attackEnemy = NewState();
		attackEnemy->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			GridEntity			*nearestEnemy = ent->StateMachineAttr().m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			ent->Seek(targetPosition, dt);
		});

		StateNode	*fleeEnemy = NewState();
		fleeEnemy->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			GridEntity			*nearestEnemy = ent->StateMachineAttr().m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			ent->Flee(targetPosition, dt);
		});

		StateNode	*goForEnemyFlag = NewState();
		goForEnemyFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(GridScene::ANTELOPE);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(GridScene::ANTELOPE)->Position();

			ent->Seek(targetPosition, dt);
		});

		StateNode	*getBackFlag = NewState();
		getBackFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(GridScene::ANTELOPE);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(GridScene::ANTELOPE)->Position();

			ent->Seek(targetPosition, dt);
		});

		ICondition	*hasFlag = NewCondition(EHasFlag, Equal, true);
		ICondition	*dontHaveFlag = NewCondition(EHasFlag, Equal, false);

		ICondition	*teamHasFlag = NewCondition(ETeamHasFlag, Equal, true);
		ICondition	*teamDontHasFlag = NewCondition(ETeamHasFlag, Equal, false);

		ICondition	*enemyHasFlag = NewCondition(EEnemyTeamHasFlag, Equal, true);
		ICondition	*enemyDontHaveFlag = NewCondition(EEnemyTeamHasFlag, Equal, false);

		ICondition	*nextFromFlag = NewCondition(EDistanceFromMyFlag, Inferior, 5.f);
		ICondition	*farFromFlag = NewCondition(EDistanceFromMyFlag, Superior, 5.f);

		ICondition	*teamHasFlagAndNextFromFlag = NewCondition(teamHasFlag, And, nextFromFlag);
		ICondition	*teamHasFlagAndFarFromFlag = NewCondition(teamHasFlag, And, farFromFlag);

		ICondition	*dontHasFlagAndNextFromFlag = NewCondition(dontHaveFlag, And, nextFromFlag);
		ICondition	*dontHasFlagAndFarFromFlag = NewCondition(dontHaveFlag, And, farFromFlag);

		ICondition	*isNearFromEnemy = NewCondition(EEnnemyDistance, Inferior, gridScene->Parameters().m_AntelopeFleeRadius);
		ICondition	*isNotNearFromEnemy = NewCondition(EEnnemyDistance, Superior, gridScene->Parameters().m_AntelopeFleeRadius);

		NewTransition(idle, goForBase, hasFlag);
		NewTransition(idle, goForFlag, dontHaveFlag);

		NewTransition(goForFlag, goForBase, hasFlag);
		NewTransition(goForFlag, getBackFlag, enemyHasFlag);
		NewTransition(goForFlag, attackEnemy, isNearFromEnemy);
		NewTransition(goForFlag, protectFlag, teamHasFlagAndNextFromFlag);
		NewTransition(goForFlag, goForEnemyFlag, teamHasFlagAndFarFromFlag);

		NewTransition(goForBase, fleeEnemy, isNearFromEnemy);
		NewTransition(goForBase, idle, teamDontHasFlag);

		NewTransition(getBackFlag, idle, enemyDontHaveFlag); // search and kill enemy

		NewTransition(goForEnemyFlag, protectFlag, teamHasFlagAndNextFromFlag); // defensivly
		NewTransition(goForEnemyFlag, idle, teamDontHasFlag);

		NewTransition(protectFlag, goForEnemyFlag, teamHasFlagAndFarFromFlag);
		NewTransition(protectFlag, idle, teamDontHasFlag);

		NewTransition(fleeEnemy, idle, isNotNearFromEnemy);
		NewTransition(attackEnemy, idle, isNotNearFromEnemy);
	}

	//----------------------------------------------------------

	LionStateMachine::~LionStateMachine()
	{}

	//----------------------------------------------------------
}
