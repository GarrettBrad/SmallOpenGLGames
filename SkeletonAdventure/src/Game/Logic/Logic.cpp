#include "pch.h"
#include "Logic.h"
#include "Collision.h"

#include "Game/Entity/Enemy/Knight.h"

// Used for debugging : Will increase and decrease with the arrow keys
#if _DEBUG
unsigned int g_UpDown = 0;
unsigned int g_LeftRight = 0;
#endif

// Made private for singleton
Logic::Logic()
{
	AI::SetSkeleton(&m_Skeleton);

	// temp;
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
		if (e && !e->IsSkeleton()) // Skeleton is created on the stack
		{
			delete e;
			e = nullptr;
		}	
	}
}

// Gets the current instance of the Logic class
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

// Returns all entities in a std::deque
std::deque<Entity*>& Logic::GetEntityInter()
{
	return m_Entitys;
}
// returns all entities in a std::deque
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

// Removes the entity from the entity list and frees the entity's memory
void Logic::EntityKilledInter(Entity* ent)
{

	std::deque<Entity*>::iterator it = std::find(m_Entitys.begin(), m_Entitys.end(), ent);

	// removes the entity pointer from the deque and frees the memory at that location
	if (it != m_Entitys.end())
	{
		m_Entitys.erase(it);

		delete ent;

		ent = nullptr;
	} // else nothing
}
// Removes the entity from the entity list and frees the entity's memory
void Logic::EntityKilled(Entity* ent)
{
	Get().EntityKilledInter(ent);
}

// Checks the input
void Logic::CheckInput()
{
#if _DEBUG
	if (m_KeysPressed[VK_UP])
		g_UpDown++;
	else if (m_KeysPressed[VK_DOWN])
		g_UpDown--;

	if (m_KeysPressed[VK_LEFT])
		g_LeftRight--;
	else if (m_KeysPressed[VK_RIGHT])
		g_LeftRight++;
#endif

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

// Called every frame to analyze and handle logic
void Logic::RunInter()
{
	CheckCollideInter();

	// Calls the think method for all entities
	for (auto e : m_Entitys)
		e->Think();

	Move();
}
// Called every frame to analyze and handle logic
void Logic::Run()
{
	Get().RunInter();
}

// Called when the mouse is clicked : Handles mouse input
void Logic::MouseDownInter()
{
	std::vector<Entity*> ents = m_Skeleton.Attack();

	for (auto e : ents)
	{
		e->SetModel(ModelType::Hit, (clock_t) CLOCKS_PER_SEC * 1.5f);
		e->Damage(m_Skeleton.GetAttackDamage());
	}
}
// Called when the mouse is clicked
void Logic::MouseDown()
{
	Get().MouseDownInter();
}

// Called when the mouse is released : Handles mouse input
void Logic::MouseUpInter()
{
	// Nothing Currently
}
// Called when the mouse is released
void Logic::MouseUp()
{
	Get().MouseUpInter();
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
		if (!ent) continue;
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



