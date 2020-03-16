#include "pch.h"

#include "Skeleton.h"
#include "Game/Logic/Logic.h"

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
				m_XSpeed += SKELETON_SPEED_INCREASE;

				if (m_XSpeed > SKELETON_RUN_SPEED)
					m_XSpeed = SKELETON_RUN_SPEED;
			}
			else if (dir == Direction::Left)
			{
				m_XSpeed -= SKELETON_SPEED_INCREASE;

				if (m_XSpeed < -SKELETON_RUN_SPEED)
					m_XSpeed = -SKELETON_RUN_SPEED;
			}

			break;
		}
		case (MovementType::Walk):
		{
			if (dir == Direction::Right) {
				m_XSpeed += SKELETON_SPEED_INCREASE;

				if (m_XSpeed > SKELETON_WALK_SPEED)
					m_XSpeed = SKELETON_WALK_SPEED;
			}
			else if (dir == Direction::Left)
			{
				m_XSpeed -= SKELETON_SPEED_INCREASE;

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

// slows down the speed
void Skeleton::DecaySpeed()
{
	if (m_XSpeed > 0)
	{
		m_XSpeed -= SKELETON_SPEED_DECREASE;
	}
	if (m_XSpeed < 0)
	{
		m_XSpeed += SKELETON_SPEED_DECREASE;
	}

	m_YSpeed += SKELETON_GRAVITY;

	if (m_YSpeed > SKELETON_GRAVITY_MAX)
		m_YSpeed = SKELETON_GRAVITY_MAX;
}

// Updates the hitbox to the new postion
void Skeleton::UpdateHitBox()
{
	m_HitBox.TopLeft.X = m_X + 40;
	m_HitBox.TopLeft.Y = m_Y + 30;
	m_HitBox.BottomRight.X = m_X + (int) (m_Size.width * SKEL_DEFUALT_SKELETON_SCALE * 1.5f) + 20;
	m_HitBox.BottomRight.Y = m_Y + (int) (m_Size.height * SKEL_DEFUALT_SKELETON_SCALE * 1.5f) - 3;
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

// returns true
bool Skeleton::IsSkeleton() const
{
	return true;
}

// returns true
bool Skeleton::IsFriendly() const
{
	return true;
}

// Returns the amount of damage the entity deals
int Skeleton::GetAttackDamage() const
{
	return m_AttackDamage;
}

// gets the current image that the skeleton should be displaying
ImageInfo Skeleton::GetImage() const
{
	
	if (m_Time < clock())
	{
		m_ModelShow++;
		
		m_Time = clock() + SKELETON_SWTICH_TIME;
	}

	bool flip = false;

	if (m_DirectionFacing == Direction::Left)
		flip = true;

	switch (m_ModelType)
	{
		case ModelType::Walk:
		{
			m_MaxShow = m_WalkModels.size();
			
			return { m_WalkModels[m_ModelShow % m_MaxShow], flip };
		}
		case ModelType::Run:
		{
			m_MaxShow = m_RunModels.size();

			return { m_RunModels[m_ModelShow % m_MaxShow], flip };
		}
		case ModelType::Attack1:
		{
			m_MaxShow = m_Attack1Models.size();
			return { m_Attack1Models[m_ModelShow % m_MaxShow], flip };
		}
		default: // Ready
		{
			m_MaxShow = 3;

			return { m_ReadyModels[m_ModelShow % m_MaxShow], flip };
		}
	}


}

// Gets the size of the skeleton
[[DEPRECATED]]
const D2D1_SIZE_F Skeleton::GetSize() const
{
	return m_Size;
}

void Skeleton::Think()
{
	if (m_DiffShow > clock())
		return;

	if (abs(m_XSpeed) < 1)
		m_ModelType = ModelType::Ready;
}