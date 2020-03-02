#ifndef BASE_ENTITY_STRUCTURE_H
#define BASE_ENTITY_STRUCTURE_H

// 2 dimensional vector
struct Vector2D
{
	int X, Y;
};

// The box which can be hit
struct HitBox
{
	Vector2D TopLeft;
	Vector2D BottomRight;
};

enum class Direction
{
	Up = 0,
	Down,
	Left,
	Right
};

enum class MovementType
{
	Walk = 0,
	Run,
	Jump
};

struct ImageInfo
{
	const wchar_t* file;
	bool flipped = false;

	ImageInfo(const wchar_t* file, bool flipped)
		: file(file), flipped(flipped)
	{}
};


#endif /* BASE_ENTITY_STRUCTURE_H */