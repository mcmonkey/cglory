#include "StdAfx.h"
#include "Utility.h"
#include "Sound.h"
#include "GameCursor.h"
#include "PlayManager.h"
#include "InputManager.h"
#include "JasonTest.h"
#include <map>
#include <algorithm>
#include "DevCursor.h"

ID3D10Device*	Utility::pDevice = NULL;
HWND*			Utility::hWnd = NULL;

ID3DX10Sprite*	Utility::mainSprite;

vector<GameSprite> Utility::drawList = vector<GameSprite>();
vector<GameSprite> Utility::drawAbsList = vector<GameSprite>();
D3DXVECTOR3* Utility::camera = new D3DXVECTOR3(0,0,0);
D3DXVECTOR2* Utility::mapSize = new D3DXVECTOR2(25*32, 25*32);
int Utility::gameState;

bool drawing = true;

void draw(GameSprite toDraw)
{
	toDraw.preDraw();
	Utility::mainSprite->Begin(D3DX10_SPRITE_SAVE_STATE);
	Utility::mainSprite->DrawSpritesBuffered(toDraw.sprite, 1);
	Utility::mainSprite->End();
}

void addToDraw(GameSprite sprite)
{
	Utility::drawList.push_back(sprite);
}

void addToDrawAbs(GameSprite sprite)
{
	Utility::drawAbsList.push_back(sprite);
}

void toggleDraw()
{
	drawing = !drawing;
}

void drawAll()
{
	//Utility::gCursor.draw();
	//MenuManager::draw();
	if(drawing)
	
		{//drawConsole should be last so it will draw over anything
			
			
		Utility::mainSprite->Begin(D3DX10_SPRITE_SAVE_STATE);
		for(unsigned int i=0; i< Utility::drawList.size(); i++)
		{
			GameSprite toDraw = Utility::drawList.at(i);
			//the predraw sets up the matWorld based on the position of the sprite.
			//but we want to keep the sprite's position kept without the camera's influence
			
			//change the positions
			toDraw.position.x -= Utility::camera->x;
			toDraw.position.y -= Utility::camera->y;
			//call the predraw
			toDraw.preDraw();
			//draw the sprite
			Utility::mainSprite->DrawSpritesBuffered(toDraw.sprite, 1);
			//and we're done!
		}
		for(unsigned int i=0; i<Utility::drawAbsList.size(); i++)
		{
			GameSprite toDraw = Utility::drawAbsList.at(i);
			toDraw.preDraw();
			Utility::mainSprite->DrawSpritesBuffered(toDraw.sprite, 1);
		}
	
		Utility::mainSprite->End();
		Utility::mainSprite->Flush();
	
	}

	Utility::drawList.clear();
	Utility::drawAbsList.clear();

	
	
	PlayManager::drawAll();
	DeveloperConsole::drawConsole();
	InputManager::drawAll();
	//MenuManager::draw();
	
	
}

void operator +=(string & s, int i)
{
	char temp[64];
	itoa(i, temp, 10);
	s.append(temp);
}

void operator +=(string & s, string & s2)
{
	s.append(s2);
}

void Utility::init(ID3D10Device* device, HWND* window)
{
	pDevice = device;
	hWnd = window;
	D3DX10CreateSprite(pDevice, 5, &mainSprite);
	DeveloperConsole::init();
	Utility::resize();

	ID3D10RasterizerState* rasterizerState;

	D3D10_RASTERIZER_DESC rasterizerDesc = 	{
			D3D10_FILL_SOLID,
			D3D10_CULL_NONE, 
			FALSE, 
			0, 
			0.0f,
			0.0f,	
			TRUE,
			FALSE,
			FALSE, 
			FALSE	
			};
	pDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	pDevice->RSSetState(rasterizerState);

	RECT r;
	RECT r2;
	GetWindowRect(*hWnd, &r);
	GetClientRect(*hWnd, &r2);
	r2.top = r.top;
	r2.left = r.left;
	Stats::setScreenSize(r2);
	POINT p = Stats::getScreenSize();
	D3DXMATRIX newPersp;

	D3DXMatrixOrthoOffCenterLH(&newPersp, 0, (float)p.x, (float)p.y, 0, -30, 1);
	mainSprite->SetProjectionTransform(&newPersp);

	SpriteHelper::init();
	FontManager::init();

	InformationStorage::loadAll("info.xml");
	Utility::setState(GameState::Default);
	PlayManager::init();
}

