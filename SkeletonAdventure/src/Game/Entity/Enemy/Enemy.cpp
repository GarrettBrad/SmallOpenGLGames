#include "pch.h"
#include "Enemy.h"

bool Enemy::IsEnemy() const
{
	return true;
}

void Enemy::MoveLeft(int amount)
{
	SetXSpeed(-amount);
}

// Moves the entity to the
void Enemy::MoveRight(int amount)
{
	SetXSpeed(amount);
}

void Enemy::Jump()
{

}

void Enemy::Think()
{
	m_Ai.Think();
}
