#ifndef _SPRITE_H
#define _SPRITE_H

#include "Graphics.h"
#include "Game/Entity/Skeleton.h"

// Used for loading images to screen
class Sprite
{
private:
	ID2D1Bitmap* m_Bmp;
	HRESULT m_Hr = S_OK;

	D2D1_SIZE_F m_Size = D2D_SIZE_F();

public:
	void Draw(float posX, float posY, float scale = SKEL_DEFUALT_SKELETON_SCALE);

	const D2D1_SIZE_F& GetSize() const ;

	// No default constructor
	Sprite(ImageInfo image);
	~Sprite();
};

#endif /* _SPRITE_H */
