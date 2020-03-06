#ifndef ENTITY_H
#define ENTITY_H

#include "Window/Sprite.h"

#include "BaseEntityStructure.h"

class Entity
{
protected:
	int m_X = 0, m_Y = 0;

	int m_XSpeed = 0, m_YSpeed = 0;

	// Used for drawing
	mutable int m_ModelShow = 1;
	mutable int m_MaxShow = 3; // the amount of an image model there is
	mutable clock_t m_Time = NULL;
	ModelType m_ModelType = ModelType::Ready;

	Direction m_DirectionFacing = Direction::Right;
	HitBox m_HitBox = { 0 };

	mutable ImageInfo m_LastInfo = ImageInfo(L" ", false);
	mutable Sprite* m_pSprite = nullptr;

	virtual void UpdateHitBox() = 0;

public:
	static constexpr int c_SpeedDecay = 2;

	virtual ImageInfo GetImage() const = 0;
	virtual Sprite* GetSprite() const;

	virtual void DecaySpeed();
	virtual void Move();

	virtual void Think();

	virtual HitBox Attack() const;

	virtual bool IsSkeleton() const;
	virtual bool IsEnemy() const;

	// Unlikely will be overriden but is avalible
	virtual const HitBox& GetHitBox() const;

	virtual const int& GetXSpeed() const;
	virtual const int& GetYSpeed() const;
	virtual void SetXSpeed(int x);
	virtual void SetYSpeed(int y);

	virtual const int& GetX() const;
	virtual const int& GetY() const;
	virtual void SetX(int x);
	virtual void SetY(int y);

	Entity();
	~Entity();
};

#endif /* ENTITY_H */
