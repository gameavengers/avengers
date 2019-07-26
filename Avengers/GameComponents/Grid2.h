#pragma once
#include "GameObject.h"
#include "Constants.h" 
#include "../GameObjects/Captain.h"

#include <vector>

#include <fstream>
#include <string>

using namespace std;

#define GRID_SIZE_BY_TILE (int)(GRID_SIZE / TILE_SIZE)

struct GridData
{
	vector<Tile2*> tiles;
	int x;
	int y;

	void Render()
	{
		for (int y = 0; y < GRID_SIZE_BY_TILE; y++)
			for (int x = 0; x < GRID_SIZE_BY_TILE; x++)
			{
				TileMap2::GetInstance()->Render(tiles.at(x + y * GRID_SIZE_BY_TILE));
			}
	}
};



class Grid2
{
private:
	static Grid2* _instance;

	int mapSize;

	Viewport* viewport;

	Captain* captain;

	void UpdateCurrentTiles();
public:
	static Grid2* GetInstance();

	Grid2();

	void InitializeMapGrid();

	void GetCameraPosOnGrid(int &l, int &r, int &t, int &b);

	vector<Tile2*> currentTile;
	vector<Tile2 *> GetCurTiles() { return this->currentTile; }

	vector<Tile2 *> GetNearbyTiles(int l, int r, int t, int b);
	vector<Tile2 *> GetNearbyTiles(RECT rect);

	GridData* listCell;

	GridData* GetCell(int x, int y)
	{
		return (listCell + x + y * mapSize);
	}

	void Update(DWORD dt);
	void Render();
};