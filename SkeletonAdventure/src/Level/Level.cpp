#include "pch.h"
#include "Window/Render.h"
#include "Level.h"


void Level::UpdateDrawingObjects()
{

}

// Loads the level
void Level::LoadInter()
{
	// I want a text file with everything we need for each level.
	// I have no idea how to do that

	// Im thinking a deque with ojbects we need to draw
}
// Loads the level
void Level::Load()
{
	Get().LoadInter();
}

// Draws the level based whats on frame
void Level::DrawInter(const int& skelPos)
{
	for (const auto& obj : m_DrawingObjects)
	{
		Render::DrawLevelObjects(obj);
	}
}
// Draws the level based on the what the skeleton can see
void Level::Draw(const int& SkeletonPos)
{
	Get().DrawInter(SkeletonPos);
}

// Gets the current level object
Level& Level::Get()
{
	static Level lvl; // Create on first use
	return lvl;
}


// Made private for singlton
Level::Level()
{
}

