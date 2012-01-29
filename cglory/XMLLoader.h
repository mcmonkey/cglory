#pragma once;
#include "stdafx.h"
#include "SpriteInfo.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <vector>

using std::vector;

class XMLLoader
{
public:
	static void loadSpriteInfo(const char*, std::vector<SpriteInfo*>*);
};