#include "stdafx.h"
#include "SpriteInfo.h"

SpriteInfo::SpriteInfo(const char* inName, const char* inPath)
{
	strcpy(name, inName);
	strcpy(path, inPath);
}

const char* SpriteInfo::getName()
{
	return name;
}

const char* SpriteInfo::getPath()
{
	return path;
}

void SpriteInfo::setName(const char* inName)
{
	strcpy(name, inName);
}

void SpriteInfo::setPath(const char* inPath)
{
	strcpy(path, inPath);
}