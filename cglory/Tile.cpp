#include "stdafx.h"
#include "Tile.h"
#include <string.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


Tile::Tile(const char* inName, int inShort, int inDefense, float inNormX, float inNormY)
{
	strcpy(name, inName);
	shorthand = inShort;
	defense = inDefense;
	normPosX = (int)inNormX;
	normPosY = (int)inNormY;
}

Tile::Tile()
{
	defense = 1;
	normPosX = 1;
	normPosY = 1;
}

Tile::~Tile()
{
}

char* Tile::getName()
{
	return name;
}


int Tile::getDefense()
{
	return defense;
}

int Tile::getNormPosX()
{
	return normPosX;
}

int Tile::getNormPosY()
{
	return normPosY;
} 

void Tile::setName(const char* inName)
{
	strcpy(name, inName);
}


void Tile::setDefense(int inDefense)
{
	defense = inDefense;
}

void Tile::setNormPosX(int inX)
{
	normPosX = inX;
}

void Tile::setNormPosY(int inY)
{
	normPosY = inY;
}

void Tile::printTile()
{
	std::cout << "Name: " << name << "\n";
	std::cout << "shorthand: " << shorthand << "\n";
	std::cout << "Defense: " << defense << "\n";
	std::cout << "X: " << normPosX << "\n";
	std::cout << "Y: " << normPosY << "\n";
}

void Tile::copyTile(Tile other)
{
	strcpy(name, other.name);
	defense = other.defense;
	normPosX = other.normPosX;
	normPosY = other.normPosY;
}