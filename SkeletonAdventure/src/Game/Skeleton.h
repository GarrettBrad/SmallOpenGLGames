#ifndef SKELETON_H
#define SKELETON_H


enum class ModelType
{
	Walk = 0,
	Run,
	Ready,
	Jump,
	Hit,
	Reborn,
	DeadNear,
	DeadFar,
	Corpse1,
	Corpse2,
	Attack1,
	Attack2

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

class Skeleton
{
private:

	int m_X = 0, m_Y = 0;
	
	int m_XSpeed = 0, m_YSpeed = 0;

	mutable int m_SkeletonShow = 1;
	mutable clock_t time;

	bool m_CanJump = true;

	ModelType m_ModelType = ModelType::Ready;
	Direction m_DirectionFacing = Direction::Right;

	void AdjustSpeed(ModelType model, Direction dir, MovementType movement);
	void DecaySpeed();
	
public:

	bool IsOnGround();
	bool IsRunning(); 
	bool IsWalking();
	bool IsAttacking();

	void Move();
	void Jump();
	void InSpeedSprint(Direction dir);
	void InSpeedWalk(Direction dir);
	void Attack();

	void SetCanJump();
	void SetNoJump();

	const bool& GetCanJump() const;

	ImageInfo GetImage() const;

	const int& GetX() const;
	const int& GetY() const;
	void SetX(int x);
	void SetY(int y);




};

#endif /* SKELETON_H */
