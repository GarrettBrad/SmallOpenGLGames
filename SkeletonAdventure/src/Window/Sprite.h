#ifndef _SPRITE_H
#define _SPRITE_H

#include "Graphics.h"
#include "Game/Entity/BaseEntityStructure.h"

// Used for loading images to screen
class Sprite
{
private:
	ID2D1Bitmap* m_Bmp;
	HRESULT m_Hr = S_OK;

	D2D1_SIZE_F m_Size = D2D_SIZE_F();
	int m_Count = 1;

	int m_Frame = 1;

	int m_Offset = 0; // How offset the image is
	int m_DistanceBetweenFames = 0; // How far the pictures are apart from each other	
	bool m_IsValid = false;

	void ConstructSprite(ImageInfo& image);

public:
	void Draw(float posX, float posY, float scale = SKEL_DEFUALT_SKELETON_SCALE, float alpha = 1.0f);

	const D2D1_SIZE_F& GetSize() const ;

	inline void SetOffSet(int off) { m_Offset = off; }
	inline void SetFrameDistance(int dist) { m_DistanceBetweenFames = dist; }

	// No default constructor
	Sprite(ImageInfo image);
	Sprite(ImageInfo image, int width, int height, int count);
	~Sprite();
};

#endif /* _SPRITE_H */
