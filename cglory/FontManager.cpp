#include "stdafx.h"

ID3DX10Font*	FontManager::cellFont;
ID3DX10Font*	FontManager::menuFont;
ID3DX10Font*	FontManager::mainMenuFont;

void FontManager::init()
{
	Utility::fontFactory(10, L"Arial", &cellFont);
	Utility::fontFactory(20, L"Consolas", &menuFont);
	Utility::fontFactory(40, L"Arial", &mainMenuFont);
}