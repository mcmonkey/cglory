#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>
#include <string>
#include "dxManager.h"
#include "GameSprite.h"


using namespace std;

void draw(GameSprite sprite);
void addToDraw(GameSprite sprite);
void addToDrawAbs(GameSprite sprite);
void drawAll();

void toggleDrawing();

void operator +=(string &, int i);
void operator +=(string &, string &);

class Utility
{
public:
	static HWND* hWnd;

	static vector<GameSprite>	drawList;
	static vector<GameSprite>	drawAbsList;
	static D3DXVECTOR3*			camera;
	static D3DXVECTOR2*			mapSize;
	static ID3D10Device*		pDevice;
	static ID3DX10Sprite*		mainSprite;
	static int					gameState;

public:
	Utility(void);
	~Utility(void);
	static void init(ID3D10Device* device, HWND* window);
	static void resize();
	static void moveCamera(float x, float y);
	static void moveCameraAbs(float x, float y);
	static void clampCam();
	static void moveCursor(float x, float y);

	static void debugUpdate();

	// Helper functions for creating sprites and fonts.
	static HRESULT paletteSwappedSpriteFactory(GameSprite* pSprite, LPCWSTR pathToFile);
	static HRESULT spriteFactory(GameSprite* pSprite, LPCWSTR pathToFile);
	static void fontFactory(int fontHeight, wchar_t* fontFamily, ID3DX10Font** font);

	static void parseCommand(string s);			// parses a command string. Only from dev console at this point

	// String manipulation functions.
	static wstring widen(string s);				// Change strings between char strings and wchar_t wstrings
	static string narrow(wstring s);			// Change strings between wchar_t wstrings and char strings
	static string toLowerCase(string ws);		// Convert a string to lowercase.
	static vector<string> split(string, char);	// Split a string on the given character.

	static void setState(int gS);
	static int getState();

};

