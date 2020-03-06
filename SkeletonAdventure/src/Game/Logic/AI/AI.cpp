#include "pch.h"
#include "AI.h"

#include "Game/Entity/Enemy/Enemy.h"

const Skeleton* AI::s_Player;

void AI::MoveToPlayer()
{
	Enemy* ent = dynamic_cast<Enemy*> (m_ParentEnt);

	if (!ent) return;

	if (m_ParentEnt->GetX() > s_Player->GetX())
	{
		ent->MoveLeft();
	}
	else if (m_ParentEnt->GetX() < s_Player->GetX())
	{
		ent->MoveRight();
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