#include "pch.h"
#include "Enemy.h"

bool Enemy::IsEnemy() const
{
	return true;
}

void Enemy::Think()
{
	m_Ai.Think();
}
