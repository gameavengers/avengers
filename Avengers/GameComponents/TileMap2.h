#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Sprite.h"
#include "Debug.h"
#include "Constants.h"
#include "GameObject.h"

using namespace std;

struct Tile2 {
	int tileId;
	ObjectType type;
	int x, y;
	int size = TILE_SIZE;
	Collider *colider;
};

struct TileSet {
	int id;
	int x;
	int y;
};

struct MapPack {
	int size;
	Tile2* tiles;
	vector <TileSet> tileSet;
	vector <Sprite*> TilesSetSprite;

	Sprite* GetSpriteByID(int id)
	{
		if (id != -1)
			return TilesSetSprite.at(id);
		return nullptr;
	}

	Tile2* GetTile(int x, int y)
	{
		return (tiles + x + y * size);
	}
};

class TileMap2
{
private:

	static TileMap2* _instance;
	
	vector <MapPack> mapList;

	void LoadTilesData(LPCWSTR filePath, LPCWSTR tileSetLocation);

public:
	static TileMap2* GetInstance();
	MapPack* currentMap;
	void Render(int x, int y);
	void Render(Tile2* itile);
};