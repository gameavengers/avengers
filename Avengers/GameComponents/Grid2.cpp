#include "Grid2.h"

Grid2* Grid2::_instance;

Grid2* Grid2::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Grid2();
	}
	return _instance;
}

Grid2::Grid2()
{
	captain = Captain::GetInstance();
	viewport = Viewport::GetInstance();
	runningMan = RunningMan::GetInstance();
	domesto = Domesto::GetInstance();
	gigi = Gigi::GetInstance();
	boss1 = Boss1::GetInstance();
	boss2 = Boss2::GetInstance();
	barrel = new Barrel();
}

void Grid2::InitializeMapGrid()
{
	mapSize = TileMap2::GetInstance()->currentMap->size / 4;
	listCell = new GridData[mapSize*mapSize];

	for (int y = 0; y < mapSize; y++)
		for (int x = 0; x < mapSize; x++)
			for (int yy = 0; yy < GRID_SIZE_BY_TILE; yy++)
				for (int xx = 0; xx < GRID_SIZE_BY_TILE; xx++)
				{
					Tile2* tempTile = TileMap2::GetInstance()->currentMap->GetTile(xx + x * GRID_SIZE_BY_TILE, yy + y * GRID_SIZE_BY_TILE);
					(listCell + x + y * mapSize)->tiles.push_back(tempTile);
				}
}

void Grid2::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = viewport->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
	if (r >= mapSize)
		r = mapSize-1;
	if (t >= mapSize)
		t = mapSize - 1;
}

void Grid2::UpdateCurrentTiles()
{
	currentTile.clear();
	RECT rect = captain->GetRect();
	int left = (int)(rect.left / GRID_SIZE);
	int right = (int)(rect.right / GRID_SIZE);
	int top = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	int bottom = (int)(rect.bottom / GRID_SIZE);

	for (int x = left; x <= right; x++)
	{
		for (int y = bottom; y <= top; y++)
		{
			currentTile.insert(currentTile.end(), GetCell(x, y)->tiles.begin(), GetCell(x, y)->tiles.end());
		}
	}
}

vector<Tile2 *> Grid2::GetNearbyTiles(int l, int r, int t, int b)
{
	vector<Tile2*> nearbyTiles;
	int left = (int)(l / GRID_SIZE);
	int right = (int)(r / GRID_SIZE);
	int top = (int)(t % GRID_SIZE == 0 ? t / GRID_SIZE - 1 : t / GRID_SIZE);
	int bottom = (int)(b / GRID_SIZE);

	for (int x = left; x <= right; x++)
	{
		for (int y = bottom; y <= top; y++)
		{
			nearbyTiles.insert(nearbyTiles.end(), GetCell(x, y)->tiles.begin(), GetCell(x, y)->tiles.end());
		}
	}

	return nearbyTiles;
}

vector<Tile2 *> Grid2::GetNearbyTiles(RECT rect)
{
	vector<Tile2*> nearbyTiles;
	int left = (int)(rect.left / GRID_SIZE);
	int right = (int)(rect.right / GRID_SIZE);
	int top = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	int bottom = (int)(rect.bottom / GRID_SIZE);

	for (int x = left; x <= right; x++)
	{
		for (int y = bottom; y <= top; y++)
		{
			nearbyTiles.insert(nearbyTiles.end(), GetCell(x, y)->tiles.begin(), GetCell(x, y)->tiles.end());
		}
	}

	if (nearbyTiles[0]->tileId == 0)
	{
		int a = 0;
	}

	return nearbyTiles;
}

void Grid2::Update(DWORD dt)
{
	//UpdateCurrentTiles();
	captain->Update(dt);
	runningMan->Update(dt);
	domesto->Update(dt);
	boss1->Update(dt);
}

void Grid2::Render()
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);

	for (int y = bCell; y <= tCell; y++)
	{
		for (int x = lCell; x <= rCell; x++)
		{
			(listCell + x + y * mapSize)->Render();
		}
	}

	captain->Render();
	runningMan->Render();
	domesto->Render();
	gigi->Render();
	boss1->Render();
	/*boss2->Render();
	barrel->Render();*/
}
