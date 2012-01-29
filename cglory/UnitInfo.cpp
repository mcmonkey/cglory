#include "StdAfx.h"
#include "UnitInfo.h"


UnitInfo::UnitInfo(void)
{
}


UnitInfo::~UnitInfo(void)
{
}



void UnitInfo::factory(Unit *u)
{
	u->atk = atk;
	u->defense = def;
	u->cost = cost;
	u->gSprite = sprite;
	u->health = health;
	u->maxHealth = health;
	u->id = id;
	u->maxRange = maxRange;
	u->minRange = minRange;
	u->movement = movement;
	u->movementType = movementType;
	u->sightRange = sightRange;
	u->ambushes = ambushes;
	u->bombards = bombards;
	u->captures = captures;
	u->name = name;
	u->description = description;

}

void UnitInfo::load(TiXmlNode* pUnitNode)
{
	//Set the ID
	TiXmlNode* pUnitInfoNode = pUnitNode->FirstChild("ID");
	id = atoi(pUnitInfoNode->ToElement()->GetText());

	//Set the name
	//Using string::assign() to avoid problems with const char*[] being returned
	pUnitInfoNode = pUnitNode->FirstChild("Name");
	name.assign(pUnitInfoNode->ToElement()->GetText());

	//Set the description
	pUnitInfoNode = pUnitNode->FirstChild("Description");
	description.assign(pUnitInfoNode->ToElement()->GetText());

	//Set the sprite path
	pUnitInfoNode = pUnitNode->FirstChild("SpritePath");
	//wchar_t tempPath[1024];
	//std::string testPath = pUnitInfoNode->ToElement()->GetText();
	//MultiByteToWideChar(0, 0, testPath.c_str(), -1, tempPath, 0);
	//tempPath = _T(testPath);
	//Utility::spriteFactory(&sprite, tempPath);

	wstring tempPath = Utility::widen(pUnitInfoNode->ToElement()->GetText());
	Utility::spriteFactory(&sprite, tempPath.c_str());


	pUnitInfoNode = pUnitNode->FirstChild("TextureCoordinates");
	float tempXCoord = 0;
	float tempYCoord = 0;
			
	pUnitInfoNode->ToElement()->QueryFloatAttribute("x", &tempXCoord);
	pUnitInfoNode->ToElement()->QueryFloatAttribute("y", &tempYCoord);

	sprite.texCoord.x = tempXCoord/(sprite.getSize().x/Stats::getTilesize());
	sprite.texCoord.y = tempYCoord/(sprite.getSize().y/Stats::getTilesize());

	sprite.drawSize = D3DXVECTOR2(Stats::getTilesize(), Stats::getTilesize());
	sprite.sprite->TexSize.x = 1.0f/(sprite.originalSize.x/Stats::getTilesize());
	sprite.sprite->TexSize.y = 1.0f/(sprite.originalSize.y/Stats::getTilesize());
	sprite.position = D3DXVECTOR3(tempXCoord, tempYCoord, ZOrdering::Unit);
	sprite.hasAnimation = true;


	//Set the combat statistics
	pUnitInfoNode = pUnitNode->FirstChild("CombatStats");
	pUnitInfoNode->ToElement()->QueryIntAttribute("attack", &atk);
	pUnitInfoNode->ToElement()->QueryIntAttribute("defense", &def);
	pUnitInfoNode->ToElement()->QueryIntAttribute("minrange", &minRange);
	pUnitInfoNode->ToElement()->QueryIntAttribute("maxrange", &maxRange);
	pUnitInfoNode->ToElement()->QueryIntAttribute("health", &health);
	pUnitInfoNode->ToElement()->QueryIntAttribute("movement", &movement);
	pUnitInfoNode->ToElement()->QueryIntAttribute("movementtype", &movementType);
	pUnitInfoNode->ToElement()->QueryIntAttribute("cost", &cost);
	pUnitInfoNode->ToElement()->QueryIntAttribute("sight", &sightRange);
	
	ambushes = captures = bombards = 0;
	pUnitInfoNode->ToElement()->QueryIntAttribute("ambushes", &ambushes);
	pUnitInfoNode->ToElement()->QueryIntAttribute("captures", &captures);
	pUnitInfoNode->ToElement()->QueryIntAttribute("bombards", &bombards);

}