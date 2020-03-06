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

	bool IsEnemy() const override final;

	void MoveLeft(int amount = 5);
	void MoveRight(int amount = 5);

	void Jump();

	virtual void Think() override;

};

#endif /* ENEMY_H */
