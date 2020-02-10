#ifndef PADDLE_H
#define PADDLE_H

enum class PlayerNumber
{
	ONE,
	TWO
};

enum class Direction
{
	UP,
	DOWN,
	AI_UP,
	AI_DOWN
};

class Paddle
{
private:
	float m_X = 0.0f, m_Y = 0.0f;
	PlayerNumber m_PlayerNumber;
public:
	const float c_Height = 0.4f; // Const so it can be public
	const float c_Width = 0.01f; 
	const float c_MoveSpeed = 0.02f;
	const float c_AIMoveSpeed = 0.01f; // Slower

	const PlayerNumber& GetPlayerNumber() const;

	inline const float& GetX() const { return this->m_X; }
	inline const float& GetY() const { return this->m_Y; }

	void Move(Direction dir);

	Paddle(PlayerNumber PNum); // Player 1 or two
	~Paddle();

};

#endif /* PADDLE_H */
