#include "stdafx.h"

#include "AntelopeSM.h"
#include "StateNode.h"
#include "Transition.h"
#include "GridEntity.h"
#include "GridScene.h"
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
			GridScene::ETeam	enemyType = type == GridScene::LION ? GridScene::LION : GridScene::ANTELOPE;

			glm::vec3			targetPosition = gridScene->GetFlagsEntity(enemyType)->Position();

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

		ICondition	*isAlone = NewCondition(EFriendDistance, Superior, gridScene->Parameters().m_AntelopeLonelinessRadius);
		ICondition	*isNotAlone = NewCondition(EFriendDistance, Inferior, gridScene->Parameters().m_AntelopeLonelinessRadius);

		ICondition	*isNearFromEnemy = NewCondition(EEnnemyDistance, Inferior, gridScene->Parameters().m_AntelopeFleeRadius);
		ICondition	*isNotNearFromEnemy = NewCondition(EEnnemyDistance, Superior, gridScene->Parameters().m_AntelopeFleeRadius);

		ICondition	*isSafeToAttack = NewCondition(ENearFriendCount, Superior | Equal, gridScene->Parameters().m_AntelopeFriendCountToAttack);
		ICondition	*isNotSafeToAttack = NewCondition(ENearFriendCount, Inferior, gridScene->Parameters().m_AntelopeFriendCountToAttack);

		ICondition	*isNearEnemyAndSafeToAttack = NewCondition(isNearFromEnemy, And, isSafeToAttack);

		// Transitions between states
		NewTransition(idle, makeFriends, isAlone);
		NewTransition(idle, goForFlag, isNotAlone);

		NewTransition(makeFriends, goForFlag, isNotAlone);

		NewTransition(goForFlag, idle, isAlone);
		NewTransition(goForFlag, attackEnemy, isNearEnemyAndSafeToAttack);
		NewTransition(goForFlag, fleeEnemy, isNearFromEnemy);

		NewTransition(fleeEnemy, idle, isNotNearFromEnemy);

		NewTransition(attackEnemy, idle, isNotNearFromEnemy);
	}

//----------------------------------------------------------

	AntelopeStateMachine::~AntelopeStateMachine()
	{}

//----------------------------------------------------------
}
