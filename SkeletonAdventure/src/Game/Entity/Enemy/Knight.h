#ifndef KNIGHT_H
#define KNIGHT_H

#include "Enemy.h"

// TODO: Finish C:
class Knight : public Enemy
{
private:

	void UpdateHitBox() override;
public:

	void Think() override;

	ImageInfo GetImage() const override;
	Sprite* GetSprite() const final override;
};

#endif /* KNIGHT_H */
