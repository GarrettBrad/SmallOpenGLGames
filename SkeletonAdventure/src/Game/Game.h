#ifndef GAME_H
#define GAME_H

#include "Skeleton.h"

class Game
{
private:

	bool m_ShouldClose = false;

	Skeleton skeli = Skeleton();
public:
	int Init();
	bool ShouldClose();
	void Run();

};

#endif /* GAME_H */
