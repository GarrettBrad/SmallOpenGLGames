#ifndef ALLOCATE_H
#define ALLOCATE_H
#include "pch.h"

// Allocates memory and avoids which you can delete without freeing the memory
template<class _Type>
class Allocate
{
private:

	_Type* m_pData = nullptr;

public:

	// Zeros out the memory
	void ZeroMem()
	{
		m_pData* = { 0 };
	}

	_Type* Get()
	{
		return m_pData;
	}

	Allocate()
	{
		m_pData = malloc(sizeof(_Type));
	}

	_Type& operator*()
	{
		return m_pData*;
	}
	
	~Allocate()
	{
		free(m_pData);
	}

};



#endif /* ALLOCATE_H */
