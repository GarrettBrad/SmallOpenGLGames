#include "pch.h"
#include <time.h>
#include "Knight.h"


extern unsigned int g_Increase;

// Update the hitbox pos
void Knight::UpdateHitBox()
{
	m_HitBox.TopLeft.X = m_X + 60;
	m_HitBox.TopLeft.Y = m_Y + 35;
	m_HitBox.BottomRight.X = m_X + 60 + 50;
	m_HitBox.BottomRight.Y = m_Y + 35 + 75;

}

void Knight::Think()
{
	if (abs(m_XSpeed) > 1) {
		m_ModelType = ModelType::Run;
	}
	else {
		m_ModelType = ModelType::Ready;
	}

	this->Enemy::Think();
}

// Gets the image that should be used
ImageInfo Knight::GetImage() const
{
	if (m_Time < clock())
	{
		m_ModelShow++;

		m_Time = clock() + SKELETON_SWTICH_TIME;
	}

	bool flip = false;

	if (m_DirectionFacing == Direction::Left)
		flip = true;

	switch (m_ModelType)
	{
	case ModelType::Attack1: // [[fallthrough]]
	case ModelType::Attack2:
	{
		m_MaxShow = 22; // Amount of frames/pics in an image
		m_DrawOffset = 0;
		m_FrameDistance = 0;

		return { L"resources/Knight/KnightAttack.png", flip };
		break;
	}
	case ModelType::Run:
	{

		m_DrawOffset = 17;
		m_FrameDistance = 32;

		m_MaxShow = 8;

		return { L"resources/Knight/KnightRun.png", flip };

		break;
	}
	case ModelType::DeadNear: // [[fallthrough]]
	case ModelType::DeadFar:
	{
		m_MaxShow = 15;		
		m_DrawOffset = 0;
		m_FrameDistance = 0;

		return { L"resources/Knight/KnightDeath.png", flip };

		break;
	}
	case ModelType::Hit:
	{
		m_MaxShow = 7;
		m_DrawOffset = 0;
		m_FrameDistance = 0;

		return { L"resources/Knight/KnightShield.png", flip };

		break;
	}
	default: // Ready
	{
		m_MaxShow = 12;
		m_DrawOffset = 0;
		m_FrameDistance = 0;

		return { L"resources/Knight/KnightIdle.png", flip };
		
		break;
	}
	}


	// Return " " if problem
	return ImageInfo(L" ", false);
}

// Gets the custom sprite for drawing
Sprite* Knight::GetSprite() const
{

	// this stops recreating the sprite if the image is the same
	if (m_LastInfo.file != GetImage().file)
	{
		m_LastInfo = GetImage();

		// Deletes SkeletonSprite if there is a new one in que
		if (m_pSprite)
		{
			delete m_pSprite;
			m_pSprite = nullptr;
		}
	}

	// Creates a new sprite to be drawing
	if (!m_pSprite)
	{
		m_pSprite = new Sprite(GetImage(), 64, 64, m_MaxShow);
	}

	m_pSprite->SetOffSet(m_DrawOffset);
	m_pSprite->SetFrameDistance(m_FrameDistance);

	return m_pSprite;
}