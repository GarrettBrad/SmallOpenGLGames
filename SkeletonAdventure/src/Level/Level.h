#ifndef LEVEL_H
#define LEVEL_H

struct DrawObject
{

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
	void DrawInter(const int& SkeletonPos);

	Level();

public:
	// Every thirty frames we update m_DrawingObjects
	const int c_FramesNeedForNextLoad = 30;

	static void Load();

	static void Draw(const int& SkeletonPos);

	static Level& Get();

};


#endif /* LEVEL_H */