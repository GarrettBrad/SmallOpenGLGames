#ifndef ENTITY_H
#define ENTITY_H

#include "Window/Sprite.h"

#include "BaseEntityStructure.h"

class Entity
{
protected:
	int m_X = 0, m_Y = 0;

	int m_XSpeed = 0, m_YSpeed = 0;

	bool m_CanJump = true;
	bool m_CanAttack = true;

	int m_AttackDamage = 10;
	int m_Health = 100;

	// Used for drawing
	mutable Sprite* m_pSprite = nullptr;
	mutable ImageInfo m_LastInfo = ImageInfo(L" ", false);
	mutable clock_t m_Time = clock();
	mutable clock_t m_DiffShow = NULL;
	mutable ModelType m_ModelType = ModelType::Ready;
	mutable int m_MaxShow = 3; // the amount of an image model there is
	mutable int m_ModelShow = 1;
	mutable int m_DrawOffset = 0;
	mutable int m_FrameDistance = 0;

	// Used for Collision
	Direction m_DirectionFacing = Direction::Right;
	HitBox m_HitBox = { 0 };


	virtual void UpdateHitBox() = 0;


public:
	virtual HitBox GetAttackHitBox();
	static constexpr int c_SpeedDecay = 2;

	virtual ImageInfo GetImage() const = 0;
	virtual Sprite* GetSprite() const;
	virtual void SetModel(ModelType mdl, clock_t nextChange = CLOCKS_PER_SEC) const;

	virtual void DecaySpeed();
	virtual void Move();
	virtual void MoveLeft(int amount = 5);
	virtual void MoveRight(int amount = 5);
	virtual void Jump();

	virtual void Think();

	virtual bool IsSkeleton() const;
	virtual bool IsKnight() const;
	virtual bool IsFriendly() const;
	virtual bool IsEnemy() const;

	virtual void SetCanJump();
	virtual void SetNoJump();
	virtual bool CanJump() const;

	virtual void SetAttack(bool attack);
	virtual void SetCanAttack();
	virtual void SetNoAttack();
	virtual bool CanAttack() const;
	virtual std::vector<Entity*> Attack();

	virtual int GetAttackDamage() const;
	virtual void SetAttackDamage(int dmg);
	virtual void Damage(int amount);

	virtual void Kill();

	// Unlikely will be overriden but is avalible
	virtual const HitBox& GetHitBox() const;

	virtual int Health() const;
	virtual void SetHealth(int health);

	virtual int GetXSpeed() const;
	virtual int GetYSpeed() const;
	virtual void SetXSpeed(int x);
	virtual void SetYSpeed(int y);

	virtual int GetX() const;
	virtual int GetY() const;
	virtual void SetX(int x);
	virtual void SetY(int y);

	Entity();
	virtual ~Entity();
};

#endif /* ENTITY_H */
