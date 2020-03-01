#ifndef KNIGHT_H
#define KNIGHT_H

#include "Enemy.h"

// TODO: Finish C:
class Knight : public Enemy
{
private:

	void UpdateHitBox() override;
public:

	ImageInfo GetImage() const override;

};

#endif /* KNIGHT_H */