void Utility::moveCamera(float x, float y)
{
	camera->x += x;
	camera->y += y;

	Utility::clampCam();
}

void Utility::moveCameraAbs(float x, float y)
{
	camera->x = x;
	camera->y = y;
	Utility::clampCam();
}

void Utility::clampCam()
{
	if(camera->x < 0)
	{
		camera->x = 0;
	}
	if(camera->y < 0)
	{
		camera->y = 0;
	}
	if(camera->x > Utility::mapSize->x - Stats::getResolution().x)
	{
		camera->x = Utility::mapSize->x- Stats::getResolution().x;
	}
	if(camera->y > Utility::mapSize->y- Stats::getResolution().y)
	{
		camera->y = Utility::mapSize->y- Stats::getResolution().y;
	}
}

void Utility::moveCursor(float x, float y)
{

}

void Utility::debugUpdate()
{
	
}

HRESULT Utility::spriteFactory(GameSprite* result, LPCWSTR pathToFile)
{
	// May have already loaded, easy out
	// This really long line looks through the storage in SpriteHelper for the file name.
	auto fileSearchResult = SpriteHelper::spriteStorage.find(pathToFile);
	
	if(fileSearchResult != SpriteHelper::spriteStorage.end())
	{
		*result = fileSearchResult->second;
		return 777;
	}

	HRESULT imageR;
	D3DX10_IMAGE_INFO infoFromFile;
	D3DX10_IMAGE_LOAD_INFO loadImageInfo;

	imageR = D3DX10GetImageInfoFromFile(pathToFile, NULL, &infoFromFile, NULL);
	if(FAILED(imageR))
	{
		DeveloperConsole::write("Failed to load image ");
		DeveloperConsole::writeLine(narrow(pathToFile));
		return -1;
	}

	loadImageInfo.Width  = infoFromFile.Width;
	loadImageInfo.Height = infoFromFile.Height;
	loadImageInfo.Depth  = infoFromFile.Depth;
	loadImageInfo.FirstMipLevel = 1;
	loadImageInfo.MipLevels = infoFromFile.MipLevels;
	loadImageInfo.Usage = D3D10_USAGE_DEFAULT;
	loadImageInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	loadImageInfo.CpuAccessFlags = 0;
	loadImageInfo.MiscFlags = 0;
	loadImageInfo.Format = infoFromFile.Format;
	loadImageInfo.Filter = D3DX10_FILTER_NONE;
	loadImageInfo.MipFilter = D3DX10_FILTER_NONE;
	loadImageInfo.pSrcInfo = &infoFromFile;
	*result = GameSprite(infoFromFile.Width, infoFromFile.Height);

	//setup the shader resource
	ID3D10ShaderResourceView* pSRVx;
	imageR = D3DX10CreateShaderResourceViewFromFile(pDevice, pathToFile, &loadImageInfo, NULL, &pSRVx, NULL);
	if(FAILED(imageR))
	{
		return imageR;
	}

	//using the resource, setup the sprite pointer that was passed in
	result->sprite->pTexture = pSRVx;
	result->sprite->TexCoord = D3DXVECTOR2(0.0, 0.0);
	result->sprite->TexSize = D3DXVECTOR2(1.0f, 1.0f);
	//result->sprite.TexSize = D3DXVECTOR2(Stats::getScreenSize().x, Stats::getScreenSize().y);
	result->sprite->ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	result->sprite->TextureIndex = 0;
	result->drawSize = result->originalSize;

	// Save the result for later use.
	SpriteHelper::spriteStorage[wstring(pathToFile)] = *result;

	return 777;
}

void Utility::fontFactory(int fontHeight, wchar_t* fontFamily, ID3DX10Font** font)
{
	D3DX10_FONT_DESC fontDesc;
		fontDesc.Height			= fontHeight;
		fontDesc.Weight			= 1;
		fontDesc.MipLevels		= 1;
		fontDesc.Italic			= false;
		fontDesc.CharSet		= DEFAULT_CHARSET;
		fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		fontDesc.Quality		= DEFAULT_QUALITY;
		fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(fontDesc.FaceName, fontFamily);
	
	D3DX10CreateFontIndirect(pDevice, &fontDesc, font);
}

