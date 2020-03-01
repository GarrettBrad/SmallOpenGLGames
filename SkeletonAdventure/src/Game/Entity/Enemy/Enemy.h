#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity/Entity.h"


class Enemy : public Entity
{
private:


public:

	bool IsEnemy() const override final;

};

#endif /* ENEMY_H */
