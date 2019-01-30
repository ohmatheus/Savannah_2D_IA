#include "stdafx.h"

#include "AntelopeSM.h"
#include "StateNode.h"
#include "SimpleEntity.h"
#include "GridScene.h"

namespace
{
	glm::vec2 CrossProduct(const glm::vec2 & v)
	{
		return glm::vec2(v.y, -v.x);
	}

	float		CrossProduct(const glm::vec2 &v1, const glm::vec2 &v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
}

namespace StateMachine
{
	AntelopeStateMachine::AntelopeStateMachine(IScene *scene)
	:	Super(scene)
	{
		StateNode *idle = NewState();
		m_Root = idle;
		idle->SetFunc([](IScene *sce, SimpleEntity *ent, float dt)
		{
			GridScene *gridScene = static_cast<GridScene*>(sce);
			assert(gridScene != nullptr);

			glm::vec3			targetPosition = gridScene->GetFlagsEntity(GridScene::LION)->Position();

			const glm::mat4		model = ent->ModelMatrix();
			const glm::vec3		&position = ent->Position();
			glm::vec3			directionVector = model * glm::vec4(0.f, 1.f, 0.f, 0.f);
			directionVector = glm::normalize(directionVector);
			const glm::vec3		diff = glm::normalize(targetPosition - position);
			const float			dot = glm::dot(diff, directionVector);
			const float			cross = CrossProduct(glm::vec2(directionVector), glm::vec2(diff));
			const float			acosDot = glm::acos(dot);
			const float			angleDif = glm::degrees(acosDot);

			ent->Rotate((cross < 0 ? -1 : 1) * angleDif, dt);
			ent->MoveForward(dt);
		});
	}

//----------------------------------------------------------

	AntelopeStateMachine::~AntelopeStateMachine()
	{}

//----------------------------------------------------------
}
