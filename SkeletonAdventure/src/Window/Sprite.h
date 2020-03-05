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

	void ConstructSprite(ImageInfo& image);

public:
	void Draw(float posX, float posY, float scale = SKEL_DEFUALT_SKELETON_SCALE);

	const D2D1_SIZE_F& GetSize() const ;

	// No default constructor
	Sprite(ImageInfo image);
	Sprite(ImageInfo image, float width, float height, int count);
	~Sprite();
};

#endif /* _SPRITE_H */
