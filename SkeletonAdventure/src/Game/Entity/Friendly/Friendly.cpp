#include "pch.h"
#include "Friendly.h"


// Returns true
bool Friendly::IsFriendly() const
{
	return true;
}

// Returns false
bool Friendly::IsEnemy() const
{
	return false;
}

void Friendly::Think()
{
	m_Ai.Think();
}

Friendly::~Friendly()
{
}