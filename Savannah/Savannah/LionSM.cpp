#include "stdafx.h"

#include "LionSM.h"
#include "StateNode.h"
#include "Transition.h"
#include "GridEntity.h"
#include "GridScene.h"
#include "Steering.h"

namespace StateMachine
{
	LionStateMachine::LionStateMachine(IScene *scene)
	: Super(scene)
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

			ent->Seek(targetPosition, dt);
		});

		StateNode	*makeFriends = NewState(); // ???
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

		ICondition	*isAlone = NewCondition(EFriendDistance, Superior, 1.f);
		ICondition	*isNotAlone = NewCondition(EFriendDistance, Inferior, 1.f);

		NewTransition(idle, goForFlag, isNotAlone);

		//Transition	*makeFriendsToGoForFlag = NewTransition(goForFlag, isNotAlone);
		//makeFriends->AddTransition(makeFriendsToGoForFlag);

	}

	//----------------------------------------------------------

	LionStateMachine::~LionStateMachine()
	{}

	//----------------------------------------------------------
}
