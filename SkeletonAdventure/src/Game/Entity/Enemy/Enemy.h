#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity/Entity.h"
#include "Game/Logic/AI/AI.h"


class Enemy : public Entity
{
private:
	// A AI hostel AI
	AI m_Ai = AI(false, this); // All enemies have AI

public:

	inline const AI& cGetAI() const { return m_Ai;}
	inline AI& GetAI() { return m_Ai; }

	bool IsFriendly() const final override; // All enemys are not friendly
	bool IsEnemy() const final override;

	virtual void Think() override;

	virtual ~Enemy();

};

#endif /* ENEMY_H */
