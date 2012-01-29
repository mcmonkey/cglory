#include "stdafx.h"
#include "XMLLoader.h"

void XMLLoader::loadSpriteInfo(const char *xmlPath, std::vector<SpriteInfo*>* spriteInfo)
{
	TiXmlDocument doc( xmlPath );
	if(doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);
		pElem = hDoc.FirstChildElement().Element();
		hRoot=TiXmlHandle(pElem);
		//block: Sprites
		pElem = hRoot.FirstChild( "Sprites" ).FirstChild().Element();
		for( pElem; pElem; pElem=pElem->NextSiblingElement())
		{
			const char *pKey=pElem->Value();
			const char *pText=pElem->GetText();
			if(pKey && pText)
			{
				spriteInfo->push_back(new SpriteInfo(pKey, pText));
			}
		}
	}
	else
	{
	}
}