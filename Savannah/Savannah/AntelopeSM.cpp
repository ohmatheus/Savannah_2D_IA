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
			GridScene::ETeam	enemyType = type == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION;

			glm::vec3			targetPosition;
			targetPosition = gridScene->GetFlagsEntity(enemyType)->Position();

			const glm::vec3		&position = ent->Position();
			const glm::vec3		&forward = ent->Forward();
			const glm::vec3		direction = glm::normalize(targetPosition - position);

			const float angleDif = ISteering::Angle(direction, forward);

			ent->Rotate(angleDif, dt);
			ent->MoveForward(dt);
		});

		StateNode	*makeFriends = NewState();
		makeFriends->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();
			GridScene::ETeam	enemyType = type == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION;

			GridEntity	*nearestFriend = ent->m_StateMachineAttr.m_NearestFriend;

			glm::vec3			targetPosition;
			if (nearestFriend != nullptr)
				targetPosition = nearestFriend->Position();
			else
				return;

			const glm::vec3		&position = ent->Position();
			const glm::vec3		&forward = ent->Forward();
			const glm::vec3		direction = glm::normalize(targetPosition - position);

			const float angleDif = ISteering::Angle(direction, forward);

			ent->Rotate(angleDif, dt);
			ent->MoveForward(dt);
		});

		StateNode	*fleeEnemy = NewState();
		fleeEnemy->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();
			GridScene::ETeam	enemyType = type == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION;

			GridEntity	*nearestEnemy = ent->m_StateMachineAttr.m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			const glm::vec3		&position = ent->Position();
			const glm::vec3		&forward = ent->Forward();
			const glm::vec3		direction = glm::normalize(position - targetPosition);

			const float angleDif = ISteering::Angle(direction, forward);

			ent->Rotate(angleDif, dt);
			ent->MoveForward(dt);
		});

		StateNode	*attackEnemy = NewState();
		attackEnemy->SetFunc([](IScene *sce, GridEntity *ent, float dt)
		{
			GridScene			*gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);
			GridScene::ETeam	type = ent->Team();
			GridScene::ETeam	enemyType = type == GridScene::LION ? GridScene::ANTELOPE : GridScene::LION;

			GridEntity	*nearestEnemy = ent->m_StateMachineAttr.m_NearestEnemy;

			glm::vec3			targetPosition;
			if (nearestEnemy != nullptr)
				targetPosition = nearestEnemy->Position();
			else
				return;

			const glm::vec3		&position = ent->Position();
			const glm::vec3		&forward = ent->Forward();
			const glm::vec3		direction = glm::normalize(targetPosition - position);

			const float angleDif = ISteering::Angle(direction, forward);

			ent->Rotate(angleDif, dt);
			ent->MoveForward(dt);
		});

		ICondition	*isAlone = NewCondition(EFriendDistance, Superior, 1.f);
		ICondition	*isNotAlone = NewCondition(EFriendDistance, Inferior, 1.f);

		ICondition	*isNearFromEnemy = NewCondition(EEnnemyDistance, Inferior, 5.f);
		ICondition	*isNotNearFromEnemy = NewCondition(EEnnemyDistance, Superior, 5.f);

		ICondition	*isSafeToAttack = NewCondition(ENearFriendCount, Superior | Equal, 4);
		ICondition	*isNotSafeToAttack = NewCondition(ENearFriendCount, Inferior, 4);

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
