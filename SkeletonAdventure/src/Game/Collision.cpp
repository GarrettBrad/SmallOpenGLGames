#include "pch.h"
#include "Collision.h"

Collision::Collision()
{}

// Returns if the object is colliable
bool Collision::IsCollideableInter(const ObjectType& obj)
{
	return m_CollisionAble.at(obj);
}
// Returns if the object is colliable
bool Collision::IsCollideable(const ObjectType& obj)
{
	return Get().IsCollideableInter(obj);
}

// Gets the current instance of this
Collision& Collision::Get()
{
	static Collision coli;
	return coli;
}

// Checks to see if the Hitbox is between the objects Y cords
bool Collision::BetweenY(const DrawObject& obj, const HitBox& hit)
{
	return (hit.BottomRight.Y - 1 > obj.TopLeft.Y&& hit.TopLeft.Y + 1 < obj.BottomRight.Y);
}

// Checks to see if the hitbox is between the ojbects X cords
bool Collision::BetweenX(const DrawObject& obj, const HitBox& hit)
{
	return (hit.BottomRight.X > obj.TopLeft.X + 1 && hit.TopLeft.X < obj.BottomRight.X - 1);
}

// a visual example
///			----------	// Entity
///				||		// Wall
/// TRUE
///			----------	// Entity
///		  ||			// Wall 
/// FALSE

// Checks collison on the left side of the given obj and not past ot
bool Collision::CollisionXLeft(const DrawObject& obj, const HitBox& hit)
{
	if (hit.BottomRight.X > obj.TopLeft.X && obj.TopLeft.X + 11 > hit.BottomRight.X) {

		return BetweenY(obj, hit);
		//if (hit.BottomRight.Y - 1 > obj.TopLeft.Y && hit.TopLeft.Y + 1 < obj.BottomRight.Y) {
		//	return true;
		//}
	}

	return false;
}

// Checks collison on the top of an object
bool Collision::CollisionYUp(const DrawObject& obj, const HitBox& hit)
{

	if (hit.BottomRight.Y > obj.TopLeft.Y &&  hit.BottomRight.Y < obj.TopLeft.Y + 11) {
		return BetweenX(obj, hit);
		
		/*if (hit.BottomRight.X > obj.TopLeft.X + 1 && hit.TopLeft.X < obj.BottomRight.X - 1) {
			return true;
		}*/
	}

	return false;
}

// Checks collison to the right of the given object
bool Collision::CollisionXRight(const DrawObject& obj, const HitBox& hit)
{
	if (hit.TopLeft.X < obj.BottomRight.X && obj.BottomRight.X - 11 < hit.TopLeft.X) {
		return BetweenY(obj, hit);

		/*if (hit.BottomRight.Y - 1 > obj.TopLeft.Y && hit.TopLeft.Y + 1 < obj.BottomRight.Y) {
			return true;
		}*/
	}

	return false;
}

// checks collision to the bottom of the object
bool Collision::CollisionYDown(const DrawObject& obj, const HitBox& hit)
{
	if (hit.TopLeft.Y < obj.BottomRight.Y && obj.BottomRight.Y - 11 < hit.TopLeft.Y)
		return BetweenX(obj, hit);

	return false;
}
