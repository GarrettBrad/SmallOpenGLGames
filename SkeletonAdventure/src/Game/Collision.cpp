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

///			----------	// Entity
///				||		// Wall
/// TRUE
///			----------	// Entity
///		  ||			// Wall 
/// FALSE
// Checks collison on the left side of the given obj and not past ot
bool Collision::CollisionXLeft(const DrawObject& obj, const HitBox& hit)
{

	// Check we are to the right of the left side
	if (hit.BottomRight.X > obj.TopLeft.X)
	{
		if (hit.BottomRight.Y > obj.TopLeft.Y + 11) // - 1 to stop a glitch
		{
			if (hit.TopLeft.Y < obj.BottomRight.Y - 11)
			{
				return hit.TopLeft.X < obj.TopLeft.X;
			}
		}
	}

	return false;
}

// Checks collison on the top of an object
bool Collision::CollisionYUp(const DrawObject& obj, const HitBox& hit)
{
	// Check we are above the object on the lowest point of the hitbox
	if (hit.BottomRight.Y > obj.TopLeft.Y)
	{
		if (hit.BottomRight.X > obj.TopLeft.X + 10)
		{
			if (hit.TopLeft.X < obj.BottomRight.X - 10)
			{
				return (hit.TopLeft.Y < obj.TopLeft.Y);
			}
		}
	}

	return false;
}

// Checks collison to the right of the given object
bool Collision::CollisionXRight(const DrawObject& obj, const HitBox& hit)
{
	// Check we are to the left to the right side
	if (hit.TopLeft.X < obj.BottomRight.X)
	{
		if (hit.BottomRight.Y > obj.TopLeft.Y + 11) // - 1 to stop a glitch
		{
			if (hit.TopLeft.Y < obj.BottomRight.Y - 11)
			{
				return hit.BottomRight.X > obj.BottomRight.X;
			}
		}
	}

	return false;
}

// checks collision to the bottom of the object
bool Collision::CollisionYDown(const DrawObject& obj, const HitBox& hit)
{

	// The top of the hitbox is past the bottom of the bottom
	if (hit.TopLeft.Y < obj.BottomRight.Y)
	{
		if (hit.BottomRight.Y > obj.BottomRight.Y + 10)
		{
			if (hit.BottomRight.X > obj.TopLeft.X - 10)
			{
				return (hit.TopLeft.X < obj.BottomRight.X);
			}
		}
	}

	return false;
}
