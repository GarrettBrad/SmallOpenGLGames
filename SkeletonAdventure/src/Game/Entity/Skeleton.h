#ifndef SKELETON_H
#define SKELETON_H

#include "Entity.h"



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


class Skeleton : public Entity
{
private:
	std::array<const wchar_t*, 6> m_Attack1Models = {
		L"resources/Skeleton/attack1_1.png",
		L"resources/Skeleton/attack1_2.png",
		L"resources/Skeleton/attack1_3.png",
		L"resources/Skeleton/attack1_4.png",
		L"resources/Skeleton/attack1_5.png",
		L"resources/Skeleton/attack1_6.png",
	};

	std::array<const wchar_t*, 6> m_Attack2Models = {
		L"resources/Skeleton/attack2_1.png",
		L"resources/Skeleton/attack2_2.png",
		L"resources/Skeleton/attack2_3.png",
		L"resources/Skeleton/attack2_4.png",
		L"resources/Skeleton/attack2_5.png",
		L"resources/Skeleton/attack2_6.png",
	};

	std::array<const wchar_t*, 1> m_Corpse_1Models = {
		L"resources/Skeleton/corpse_1.png"
	};

	std::array<const wchar_t*, 1> m_Corpse_2Models = {
		L"resources/Skeleton/corpse_2.png"
	};

	std::array<const wchar_t*, 6> m_DeadFar = {
		L"resources/Skeleton/dead_far_1.png",
		L"resources/Skeleton/dead_far_2.png",
		L"resources/Skeleton/dead_far_3.png",
		L"resources/Skeleton/dead_far_4.png",
		L"resources/Skeleton/dead_far_5.png",
		L"resources/Skeleton/dead_far_6.png"
	};

	std::array<const wchar_t*, 6> m_DeadNearModels = {
		L"resources/Skeleton/dead_near_1.png",
		L"resources/Skeleton/dead_near_2.png",
		L"resources/Skeleton/dead_near_3.png",
		L"resources/Skeleton/dead_near_4.png",
		L"resources/Skeleton/dead_near_5.png",
		L"resources/Skeleton/dead_near_6.png"
	};

	std::array<const wchar_t*, 3> m_HitModel = {
		L"resources/Skeleton/hit_1.png",
		L"resources/Skeleton/hit_2.png",
		L"resources/Skeleton/hit_3.png"
	};

	std::array<const wchar_t*, 5> m_JumpModel = {
		L"resources/Skeleton/jump_1.png",
		L"resources/Skeleton/jump_2.png",
		L"resources/Skeleton/jump_3.png",
		L"resources/Skeleton/jump_4.png",
		L"resources/Skeleton/jump_5.png"

	};

	std::array<const wchar_t*, 3> m_ReadyModels = {
		L"resources/Skeleton/ready_1.png",
		L"resources/Skeleton/ready_2.png",
		L"resources/Skeleton/ready_3.png"
	};

	std::array<const wchar_t*, 3> m_RebornModels = {
		L"resources/Skeleton/reborn_1.png",
		L"resources/Skeleton/reborn_2.png",
		L"resources/Skeleton/reborn_3.png"
	};

	std::array<const wchar_t*, 6> m_RunModels = {
		L"resources/Skeleton/run_1.png",
		L"resources/Skeleton/run_2.png",
		L"resources/Skeleton/run_3.png",
		L"resources/Skeleton/run_4.png",
		L"resources/Skeleton/run_5.png",
		L"resources/Skeleton/run_6.png"
	};

	std::array<const wchar_t*, 6> m_WalkModels = {
		L"resources/Skeleton/walk_1.png",
		L"resources/Skeleton/walk_2.png",
		L"resources/Skeleton/walk_3.png",
		L"resources/Skeleton/walk_4.png",
		L"resources/Skeleton/walk_5.png",
		L"resources/Skeleton/walk_6.png"
	};


private:

	// Used for drawing
	mutable int m_SkeletonShow = 1;
	mutable int m_MaxShow = 3; // the amount of an imagle there is
	mutable clock_t time;

	bool m_CanJump = true;
	const D2D1_SIZE_F m_Size = { 18,29 };

	ModelType m_ModelType = ModelType::Ready;

	void AdjustSpeed(ModelType model, Direction dir, MovementType movement);
	void DecaySpeed() override;
	void UpdateHitBox() override;
	
public:

	void Move() override;
	void Jump();
	void InSpeedSprint(Direction dir);
	void InSpeedWalk(Direction dir);
	void Attack();

	bool IsSkeleton() const override final;

	void SetCanJump();
	void SetNoJump();

	const bool& GetCanJump() const;

	ImageInfo GetImage() const override;

	const D2D1_SIZE_F GetSize();





};

#endif /* SKELETON_H */
