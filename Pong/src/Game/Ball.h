#ifndef BALL_H
#define BALL_H

class Ball
{
private:
	float m_X = 0, m_Y = 0; // Center of the screen

	float m_XSpeed = 0.0f; // Not moving
	float m_YSpeed = 0.0f;
public:
	const float c_Radius = 0.04f;
	const float c_InitSpeed = 0.002f;
	const float c_MaxSpeed = 0.005f;

	inline const float& GetX() const { return this->m_X; }
	inline const float& GetY() const { return this->m_Y; }
	inline const float& GetXSpeed() const { return this->m_XSpeed; }
	inline const float& GetYSpeed() const { return this->m_YSpeed; }

	void Start();
	void SwapXDirection();
	void SwapYDirection();
	void ChangeSpeed(const float& ballPos, const float& PaddlePos);

	void Move();

	void Reset();

};

#endif /* BALL_H */
