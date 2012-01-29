#pragma once
#include <D3DX10.h>
#include <string>
class GameSprite
{	

public:
	D3DXVECTOR2 originalSize;
	D3DXVECTOR2 frameSize;
	D3DXVECTOR3 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR2 drawSize;

	D3DXCOLOR color;

	bool hasAnimation;
	int animationPos;
	int numFrames;
	int timePerFrame;
	int animationRow;//for sprites with multiple animations, there will be one complete animation per row so just move the row and we have the other animations
					 //this will also most likely use an Enum to interpret what animation the sprite should be at (moving up, down, left, right and so on)
	
	D3DX10_SPRITE* sprite;
	//vector<D3DX10_SPRITE*>
	
	GameSprite();
	GameSprite(int width, int height);
	~GameSprite(void);

	POINT getSize();
	void preDraw();
};

