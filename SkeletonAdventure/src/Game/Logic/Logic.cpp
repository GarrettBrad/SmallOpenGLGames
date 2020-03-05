#include "pch.h"
#include "Logic.h"
#include "Collision.h"

#include "Game/Entity/Enemy/Knight.h"

// Made private for singleton
Logic::Logic()
{
	Knight* knight = new Knight();

	knight->SetX(100);
	knight->SetXSpeed(20);

	m_Entitys.emplace_back(knight);
	m_Entitys.emplace_back(&m_Skeleton);
}

// Cleanup
Logic::~Logic()
{
	// Clean up;
	for (auto e : m_Entitys)
	{
		if (e && !e->IsSkeleton()) delete e;
	}
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

std::deque<Entity*>& Logic::GetEntityInter()
{
	return m_Entitys;
}
std::deque<Entity*>& Logic::GetEntities()
{
	return Get().GetEntityInter();
} 

// Adds an entity to the entity list
void Logic::AddEntityInter(Entity* ent)
{
	m_Entitys.emplace_back(ent);
}
// Adds an entity to the entity list : DO NOT Logic::AddEntity(new Knight());
void Logic::AddEntity(Entity* ent)
{
	Get().AddEntityInter(ent);
}

// Checks the input
void Logic::CheckInput()
{
	if ((m_KeysPressed[VK_SPACE] || m_KeysPressed[SKEL_KEY_W]) && m_Skeleton.CanJump())
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

	for (auto ent : m_Entitys)
	{
		ent->Move();
	}
}

void Logic::RunInter()
{
	Move();

	CheckCollideInter();
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
void PushBackX(Entity* ent)
{
	ent->SetX(ent->GetX() - ent->GetXSpeed());
	ent->SetXSpeed(0);
}
// Push back the skeleton in the y cord
void PushBackY(Entity* ent, Direction dir)
{
	if (dir == Direction::Down) {
		ent->SetY(ent->GetY() + abs(ent->GetYSpeed()));
		ent->SetYSpeed(0);
	}
	else { // Direction::Up
		ent->SetY(ent->GetY() - ent->GetYSpeed());
		ent->SetYSpeed(0);
	}
}

// Checks to see if the skeleton is colliding with an level object
void Logic::CheckCollideInter()
{
	// Loops through all entities for collision
	for (auto& ent : m_Entitys)
	{
		// Handle Entity Collision
		for (const auto& o : Level::GetObjects())
		{
			if (!Collision::IsCollideable(o.Type)) return;

			const HitBox& hit = ent->GetHitBox();

			if (Collision::CollisionYUp(o, hit)) {
				if (ent->IsSkeleton())
					m_Skeleton.SetCanJump(); // Luckily the skeleton is its own var C;
	
				PushBackY(ent, Direction::Up);
			}
			else if (Collision::CollisionYDown(o, hit)) {
				PushBackY(ent, Direction::Down);
			}
			else if (Collision::CollisionXLeft(o, hit)) {
				if (ent->GetXSpeed() > 0)
					PushBackX(ent);
			}
			else if (Collision::CollisionXRight(o, hit)) {
				if (ent->GetXSpeed() < 0)
					PushBackX(ent);
			}
		}

		ent->DecaySpeed();

	}

}
// Checks and handles collision
void Logic::CheckCollide()
{
	Get().CheckCollideInter();
}



