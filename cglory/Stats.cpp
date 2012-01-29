#include "StdAfx.h"
#include "Stats.h"
#include <time.h>

static Stats* s = 0;

static POINT mouse;
static POINT resolution;
static POINT actualMouse;
static float mouseN[2];
static RECT screen;
static int	tilesize = 32;
static POINT mapSize;
static int const flatGloryRate = 1000;
static float _dt = 0.0f;

void Stats::setMouse(POINT p)
{
	actualMouse = p;
	evalMouse();
}
void Stats::setScreenSize(RECT r)
{
	screen = r;
	evalMouse();
}
void Stats::setResolution(int x, int y)
{
	resolution.x = x;
	resolution.y = y;
}

POINT Stats::getResolution()
{
	return resolution;
}

POINT Stats::getScreenSize()
{
	POINT p;
	p.x = screen.right;
	p.y = screen.bottom;
	return p;
}

static clock_t fpsClock;
static float fpsAggregate[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
static int currentIndex = 0;
void Stats::startFPS()
{
	fpsClock = clock();
}
void Stats::endFPS()
{
	fpsClock = clock() - fpsClock;
	fpsAggregate[currentIndex] = (float)fpsClock;
	_dt = (float)fpsClock / 1000.0f;
	currentIndex = (currentIndex + 1) % 5;
}

float Stats::dt()
{
	return _dt;
}

float Stats::getFPS()
{
	float result = 0;
	for(int i = 0; i < 5; i++)
		result+=fpsAggregate[i];
	result = 5.0f / (result / 1000.0f);
	return result;
}

int Stats::timeSinceStart()
{
	return (int)clock();
}

POINT Stats::getMouse()
{
	return mouse;
}

void Stats::getMouseNormalized(float* point)
{
	point[0] = mouseN[0];
	point[1] = mouseN[1];
}

void Stats::evalMouse()
{	
	mouse.x = actualMouse.x - screen.left;
	mouse.y = actualMouse.y - screen.top;
		
	mouseN[0] = (float)(mouse.x) / (screen.right);
	mouseN[1] = (float)(mouse.y) / (screen.bottom);
}

void Stats::setMapsize(int x, int y)
{
	mapSize.x = x;
	mapSize.y = y;
}

POINT Stats::getMapsize()
{
	return mapSize;
}

int Stats::getTilesize()
{
	return tilesize;
}

int Stats::getGloryRate()
{
	return flatGloryRate;
}

void Stats::update()
{
	return;
}

Stats::Stats(void)
{
}

Stats::~Stats(void)
{
}
