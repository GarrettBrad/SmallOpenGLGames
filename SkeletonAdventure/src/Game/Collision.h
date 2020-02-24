#ifndef COLLISON_H
#define COLLISON_H
#include "Entity/Skeleton.h"
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
	static bool IsCollideable(const ObjectType& obj);

	static Collision& Get();
	
	static bool BetweenY(const DrawObject& obj, const HitBox& hit);
	static bool BetweenX(const DrawObject& obj, const HitBox& hit);

	static bool CollisionXLeft(const DrawObject& obj, const HitBox& hit);
	static bool CollisionYUp(const DrawObject& obj, const HitBox& hit);

	static bool CollisionXRight(const DrawObject& obj, const HitBox& hit);
	static bool CollisionYDown(const DrawObject& obj, const HitBox& hit);
};

#endif /* COLLISON_H */