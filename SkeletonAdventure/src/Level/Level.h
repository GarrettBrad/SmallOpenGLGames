#ifndef LEVEL_H
#define LEVEL_H

#include "Game/Skeleton.h"

enum class ObjectType
{
	Floor,
	OneWayBlock,
	Light
};

struct DrawObject
{
	ObjectType Type;
	Vector2D TopLeft;
	Vector2D BottomRight;
	const wchar_t* Texture;

	DrawObject(ObjectType type, Vector2D lu, Vector2D rd, const wchar_t* text)
		: Type(type), TopLeft(lu), BottomRight(rd), Texture(text)
	{}
};

// Singleton
// Makes the level
class Level
{
private:
	
	// holds all objects in the level
	std::deque<DrawObject> m_LevelOjbects;
	// Holds all ojbects we need to draw currently
	std::deque<DrawObject> m_DrawingObjects;

	int c_FramesTillNextLoad = 0;

private:

	void UpdateDrawingObjects();

	void LoadInter();

	const std::deque<DrawObject>& GetObjecstInter();

	void DrawInter();

	Level();

public:
	// Every thirty frames we update m_DrawingObjects
	const int c_FramesNeedForNextLoad = 30;

	static void Load();

	static const std::deque<DrawObject>& GetObjects();

	static void Draw();

	static Level& Get();

};


#endif /* LEVEL_H */