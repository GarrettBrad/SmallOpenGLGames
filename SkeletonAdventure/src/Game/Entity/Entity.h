#ifndef ENTITY_H
#define ENTITY_H

// 2 dimensional vector
struct Vector2D
{
	int X, Y;
};

// The box which can be hit
struct HitBox
{
	Vector2D TopLeft;
	Vector2D BottomRight;
};

enum class Direction
{
	Up = 0,
	Down,
	Left,
	Right
};

enum class MovementType
{
	Walk = 0,
	Run,
	Jump
};

struct ImageInfo
{
	const wchar_t* file;
	bool flipped = false;

	ImageInfo(const wchar_t* file, bool flipped)
		: file(file), flipped(flipped)
	{}
};

class Entity
{
protected:
	int m_X = 0, m_Y = 0;

	int m_XSpeed = 0, m_YSpeed = 0;

	Direction m_DirectionFacing = Direction::Right;
	HitBox m_HitBox;

	virtual void DecaySpeed();
	virtual void UpdateHitBox() = 0;

public:
	static constexpr int c_SpeedDecay = 2;

	virtual ImageInfo GetImage() const = 0;

	virtual void Move();

	virtual bool IsSkeleton() const;

	virtual const HitBox& GetHitBox() const;

	virtual const int& GetXSpeed() const;
	virtual const int& GetYSpeed() const;
	virtual void SetXSpeed(int x);
	virtual void SetYSpeed(int y);

	virtual const int& GetX() const;
	virtual const int& GetY() const;
	virtual void SetX(int x);
	virtual void SetY(int y);
};

#endif /* ENTITY_H */
