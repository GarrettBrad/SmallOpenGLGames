#ifndef LOGIC_H
#define LOGIC_H

#include "Collision.h"

// Singleton
class Logic
{
private: // Members
	std::map<WPARAM, bool> m_KeysPressed;

	std::deque<Entity*> m_Entitys; // Holds a pointer to all entities 
	Skeleton m_Skeleton = Skeleton();

private: // Methods
	Logic();

	// Faster to copy than pass by pointer or ref
	Skeleton& GetSkeletonInter();

	void AddEntityInter(Entity* ent);

	void RunInter();

	void CheckInput();
	void Move();

	void KeyPressedInter(WPARAM key);
	void KeyReleasedInter(WPARAM key);
	void MoveSkeletonInter(Direction dir);
	void CheckCollideInter();
public:
	Logic(const Logic& l) = delete;
	static Logic& Get();

	static void Run();

	static Skeleton& GetSkeleton();
	static const Skeleton& cGetSkeleton();

	static void AddEntity(Entity* ent);

	static void KeyPressed(WPARAM key);
	static void KeyReleased(WPARAM key);
	static void MoveSkeleton(Direction dir);
	static void CheckCollide();



};

#endif /* LOGIC_H */
