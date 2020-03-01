#include "pch.h"
#include "Entity.h"

// decays the speed of 
void Entity::DecaySpeed()
{
	
	do
	{
		if (m_XSpeed == 0)
			break;

		if (m_XSpeed > 0)
			m_XSpeed -= c_SpeedDecay;
		else if (m_XSpeed < 0)
			m_XSpeed += c_SpeedDecay;
	} while (false);

	m_YSpeed += SKELETON_GRAVITY;

	if (m_YSpeed > SKELETON_GRAVITY_MAX)
		m_YSpeed = SKELETON_GRAVITY_MAX;
}

// Will move the player by the speed.
void Entity::Move()
{
	m_X += m_XSpeed;
	m_Y += m_YSpeed;

	UpdateHitBox();


	DecaySpeed();
}

// Returns the hitbox where the skeleton attacked
// Does not register hit.
// Use the returned Hit Box
[[nodiscard]]
HitBox Entity::Attack() const
{
	// TODO: add attacking

	if (m_DirectionFacing == Direction::Left)
		return {
			{ m_HitBox.BottomRight.X, m_HitBox.BottomRight.Y - 10 },
			{ m_HitBox.TopLeft.X - 40, m_HitBox.TopLeft.Y + 10 }
	};
	else
		return {
			{ m_HitBox.BottomRight.X + 40, m_HitBox.BottomRight.Y - 10 },
			{ m_HitBox.TopLeft.X, m_HitBox.TopLeft.Y + 10 }
	};

}

// returns if the entity is a skeleton
bool Entity::IsSkeleton() const
{
	return false;
}

// returns if the entity is a Enemy to the skeleton
bool Entity::IsEnemy() const
{
	return false;
}

// Returns the hit box of the entity
const HitBox& Entity::GetHitBox() const
{
	return m_HitBox;
}

// Gets x speed
const int& Entity::GetXSpeed() const
{
	return m_XSpeed;
}

// Gets y Speed
const int& Entity::GetYSpeed() const
{
	return m_YSpeed;
}

// Sets X Speed
void Entity::SetXSpeed(int x)
{
	m_XSpeed = x;
}

// Sets y Speed
void Entity::SetYSpeed(int y)
{
	m_YSpeed = y;
}

// Gets the x pos value
const int& Entity::GetX() const
{
	return m_X;
}

// Gets the y Pos value
const int& Entity::GetY() const
{
	return m_Y;
}

// Sets the xvalue of the entity
void Entity::SetX(int x)
{
	m_X = x;
}

// Sets the yvalue of the entity
void Entity::SetY(int y)
{
	m_Y = y;
}
