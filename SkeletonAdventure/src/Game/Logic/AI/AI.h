#ifndef AI_H
#define AI_H


#include "Game/Entity/Entity.h"
#include "Game/Entity/Skeleton.h"

class AI
{
private:
	bool m_Friendly;
	Entity* m_ParentEnt;

	static const Skeleton* s_Player;

	std::array<int, 3> m_LastXCords; // 3rd element is the current pos

private:

	void MoveToPlayer();
public:


	const float c_DistanceToTrack = 500.f; // The distance in which an AI will tack

	void EnemyThink();
	void FriendlyThink();
	void Think();

	AI(bool friendly, Entity* ent);

	static void SetSkeleton(const Skeleton* skel);
};

#endif /* AI_H */
