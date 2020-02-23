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

	m_LevelOjbects.push_back(DrawObject(ObjectType::Floor, {0, 681}, { SKEL_WINDOW_WIDTH, 720}, L" "));
	m_LevelOjbects.push_back(DrawObject(ObjectType::Floor, {500, 550}, {600, 600}, L" "));
	m_LevelOjbects.push_back(DrawObject(ObjectType::Floor, {600, 500}, {750, 550}, L" "));
	m_LevelOjbects.push_back(DrawObject(ObjectType::Floor, {750, 550}, {800, 600}, L" "));
	m_LevelOjbects.push_back(DrawObject(ObjectType::Floor, {100, 600}, {200, 650}, L" "));
	m_DrawingObjects.push_back(m_LevelOjbects[0]);
	m_DrawingObjects.push_back(m_LevelOjbects[1]);
	m_DrawingObjects.push_back(m_LevelOjbects[2]);
	m_DrawingObjects.push_back(m_LevelOjbects[3]);
	m_DrawingObjects.push_back(m_LevelOjbects[4]);
}
// Loads the level
void Level::Load()
{
	Get().LoadInter();
}

// Gets the current objects being draw	
const std::deque<DrawObject>& Level::GetObjecstInter()
{
	return m_DrawingObjects;
}
// Gets the current draw objects
const std::deque<DrawObject>& Level::GetObjects()
{
	return Get().GetObjecstInter();
}


// Draws the level
void Level::DrawInter()
{
	for (const auto& obj : m_DrawingObjects)
	{
		Render::DrawLevelObjects(obj);
	}
}
// Draws the level based on the what the skeleton can see
void Level::Draw()
{
	Get().DrawInter();
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

