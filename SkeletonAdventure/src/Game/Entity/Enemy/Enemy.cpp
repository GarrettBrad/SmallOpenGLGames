#include "pch.h"
#include "Enemy.h"

// Returns false
bool Enemy::IsFriendly() const
{
	return false;
}

// Returns true
bool Enemy::IsEnemy() const
{
	return true;
}

void Enemy::Think()
{
	m_Ai.Think();
}
