#pragma once

namespace TerrainType{
	enum tT
	{
		GRASS,
		ROAD,
		WATER,
		MOUNTAIN,
		Count
	};
}

namespace MovementType{
	enum mT
	{
		FOOT,
		WHEEL,
		TREAD,
		WATER,
		AIR,
		UNDERGROUD,
		Count
	};
}

namespace MovementDirection
{
	enum mD
	{
		DOWN = 0,
		LEFT = 1,
		UP = 2,
		RIGHT = 3,
		Count = 4
	};
}

namespace ZOrdering
{
	enum zo
	{
		//0-10 = Map
		Terrain		= 0,
		Building	= -3,
		Unit		= -5,
		Fog			= -7,

		// 11-20 Menus
		MapOverlay	= -11,
		MapSelector = -13,
		HUD			= -15,
		Menus		= -17,

		DeveloperConsole = -21,
		MouseCursor = -22,
	};
}

namespace MenuType
{
	enum menuT
	{
		UnitOptions,
		BuildingOptions,
		BuildingProductionOptions,
		Count
	};
}

namespace GameState
{
	enum gT
	{
		Default,
		InMenu,
		MovementSelect,
		Count
	};
}

namespace CellLayers
{
	enum cL
	{
		Terrain,
		Building,
		Unit,
		Count	// Keep at the end, used for looping
	};
}

namespace GameObjects
{
	enum gO
	{
		Terrain,
		Building,
		Unit
	};
}

namespace GameStats
{
	enum gS
	{
		Attack,
		MinRange,
		MaxRange,
		Movement,
		MovementType,
		Defense,
		Health,
		MaxHealth,
		Sight,
		GloryMod
	};
}