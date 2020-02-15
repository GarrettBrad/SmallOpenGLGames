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

class Skeleton
{
private:

	float m_X = 0, m_Y = 0;
	
	float m_XSpeed = 0, m_YSpeed = 0;

	ModelType m_ModelType = ModelType::Ready;
	Direction m_DirectionFacing = Direction::Right;

	void AdjustSpeed(ModelType model, Direction dir, MovementType movement);
	
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




};

#endif /* SKELETON_H */
