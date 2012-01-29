#include "StdAfx.h"
#include "BuildingInfo.h"
#include "InformationStorage.h"

BuildingInfo::BuildingInfo(void)
{
}


BuildingInfo::~BuildingInfo(void)
{
}

void BuildingInfo::factory(Building* b)
{
	for(int i = 0; i < productionIds.size(); i++)
	{
		b->availableProduction.push_back(productionIds[i]);
	}
	
	b->defense	= defense;
	b->name		= name;
	b->gSprite	= sprite;
	b->gloryMod	= gloryMod;
	b->id		= id;
	b->health	= health;
	b->maxHealth = health;
}

void BuildingInfo::load(TiXmlNode* pBuildingNode)
{
	TiXmlNode* pBuildingInfoNode, *pProductionIDNode;

	//Set the ID
	pBuildingInfoNode = pBuildingNode->FirstChild("ID");
	id = atoi(pBuildingInfoNode->ToElement()->GetText());

	//Set the name
	//Using string::assign() to avoid problems with const char*[] being returned
	pBuildingInfoNode = pBuildingNode->FirstChild("Name");
	name.assign(pBuildingInfoNode->ToElement()->GetText());

	//Set the defense
	pBuildingInfoNode = pBuildingNode->FirstChild("Defense");
	defense = atoi(pBuildingInfoNode->ToElement()->GetText());

	//Set the glory mod
	pBuildingInfoNode = pBuildingNode->FirstChild("GloryMod");
	gloryMod = atoi(pBuildingInfoNode->ToElement()->GetText());

	//Load in the maxhealth, and set the buildings health and max health
	pBuildingInfoNode = pBuildingNode->FirstChild("Health");
	health = atoi(pBuildingInfoNode->ToElement()->GetText());

	//Set the production IDS
	pProductionIDNode = pBuildingNode->FirstChild("Production")->FirstChild();
	for(pProductionIDNode; pProductionIDNode; pProductionIDNode=pProductionIDNode->NextSiblingElement())
	{
		productionIds.push_back(atoi(pProductionIDNode->ToElement()->GetText()));
	}

	pBuildingInfoNode = pBuildingNode->FirstChild("SpritePath");
	//wchar_t tempPath[1024];
	//MultiByteToWideChar(0, 0, pBuildingInfoNode->ToElement()->GetText(), -1, tempPath, 0);

	wstring tempPath = Utility::widen(pBuildingInfoNode->ToElement()->GetText());
	Utility::spriteFactory(&sprite, tempPath.c_str());

	pBuildingInfoNode = pBuildingNode->FirstChild("TextureCoordinates");
	float tempXCoord = 0;
	float tempYCoord = 0;
			
	pBuildingInfoNode->ToElement()->QueryFloatAttribute("x", &tempXCoord);
	pBuildingInfoNode->ToElement()->QueryFloatAttribute("y", &tempYCoord);

	sprite.texCoord.x = tempXCoord/(sprite.getSize().x/Stats::getTilesize());
	sprite.texCoord.y = tempYCoord/(sprite.getSize().y/Stats::getTilesize());
	sprite.position.z = ZOrdering::Building;

	sprite.drawSize = D3DXVECTOR2(Stats::getTilesize(), Stats::getTilesize());
	sprite.sprite->TexSize.x = 1.0f/(sprite.originalSize.x/Stats::getTilesize());
	sprite.sprite->TexSize.y = 1.0f/(sprite.originalSize.y/Stats::getTilesize());
	sprite.position = D3DXVECTOR3(tempXCoord, tempYCoord, ZOrdering::Building);
}