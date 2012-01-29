#include "StdAfx.h"
#include "MapSelectionMenu.h"


MapSelectionMenu::MapSelectionMenu(void)
{
	generalInit();
	setupSprites();
}


MapSelectionMenu::~MapSelectionMenu(void)
{
}

void MapSelectionMenu::setupOptions()
{
	title = L"Load Map";
	// Load xml in. Store Paths in pathnames
	// foreach map
	// pathnames[i++] = path
	// addoption(name, i)
	// leave UIMenu::setupOptions();
	TiXmlDocument doc( "maplist.xml");
	if(doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);
		pElem = hDoc.FirstChildElement().Element();
		hRoot=TiXmlHandle(pElem);
		TiXmlElement* pMap = hRoot.FirstChild("Map").ToElement();
		int i=0;
		for(pMap; pMap; pMap = pMap->NextSiblingElement("Map"))
		{
			pathNames.insert(pair<int, string>(i, pMap->Attribute("path")));
			addOption(Utility::widen(pMap->Attribute("name")), i);
			i++;
		}
	}
	//addOption(L"Pea Island, 2p", 0);
	//addOption(L"Dev Map, 2p", 1);
	UIMenu::setupOptions();
}

void MapSelectionMenu::select(int id)
{
	if(id < pathNames.size())
	{
	
		PlayManager::newMap(Map::loadFromXML(pathNames.at(id).c_str()));
		return;
	}
	UIMenu::select(id);
}
