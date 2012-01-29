#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "Utility.h"

class FontManager
{
public:
	
	// Very small text (8px), use for drawing information on a cell.
	static ID3DX10Font*		cellFont;
	static ID3DX10Font*		menuFont;
	static ID3DX10Font*		mainMenuFont;

	static void init();
};
