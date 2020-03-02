#include "pch.h"
#include "Logic.h"
#include "Collision.h"

// Made private for singleton
Logic::Logic()
{
}

Logic& Logic::Get()
{
	static Logic log;
	return log;
}

// Gets a reference to the skeleton object;
Skeleton& Logic::GetSkeletonInter()
{
	return m_Skeleton;
}
// Gets the Skeleton object
Skeleton& Logic::GetSkeleton()
{
	return Get().GetSkeletonInter();
}
// Gets a const reference to the skeleton object
const Skeleton& Logic::cGetSkeleton()
{
	return Get().GetSkeletonInter();
}

// Checks the input
void Logic::CheckInput()
{
	if (m_KeysPressed[VK_SPACE] || m_KeysPressed[SKEL_KEY_W])
		m_Skeleton.Jump();

	if (m_KeysPressed[SKEL_KEY_D])
		MoveSkeletonInter(Direction::Right);
	
	if (m_KeysPressed[SKEL_KEY_A])
		MoveSkeletonInter(Direction::Left);
}

// Calls all movement
void Logic::Move()
{
	CheckInput();

	m_Skeleton.Move();
}

void Logic::RunInter()
{
	Move();
}
// Moves the skeleton
void Logic::Run()
{
	Get().RunInter();
}

// Called when a key is pressed
void Logic::KeyPressedInter(WPARAM key)
{
	m_KeysPressed[key] = true;
}
// Called when a key is press.
// Handles accordingly
void Logic::KeyPressed(WPARAM key)
{
	Get().KeyPressedInter(key);
}

// Called when a key is released and handles the release
void Logic::KeyReleasedInter(WPARAM key)
{
	m_KeysPressed[key] = false;
}
// Called when a key is released and handles the release
void Logic::KeyReleased(WPARAM key)
{
	Get().KeyReleasedInter(key);
}

// Moves the skeleton
void Logic::MoveSkeletonInter(Direction dir)
{
	if (GetAsyncKeyState(VK_SHIFT))
		m_Skeleton.InSpeedSprint(dir);
	else
		m_Skeleton.InSpeedWalk(dir);
}
// Moves the skeleton
void Logic::MoveSkeleton(Direction dir)
{
	Get().MoveSkeletonInter(dir);
}

// Push back the Skeleton in the X cord
void PushBackX(Skeleton& skel)
{
	skel.SetX(skel.GetX() - skel.GetXSpeed());
	skel.SetXSpeed(0);
}
// Push back the skeleton in the y cord
void PushBackY(Skeleton& skel, Direction dir)
{
	if (dir == Direction::Down) {
		skel.SetY(skel.GetY() + abs(skel.GetYSpeed()));
		skel.SetYSpeed(0);
	}
	else
	{
		skel.SetY(skel.GetY() - skel.GetYSpeed());
		skel.SetYSpeed(0);
	}
}

// Checks to see if the skeleton is colliding with an level object
void Logic::CheckCollideInter()
{
	const std::deque<DrawObject>& obj = Level::GetObjects();

	// Handle Skeleton Collision
	for (const auto& o : obj)
	{
		if (!Collision::IsCollideable(o.Type)) return;

		const HitBox& hit = m_Skeleton.GetHitBox();

		if (Collision::CollisionYUp(o, hit)) {
			m_Skeleton.SetCanJump();
			PushBackY(m_Skeleton, Direction::Up);
		}
		else if (Collision::CollisionYDown(o, hit)) {
			PushBackY(m_Skeleton, Direction::Down);
		}
		else if (Collision::CollisionXLeft(o, hit)) {
			if (m_Skeleton.GetXSpeed() > 0)
				PushBackX(m_Skeleton);
		}
		else if (Collision::CollisionXRight(o, hit)) {
			if (m_Skeleton.GetXSpeed() < 0)
				PushBackX(m_Skeleton);
		}

	}

}
// Checks and handles collision
void Logic::CheckCollide()
{
	Get().CheckCollideInter();
}