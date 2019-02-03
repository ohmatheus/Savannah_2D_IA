#include "stdafx.h"

#include "AntelopeSM.h"
#include "StateNode.h"
#include "Transition.h"
#include "GridEntity.h"
#include "GridScene.h"
#include "Spawner.h"
#include "Steering.h"

namespace StateMachine
{
	AntelopeStateMachine::AntelopeStateMachine(IScene *scene)
	:	Super(scene)
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

			GridEntity			*nearestFriend = ent->m_StateMachineAttr.m_NearestFriend;

			glm::vec3			targetPosition;
			if (nearestFriend != nullptr)
				targetPosition = nearestFriend->Position();
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

			GridEntity			*nearestEnemy = ent->m_StateMachineAttr.m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			ent->Flee(targetPosition, dt);
		});

		StateNode	*attackEnemy = NewState();
		attackEnemy->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			GridEntity			*nearestEnemy = ent->m_StateMachineAttr.m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			ent->Seek(targetPosition, dt);
		});

		StateNode	*goForEnemyFlag = NewState();
		goForEnemyFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(GridScene::LION);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(GridScene::LION)->Position();

			ent->Seek(targetPosition, dt);
		});

		StateNode	*getBackFlag = NewState();
		getBackFlag->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();

			glm::vec3			targetPosition;
			GridEntity			*entityHavingFlag = gridScene->EntityThatPosessFlag(GridScene::LION);

			if (entityHavingFlag != nullptr)
				targetPosition = entityHavingFlag->Position();
			else
				targetPosition = gridScene->GetFlagsEntity(GridScene::LION)->Position();

			ent->Seek(targetPosition, dt);
		});

		ICondition	*isAlone = NewCondition(EFriendDistance, Superior | Equal, gridScene->Parameters().m_AntelopeLonelinessRadius);
		ICondition	*isNotAlone = NewCondition(EFriendDistance, Inferior, gridScene->Parameters().m_AntelopeLonelinessRadius);

		ICondition	*hasFlag = NewCondition(EHasFlag, Equal, true);
		ICondition	*dontHaveFlag = NewCondition(EHasFlag, Equal, false);

		ICondition	*teamHasFlag = NewCondition(ETeamHasFlag, Equal, true);
		ICondition	*teamDontHasFlag = NewCondition(ETeamHasFlag, Equal, false);

		ICondition	*enemyHasFlag = NewCondition(EEnemyTeamHasFlag, Equal, true);
		ICondition	*enemyDontHaveFlag = NewCondition(EEnemyTeamHasFlag, Equal, false);

		ICondition	*isNotAloneAndHasFlag = NewCondition(isNotAlone, And, hasFlag);
		ICondition	*isNotAloneAndDontHasFlag = NewCondition(isNotAlone, And, dontHaveFlag);

		ICondition	*nextFromFlag = NewCondition(EDistanceFromMyFlag, Inferior, 5.f);
		ICondition	*farFromFlag = NewCondition(EDistanceFromMyFlag, Superior, 5.f);

		ICondition	*teamHasFlagAndNextFromFlag = NewCondition(teamHasFlag, And, nextFromFlag);
		ICondition	*teamHasFlagAndFarFromFlag = NewCondition(teamHasFlag, And, farFromFlag);

		ICondition	*dontHasFlagAndNextFromFlag = NewCondition(dontHaveFlag, And, nextFromFlag);
		ICondition	*dontHasFlagAndFarFromFlag = NewCondition(dontHaveFlag, And, farFromFlag);

		ICondition	*isNearFromEnemy = NewCondition(EEnnemyDistance, Inferior, gridScene->Parameters().m_AntelopeFleeRadius);
		ICondition	*isNotNearFromEnemy = NewCondition(EEnnemyDistance, Superior, gridScene->Parameters().m_AntelopeFleeRadius);

		ICondition	*isSafeToAttack = NewCondition(ENearFriendCount, Superior | Equal, gridScene->Parameters().m_AntelopeFriendCountToAttack);
		ICondition	*isNotSafeToAttack = NewCondition(ENearFriendCount, Inferior, gridScene->Parameters().m_AntelopeFriendCountToAttack);

		ICondition	*isNearEnemyAndSafeToAttack = NewCondition(isNearFromEnemy, And, isSafeToAttack);

		// Transitions between states
		NewTransition(idle, makeFriends, isAlone);
		NewTransition(idle, goForBase, hasFlag);
		NewTransition(idle, goForFlag, dontHaveFlag);

		NewTransition(makeFriends, goForFlag, isNotAlone);

		NewTransition(goForFlag, idle, isAlone);
		NewTransition(goForFlag, goForBase, hasFlag);
		NewTransition(goForFlag, getBackFlag, enemyHasFlag);
		NewTransition(goForFlag, attackEnemy, isNearEnemyAndSafeToAttack);
		NewTransition(goForFlag, fleeEnemy, isNearFromEnemy);
		NewTransition(goForFlag, protectFlag, teamHasFlagAndNextFromFlag);
		NewTransition(goForFlag, goForEnemyFlag, teamHasFlagAndFarFromFlag);

		NewTransition(goForBase, idle, isAlone);
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

	AntelopeStateMachine::~AntelopeStateMachine()
	{}

//----------------------------------------------------------
}
