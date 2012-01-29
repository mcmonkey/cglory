#include "StdAfx.h"
#include "GameSprite.h"


GameSprite::GameSprite()
{	
}

GameSprite::GameSprite(int width, int height)
{
	originalSize.x = (float)width;
	originalSize.y = (float)height;
	frameSize.x = (float)Stats::getTilesize();
	frameSize.y = (float)Stats::getTilesize();
	position.x = 0;
	position.y = 0;
	position.z = 0;
	scale.x = 1;
	scale.y = 1;
	velocity = D3DXVECTOR2(0,0);
	texCoord = D3DXVECTOR2(0,0);
	color = D3DXCOLOR(1, 1, 1, 1);

	hasAnimation = false;
	animationPos = 0;
	numFrames = width / Stats::getTilesize();
	timePerFrame = 200;
	animationRow = 0;

	sprite = new D3DX10_SPRITE();
}



GameSprite::~GameSprite(void)
{
	//delete [] name;
	//delete sprite;
}

POINT GameSprite::getSize()
{
	POINT p;
	p.x = (long)(originalSize.x * scale.x);
	p.y = (long)(originalSize.y * scale.y);
	return p;
}

void GameSprite::preDraw()
{
	sprite->ColorModulate = color;

	if(hasAnimation)
	{
		//change the current sprite
		//the problem with this is how the preDraw is called. this is a copy from the list in the dxManager and thus texCoord never changes since it gets changed. maybe finally
		//change the list to not clear every time? I think its time for that. 
		animationPos = (Stats::timeSinceStart() / timePerFrame) % numFrames;
		texCoord.x = 1.0f/(originalSize.x/32.0f) * animationPos;
		texCoord.y = 1.0f/(originalSize.y/32.0f) * animationRow;
	}

	D3DXMATRIX transMat;
	D3DXMATRIX scaleMat;
	//apply translations to make sure it is in the spot it should be in accordance to its position, original size and scale
	D3DXMatrixTranslation(&transMat, (position.x + drawSize.x * scale.x / 2.0f) / (drawSize.x * scale.x), -(position.y + drawSize.y * scale.y / 2.0f) / (drawSize.y * scale.y), (position.z));
	//after it is moved, make sure it is the correct scaled size
	D3DXMatrixScaling(&scaleMat, scale.x * drawSize.x, scale.y * -drawSize.y, 1.0f);
	//D3DXMatrixScaling(&scaleMat, -1.0 * 256.0/32.0, -1.0 * 416.0 / 32.0, 1.0);
	//use the translation matrix and scale matrix that we just made to represent its position and scale to set its matWorld
	sprite->matWorld = transMat * scaleMat;
	//then, make sure that if it has a texCoord, that it is moved to that spot in its image
	sprite->TexCoord = texCoord;
}