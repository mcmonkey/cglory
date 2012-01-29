#include "StdAfx.h"
#include "TerrainInfo.h"

TerrainInfo::TerrainInfo(void)
{
	sprite = GameSprite();
}


TerrainInfo::~TerrainInfo(void)
{
}

void TerrainInfo::factory(Terrain & t)
{
	t.id = id;
	t.name = name;
	t.movementCosts = vector<int>();
	for(int i = 0; i < MovementType::Count; i++)
	{
		t.movementCosts.push_back(movementCosts[i]);
	}
	t.defense = defense;
	t.grantsCover = grantsCover;
	t.gSprite = this->sprite;
}

void TerrainInfo::load(TiXmlNode* t)
{
	//Set the ID
	TiXmlNode* pTerrainInfoNode = t->FirstChild("ID");
	id = atoi(pTerrainInfoNode->ToElement()->GetText());

	//Set the name
	//Using string::assign() to avoid problems with const char*[] being returned
	pTerrainInfoNode = t->FirstChild("Name");
	name.assign(pTerrainInfoNode->ToElement()->GetText());

	//Set the defense
	pTerrainInfoNode = t->FirstChild("Defense");
	defense = atoi(pTerrainInfoNode->ToElement()->GetText());

	pTerrainInfoNode = t->FirstChild("GrantsCover");
	int grantsCover = 0;
	pTerrainInfoNode->ToElement()->QueryIntAttribute("value", &grantsCover);
	this->grantsCover = grantsCover;

	//Set the movement costs
	pTerrainInfoNode = t->FirstChild("MovementCosts");
	movementCosts = new int[MovementType::Count];
	pTerrainInfoNode->ToElement()->QueryIntAttribute("foot",	&movementCosts[MovementType::FOOT]);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("wheel",	&movementCosts[MovementType::WHEEL]);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("tread",	&movementCosts[MovementType::TREAD]);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("water",	&movementCosts[MovementType::WATER]);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("air",		&movementCosts[MovementType::AIR]);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("underground", &movementCosts[MovementType::UNDERGROUD]);
			
	pTerrainInfoNode = t->FirstChild("SpritePath");
	string hi = pTerrainInfoNode->ToElement()->GetText();
	// Load sprite.			
	wstring tempPath = Utility::widen(pTerrainInfoNode->ToElement()->GetText());
	Utility::spriteFactory(&sprite, tempPath.c_str());
	
	sprite.position.z = ZOrdering::Terrain;

	pTerrainInfoNode = t->FirstChild("TextureCoordinates");
	int tempXCoord = 0;
	int tempYCoord = 0;
	int animated = 0;

	pTerrainInfoNode->ToElement()->QueryIntAttribute("x", &tempXCoord);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("y", &tempYCoord);
	pTerrainInfoNode->ToElement()->QueryIntAttribute("animated", &animated);

	sprite.hasAnimation = animated;
	sprite.texCoord.x = (tempXCoord * Stats::getTilesize()) / (float)sprite.getSize().x;
	sprite.texCoord.y = (tempYCoord * Stats::getTilesize()) / (float)sprite.getSize().y;
	sprite.animationRow = tempYCoord;
	sprite.drawSize = D3DXVECTOR2(Stats::getTilesize(), Stats::getTilesize());
	sprite.sprite->TexSize.x = 1.0f/(sprite.originalSize.x/Stats::getTilesize());
	sprite.sprite->TexSize.y = 1.0f/(sprite.originalSize.y/Stats::getTilesize());
	sprite.position = D3DXVECTOR3(0, 0, ZOrdering::Terrain);

}
