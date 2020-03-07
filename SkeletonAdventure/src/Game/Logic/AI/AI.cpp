#include "pch.h"
#include "AI.h"

#include "Game/Entity/Enemy/Enemy.h"

const Skeleton* AI::s_Player;

// Moves the AI to the player
void AI::MoveToPlayer()
{
	// YSpeed is 1 if the gravity is 0
	if (m_ParentEnt->GetYSpeed() == 1 && m_ParentEnt->GetXSpeed() == 0)
		m_ParentEnt->Jump();

	if (m_ParentEnt->GetX() > s_Player->GetX() + 5)
	{
		m_ParentEnt->MoveLeft();
	}
	else if (m_ParentEnt->GetX() < s_Player->GetX() - 5)
	{
		m_ParentEnt->MoveRight();
	}



}

// A hostel AI think
void AI::EnemyThink()
{
	float distance = (sqrt( // Distance formula
		pow(m_ParentEnt->GetX() - s_Player->GetX(), 2) +
		pow(m_ParentEnt->GetY() - s_Player->GetY(), 2)
	));

	if (distance < c_DistanceToTrack)
	{
		MoveToPlayer();
	}
}

// A friendly AI think
void AI::FriendlyThink()
{

}

// Called every frame.
// Does all logic
void AI::Think()
{

	for (int i = 0; i < m_LastXCords.size(); i++)
	{
		if (i == m_LastXCords.size() - 1)
		{	
			m_LastXCords[i] = m_ParentEnt->GetX();
			break;
		}

		m_LastXCords[i] = m_LastXCords[i + 1];
	}

	// if the AI is a enemy to the player
	if (!m_Friendly)
		EnemyThink();
	else
		FriendlyThink();
}

AI::AI(bool friendly, Entity* ent)
	: m_Friendly(friendly), m_ParentEnt(ent)
{

}

// Sets the AI skeleton pointer to the pointer given
void AI::SetSkeleton(const Skeleton* skel)
{
	s_Player = skel;

}