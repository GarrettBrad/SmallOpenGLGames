#ifndef GAME_H
#define GAME_H


class Game
{
private:

	bool m_ShouldClose = false;
public:
	int Init();
	bool ShouldClose();
	void Run();

};

#endif /* GAME_H */
