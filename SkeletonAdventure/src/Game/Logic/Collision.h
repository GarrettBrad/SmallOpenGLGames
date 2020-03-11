#ifndef COLLISON_H
#define COLLISON_H

#include "Game/Entity/BaseEntityStructure.h"
#include "Level/Level.h"

// Checks collision 
class Collision
{
private:
	Collision();

	std::map<ObjectType, bool> m_CollisionAble = {
		{ObjectType::Floor, true},
		{ObjectType::OneWayBlock, true}, // Special
		{ObjectType::Light, false}
	};

	bool IsCollideableInter(const ObjectType& obj);

public:
	Collision(const Collision& col) = delete;

	static Collision& Get();

	static bool IsCollideable(const ObjectType& obj);
	
	static bool BetweenY(const DrawObject& obj, const HitBox& hit);
	static bool BetweenX(const DrawObject& obj, const HitBox& hit);

	static bool BetweenY(const HitBox& box1, const HitBox& box2);
	static bool BetweenX(const HitBox& box1, const HitBox& box2);

	static bool CollisionXLeft(const DrawObject& obj, const HitBox& hit);
	static bool CollisionYUp(const DrawObject& obj, const HitBox& hit);

	static bool CollisionXRight(const DrawObject& obj, const HitBox& hit);
	static bool CollisionYDown(const DrawObject& obj, const HitBox& hit);
};

#endif /* COLLISON_H */