// Parses a command string, generally from DevConsole.
// Only from dev console at this point.
// Splits it on spaces, currently ignores quotation marks, may be usefull later on to add.
void Utility::parseCommand(string s)
{
	s = toLowerCase(s);
	vector<string> cmds = split(s, ' ');
	
	if(cmds.size() > 0)
	{
		s = cmds[0];
		if(s == "jason")
			JasonTest::test();
		else if(s == "toggledraw")
			toggleDraw();
		else if(s == "help" || s=="halp")
		{
			DeveloperConsole::writeLine();
			DeveloperConsole::writeLine("load [map/headers] +fileName   - loads an xml file. Loads default if no file specified");
			DeveloperConsole::writeLine("controls                       - display a list of controls");
			DeveloperConsole::writeLine("toggledraw                     - Makes a thing of beauty appear");
			DeveloperConsole::writeLine("mkunit +unitId +playerId +x +y - Makes a unit");
			DeveloperConsole::writeLine("rmunit +x +y                   - Removes a unit");
		}
		else if(s == "load")
		{
			if(cmds.size() > 1)
			{

				if(cmds[1] == "map")
				{
					Map* m = 0x0;
					if(cmds.size() > 2)
						m = Map::loadFromXML(cmds[2].c_str());
					else
					{
						m = Map::loadFromXML("map.xml");
						DeveloperConsole::writeLine("Loaded default map.xml map.");
					}

					if(m)
						PlayManager::newMap(m);
				}
				else if(cmds[1] == "headers")
				{
					if(cmds.size() > 2)
					{
						InformationStorage::loadAll(cmds[2]);
					}
					else
					{
						InformationStorage::loadAll("info.xml");
						DeveloperConsole::writeLine("Loaded default info.xml headers.");
					}
				}
			}
			else
				DeveloperConsole::writeLine("Please specify a file type [map/headers]");
		}
		else if(s == "mkunit")
		{
			if(cmds.size() < 5)
				DeveloperConsole::writeLine("Needs 5 arguments - mkunit +unitId +playerId +x +y");
			else
			{
				
				PlayManager::getCurrentMap()->createUnit(atoi(cmds[1].c_str()), atoi(cmds[2].c_str()), atoi(cmds[3].c_str()), atoi(cmds[4].c_str()));
			}
		}
		else if(s == "rmunit")
		{
			if(cmds.size() < 3)
				DeveloperConsole::writeLine("Needs 2 arguments - rmunit +x +y");
			else
			{
				Unit* u = (Unit*)PlayManager::getCurrentMap()->getCell(atoi(cmds[1].c_str()), atoi(cmds[2].c_str()))->objectAtLayer(CellLayers::Unit);
				if(u)
				{
					PlayManager::getCurrentMap()->destroyGameObject(u);
					DeveloperConsole::writeLine("Destroyed unit");
				}

			}
		}
		else if(s == "next")
		{
			PlayManager::advanceTurn();
		}
		else if(s == "neutralplayer")
		{
			PlayManager::gotoNeutralPlayer();
		}
		else if(s == "togglefog")
		{
			PlayManager::toggleFogDraw();
		}
		else if(s == "musictest")
		{
			SoundManager::loopMusic("Juese.mp3");
		}
		else if(s == "stopmusic")
		{
			SoundManager::stopMusic();
		}
		else if(s == "savemap")
		{
			if(cmds.size() > 1)
				InformationStorage::saveMap(cmds[1], PlayManager::getCurrentMap());
			else
				DeveloperConsole::writeLine("Please include a file name.");
		}
		else if(s == "newmap")
		{
			if(cmds.size() < 4)
				DeveloperConsole::writeLine("newmap size-x size-y playercount");
			else
				PlayManager::newMap(new Map(atoi(cmds[1].c_str()), atoi(cmds[2].c_str()), atoi(cmds[3].c_str())));
		}
		else if(s== "devcursor")
		{
			new DevCursor();
		}
		else if(s == "shift")
		{
			Map & m = *PlayManager::getCurrentMap();
			for(int i = m.width - 1; i >= 0; --i)
				for(int j = 0; j < m.height; ++j)
				{
					Cell* c = m.getCell(i, j);
					if(c)
					{
						Cell* n = m.neighbor(c, MovementDirection::RIGHT);
						if(n)
						{
							for(int l = 0; l < CellLayers::Count; ++l)
							{
								GameObject* g = c->objectAtLayer(l);
								if(g)
									n->replaceGameObject(*g);
								c->removeGameObject(l);
							}
						}
					}
				}
		}
		else if(s == "listdeck")
		{
			DeveloperConsole::writeLine("Current Player's Deck");
			for(int i=0; i<PlayManager::getActivePlayer()->deck.size(); i++)
			{
				DeveloperConsole::writeLine(PlayManager::getActivePlayer()->deck.at(i)->name);
			}
		}

		else if(s == "listhand")
		{
			DeveloperConsole::writeLine("Current Player's Hand");
			for(int i=0; i<PlayManager::getActivePlayer()->hand.size(); i++)
			{
				DeveloperConsole::writeLine(PlayManager::getActivePlayer()->hand.at(i)->name);
			}
		}

		else if(s == "playcard")
		{
			if(cmds.size() >= 3)
			{
				int cardIndex = atoi(cmds[1].c_str());
				int x = atoi(cmds[2].c_str());
				int y = atoi(cmds[3].c_str());
				if(cardIndex < PlayManager::getActivePlayer()->hand.size() && x < PlayManager::getCurrentMap()->width && y < PlayManager::getCurrentMap()->height)
				{
					//Execute the card, then discard it
					PlayManager::getActivePlayer()->playCard(cardIndex, PlayManager::getCurrentMap()->getCell(x, y));
				}
			}
		}

		else if(s == "discardcard")
		{
			if(cmds.size() > 1)
			{
				//Discard specific card
				PlayManager::getActivePlayer()->discardCard(atoi(cmds[1].c_str()));
			}
			else
			{
				//Discard random card
				PlayManager::getActivePlayer()->discardCard();
			}
		}

		else if(s == "drawcard")
		{
			PlayManager::getActivePlayer()->drawCard();
		}

		else if(s == "purchasecard")
		{
			if(cmds.size() > 1)
			{
				PlayManager::getActivePlayer()->purchaseCard(atoi(cmds[1].c_str()));
			}
		}
	}
}

