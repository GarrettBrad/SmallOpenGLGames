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
				m_XSpeed -= -SKELETON_SPEED_INCORMENT;

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
				m_XSpeed -= -SKELETON_SPEED_INCORMENT;

				if (m_XSpeed < -SKELETON_WALK_SPEED)
					m_XSpeed = -SKELETON_WALK_SPEED;
			}

			break;
		}
	}


}

// Will move the player by the speed.
void Skeleton::Move()
{
	m_X += m_XSpeed;
	m_Y += m_YSpeed;
}

// Make the skeleton jump
void Skeleton::Jump()
{
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