#pragma once
#include "stdafx.h"
#include <string.h>

class SpriteInfo
{
public :
	char name[100];
	char path[100];
public:
	SpriteInfo(const char*, const char*);
	const char* getName();
	const char* getPath();
	void setName(const char*);
	void setPath(const char*);
};