void Utility::resize()
{
	RECT r;
	RECT r2;
	GetWindowRect(*hWnd, &r);
	GetClientRect(*hWnd, &r2);
	r2.top = r.top;
	r2.left = r.left;
	Stats::setScreenSize(r2);
	POINT p = Stats::getScreenSize();
}

// Converts a char string into a wchar_t wstring.
wstring Utility::widen(string s)
{
	wstring newString = wstring(s.length(), L' '); 
	std::copy(s.begin(), s.end(), newString.begin());
	return newString;
}

// Converts a wchar_t wstring into a char string.
string Utility::narrow(wstring ws)
{
	string newString = string(ws.length(), ' ');
	copy(ws.begin(), ws.end(), newString.begin());
	return newString;
}

// Returns a string with the lower case interpertation of the input string.
string Utility::toLowerCase(string s)
{
	string newString = string(s);
	for(int i = 0; i < s.length(); i++)
	{
		newString[i] = tolower(newString[i]);
	}
	return newString;
}

// Splits a string on the given character
vector<string> Utility::split(string s, char c)
{
	vector<string> result;
	int start = 0;
	bool lastWasC = false;
	for(int i = 0; i < s.length(); i++)
	{
		
		if(s[i] == c)
		{
			if(!lastWasC)
			{
				result.push_back(string(s, start, i - start));
				lastWasC = true;
			}
			if(lastWasC)
				start = i + 1;
		}
		else
			lastWasC = false;
	}
	if(!lastWasC)
		result.push_back(string(s, start, s.length() - start));

	return result;
}

void Utility::setState(int gS)
{
	gameState = gS;
}

int Utility::getState()
{
	return gameState;
}
Utility::Utility(void)
{
}


Utility::~Utility(void)
{
}
