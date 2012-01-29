#include "stdafx.h"
#include "CardInfo.h"

CardInfo::CardInfo(void)
{
}

CardInfo::~CardInfo(void)
{
}

void CardInfo::factory(Card* c)
{
	for(int i=0; i<effects.size(); i++)
	{
		c->effects.push_back(effects[i]);
	}
	c->id = id;
	c->description = description;
	c->name = name;
	c->purchaseCost = purchaseCost;
	c->playCost = playCost;
}

void CardInfo::load(TiXmlNode* pCardNode)
{
	TiXmlNode* pCardInfoNode, *pCardIdNode, *pEffectNode;

	//Set the ID
	pCardInfoNode = pCardNode->FirstChild("ID");
	id = atoi(pCardInfoNode->ToElement()->GetText());

	//Set the Name
	pCardInfoNode = pCardNode->FirstChild("Name");
	name = pCardInfoNode->ToElement()->GetText();

	//Set the description
	pCardInfoNode = pCardNode->FirstChild("Description");
	description = pCardInfoNode->ToElement()->GetText();

	//Set the purchase cost
	pCardNode->ToElement()->QueryIntAttribute("purchasecost", &purchaseCost);

	//Set the play cost
	pCardNode->ToElement()->QueryIntAttribute("playcost", &playCost);

	//Set the effects

	//StatChangers
	pEffectNode = pCardNode->FirstChild("StatChanger");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("StatChanger"))
	{
		StatChanger *sc = new StatChanger();
		pEffectNode->ToElement()->QueryIntAttribute("stat", &(sc->stat));
		pEffectNode->ToElement()->QueryIntAttribute("modifier", &(sc->modifier));
		pEffectNode->ToElement()->QueryIntAttribute("layer", &(sc->layer));
		pCardIdNode = pEffectNode->FirstChild("Legal")->FirstChild();
		for(pCardIdNode; pCardIdNode; pCardIdNode = pCardIdNode->NextSiblingElement())
		{
			sc->legalIDs.push_back(atoi(pCardIdNode->ToElement()->GetText()));
		}
		effects.push_back((CardEffect*)sc);
	}

	//UnitPromoters
	pEffectNode = pCardNode->FirstChild("UnitPromoter");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("UnitPromoter"))
	{
		UnitPromoter* up = new UnitPromoter();
		pEffectNode->ToElement()->QueryIntAttribute("exp", &(up->expReq));
		pEffectNode->ToElement()->QueryIntAttribute("newID", &(up->newUnitID));
		pCardIdNode = pEffectNode->FirstChild("Legal")->FirstChild();
		for(pCardIdNode; pCardIdNode; pCardIdNode = pCardIdNode->NextSiblingElement())
		{
			up->legalIDs.push_back(atoi(pCardIdNode->ToElement()->GetText()));
		}
		effects.push_back((CardEffect*)up);
	}

	//GloryRemover
	pEffectNode = pCardNode->FirstChild("GloryRemover");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("GloryRemover"))
	{
		GloryRemover* gr = new GloryRemover();
		pEffectNode->ToElement()->QueryIntAttribute("modifier", &(gr->gloryMod));
		effects.push_back((CardEffect*)gr);
	}

	//CardDiscarder
	pEffectNode = pCardNode->FirstChild("CardDiscarder");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("CardDiscarder"))
	{
		CardDiscarder* cd = new CardDiscarder();
		pEffectNode->ToElement()->QueryIntAttribute("cards", &(cd->numCards));
		effects.push_back((CardEffect*)cd);
	}

	//ObjectProducer
	pEffectNode = pCardNode->FirstChild("ObjectProducer");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("ObjectProducer"))
	{
		ObjectProducer* op = new ObjectProducer();
		pEffectNode->ToElement()->QueryIntAttribute("layer", &(op->layer));
		pEffectNode->ToElement()->QueryIntAttribute("id", &(op->id));
		effects.push_back((CardEffect*)op);
	}

	//SpecialAttacks
	pEffectNode = pCardNode->FirstChild("SpecialAttack");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("SpecialAttack"))
	{
		SpecialAttack* sa = new SpecialAttack();
		pEffectNode->ToElement()->QueryIntAttribute("minRange", &(sa->minRange));
		pEffectNode->ToElement()->QueryIntAttribute("maxRange", &(sa->maxRange));
		pEffectNode->ToElement()->QueryIntAttribute("damage", &(sa->damage));
		pEffectNode->ToElement()->QueryIntAttribute("heal", &(sa->heal));
		pCardIdNode = pEffectNode->FirstChild("Legal")->FirstChild();
		for(pCardIdNode; pCardIdNode; pCardIdNode = pCardIdNode->NextSiblingElement())
		{
			sa->legalAttackers.push_back(atoi(pCardIdNode->ToElement()->GetText()));
		}
		effects.push_back((CardEffect*)sa);
	}

	//BurstAttacks
	pEffectNode = pCardNode->FirstChild("BurstAttack");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("BurstAttack"))
	{
		BurstAttack* ba = new BurstAttack();
		pEffectNode->ToElement()->QueryIntAttribute("minRange", &(ba->minRange));
		pEffectNode->ToElement()->QueryIntAttribute("maxRange", &(ba->maxRange));
		pEffectNode->ToElement()->QueryIntAttribute("damage", &(ba->damage));
		pEffectNode->ToElement()->QueryIntAttribute("heal", &(ba->heal));
		pEffectNode->ToElement()->QueryIntAttribute("burst", &(ba->burst));
		pCardIdNode = pEffectNode->FirstChild("Legal")->FirstChild();
		for(pCardIdNode; pCardIdNode; pCardIdNode = pCardIdNode->NextSiblingElement())
		{
			ba->legalAttackers.push_back(atoi(pCardIdNode->ToElement()->GetText()));
		}
		effects.push_back((CardEffect*)ba);
	}

	//LineAttacks
	pEffectNode = pCardNode->FirstChild("LineAttack");
	for(pEffectNode; pEffectNode; pEffectNode = pEffectNode->NextSiblingElement("LineAttack"))
	{
		LineAttack* la = new LineAttack();
		pEffectNode->ToElement()->QueryIntAttribute("minRange", &(la->minRange));
		pEffectNode->ToElement()->QueryIntAttribute("maxRange", &(la->maxRange));
		pEffectNode->ToElement()->QueryIntAttribute("damage", &(la->damage));
		pEffectNode->ToElement()->QueryIntAttribute("heal", &(la->heal));
		pEffectNode->ToElement()->QueryIntAttribute("maxTargets", &(la->maxTargets));
		pCardIdNode = pEffectNode->FirstChild("Legal")->FirstChild();
		for(pCardIdNode; pCardIdNode; pCardIdNode = pCardIdNode->NextSiblingElement())
		{
			la->legalAttackers.push_back(atoi(pCardIdNode->ToElement()->GetText()));
		}
		effects.push_back((CardEffect*)la);
	}
}