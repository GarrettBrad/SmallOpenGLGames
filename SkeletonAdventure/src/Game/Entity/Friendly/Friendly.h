#ifndef FRIENDLY_H
#define FRIENDLY_H

#include "Game/Entity/Entity.h"
#include "Game/Logic/AI/AI.h"

class Friendly : public Entity
{
private:
	// A Friendly AI
	AI m_Ai = AI(true, this); // All enemies have AI

public:

	inline const AI& cGetAI() const { return m_Ai; }
	inline AI& GetAI() { return m_Ai; }

	bool IsFriendly() const final override; // All enemys are not friendly
	bool IsEnemy() const final override;

	virtual void Think() override;

};

#endif /* FRIENDLY_H */
