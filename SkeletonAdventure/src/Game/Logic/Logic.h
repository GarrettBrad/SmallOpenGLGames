#ifndef LOGIC_H
#define LOGIC_H

#include "Collision.h"

// Singleton
class Logic
{
private: // Members
	std::map<WPARAM, bool> m_KeysPressed;

	std::deque<Entity*> m_Entitys; // Holds a pointer to all entities // TODO make std::week_ptr
	Skeleton m_Skeleton = Skeleton();

private: // Methods
	Logic();

	// Faster to copy than pass by pointer or ref
	Skeleton& GetSkeletonInter();

	void InputMoveSkeleton(Direction dir);

	void CheckInput();
	void MoveInter();

	void KeyPressedInter(WPARAM key);
	void KeyReleasedInter(WPARAM key);
	void MoveSkeletonInter(Direction dir);
	void CheckCollideInter();
public:
	Logic(const Logic& l) = delete;
	static Logic& Get();

	static Skeleton& GetSkeleton();
	static const Skeleton& cGetSkeleton();

	static void Move();
	static void KeyPressed(WPARAM key);
	static void KeyReleased(WPARAM key);
	static void MoveSkeleton(Direction dir);
	static void CheckCollide();



};

#endif /* LOGIC_H */
