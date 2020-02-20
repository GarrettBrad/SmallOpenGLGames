#include "pch.h"

#include "Skeleton.h"

// Changes the speed, the direction the model is facing, and the model for the movement type (i.e. jump or sprint or walk)
void Skeleton::AdjustSpeed(ModelType model, Direction dir, MovementType movement)
{
	m_ModelType = model;

	// Changes the facing direction of the skeleton
	if (dir == Direction::Left || dir == Direction::Right) {
		m_DirectionFacing = dir;
	}

	// Which kind of movement do we want
	switch (movement)
	{
		// TODO: Make the MovementType::Run and Walk to a function for better maintance
		case (MovementType::Run):
		{
			if (dir == Direction::Right) {
				m_XSpeed += SKELETON_SPEED_INCORMENT;

				if (m_XSpeed > SKELETON_RUN_SPEED)
					m_XSpeed = SKELETON_RUN_SPEED;
			}
			else if (dir == Direction::Left)
			{
				m_XSpeed -= SKELETON_SPEED_INCORMENT;

				if (m_XSpeed < -SKELETON_RUN_SPEED)
					m_XSpeed = -SKELETON_RUN_SPEED;
			}

			break;
		}
		case (MovementType::Walk):
		{
			if (dir == Direction::Right) {
				m_XSpeed += SKELETON_SPEED_INCORMENT;

				if (m_XSpeed > SKELETON_WALK_SPEED)
					m_XSpeed = SKELETON_WALK_SPEED;
			}
			else if (dir == Direction::Left)
			{
				m_XSpeed -= SKELETON_SPEED_INCORMENT;

				if (m_XSpeed < -SKELETON_WALK_SPEED)
					m_XSpeed = -SKELETON_WALK_SPEED;
			}

			break;
		}
		case (MovementType::Jump):
		{
			m_YSpeed -= SKELETON_JUMP_SPEED;
		}
	}


}

void Skeleton::DecaySpeed()
{
	if (m_XSpeed > 0)
	{
		m_XSpeed -= SKELETON_SPEED_INCORMENT;
	}
	if (m_XSpeed < 0)
	{
		m_XSpeed += SKELETON_SPEED_INCORMENT;
	}

	m_YSpeed += SKELETON_GRAVITY;

	if (m_YSpeed > SKELETON_GRAVITY_MAX)
		m_YSpeed = SKELETON_GRAVITY_MAX;
}

// Will move the player by the speed.
void Skeleton::Move()
{
	m_X += m_XSpeed;
	m_Y += m_YSpeed;

	DecaySpeed();
}

// Make the skeleton jump
void Skeleton::Jump()
{
	if (!m_CanJump) return;
	
	SetNoJump();

	AdjustSpeed(ModelType::Jump, Direction::Up, MovementType::Jump);
}

// Move move key and sprint key are pressed
void Skeleton::InSpeedSprint(Direction dir)
{
	AdjustSpeed(ModelType::Run, dir, MovementType::Run);
}

// Move Key is pressed but not sprint
void Skeleton::InSpeedWalk(Direction dir)
{
	AdjustSpeed(ModelType::Walk, dir, MovementType::Walk);
}

// attack key is pressed
void Skeleton::Attack()
{

}

// to be added
bool Skeleton::IsOnGround()
{
	// Allows jumping inbetween this speed
	return (m_YSpeed < 0.01f && m_YSpeed > -.01f);
}

// Is attacking
bool Skeleton::IsAttacking()
{
	return false;
}

// Is Running()
bool Skeleton::IsRunning()
{
	// the -0.02 is a cushion for floating point numbers
	return (m_XSpeed >= (SKELETON_RUN_SPEED - 0.02f));
	
}

// Is Walking
bool Skeleton::IsWalking()
{
	return false;
}

void Skeleton::SetCanJump()
{
	m_CanJump = true;
}

void Skeleton::SetNoJump()
{
	m_CanJump = false;
}

const bool& Skeleton::GetCanJump() const
{
	return m_CanJump;
}

ImageInfo Skeleton::GetImage() const
{
	
	if (time < clock())
	{
		m_SkeletonShow++;

		if (m_SkeletonShow > 3)
			m_SkeletonShow = 1;
		
		time = clock() + SKELETON_SWTICH_TIME;
	}

	bool flip = false;

	if (m_DirectionFacing == Direction::Left)
		flip = true;

	if (m_SkeletonShow == 1)
		return { L"resources/Skeleton/ready_1.png", flip };
	else if (m_SkeletonShow == 2)
		return { L"resources/Skeleton/ready_2.png", flip };
	else
		return { L"resources/Skeleton/ready_3.png", flip };


}

// Gets the x pos value
const int& Skeleton::GetX() const
{
	return m_X;
}

// Gets the y Pos value
const int& Skeleton::GetY() const
{
	return m_Y;
}

void Skeleton::SetX(int x)
{
	m_X = x;
}

void Skeleton::SetY(int y)
{
	m_Y = y;
}
