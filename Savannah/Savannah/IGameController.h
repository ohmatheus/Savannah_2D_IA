#pragma once

// This is not optimal at all, and pretty ugly, but i don't want game to be aware of the main window,
// the idea is that the game should be launch from any framework
// should be removed/generalised
//----------------------------------------------------------

struct		SGameParameters
{
	bool	m_IsDirty = false;
	float	m_SimulationSpeed = 1.f;

	int		m_LionSpawnCount;
	int		m_AntelopeSpawnCount;

	float	m_LionVelocity;
	float	m_AntelopeVelocity;

	float	m_LionRotationSpeed;
	float	m_AntelopeRotationSpeed;

	float	m_LionInitialHealth;
	float	m_AntelopeInitialHealth;

	float	m_LionAttackRadius;
	float	m_AntelopeAttackRadius;

	float	m_LionDPS;
	float	m_AntelopeDPS;

	float	m_AntelopeFleeRadius;

	int		m_AntelopeFriendCountToAttack;

	float	m_AntelopeFriendCountRadius;

	float	m_AntelopeLonelinessRadius;
};

//----------------------------------------------------------

class IGameController
{
public:
	IGameController() {}
	virtual ~IGameController() {}

	virtual bool		RequestGameParameters(SGameParameters &from) = 0;

protected:
	SGameParameters		m_GameParameters;
};

//----------------------------------------------------------
