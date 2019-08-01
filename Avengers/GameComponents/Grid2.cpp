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
	//runningMan = RunningMan::GetInstance();
	//domesto = Domesto::GetInstance();
	//gigi = Gigi::GetInstance();
	boss1 = Boss1::GetInstance();
	boss1->SetPositionX(20);
	//boss2 = Boss2::GetInstance();
	//barrel = new Barrel();
	//redbox = RedBox::GetInstance();
}

void Grid2::InitializeMapGrid(TileMap2 *tileMap2)
{
	mapSize = tileMap2->currentMap->size / 4;
	listCell = new GridData[mapSize*mapSize];

	for (int y = 0; y < mapSize; y++)
		for (int x = 0; x < mapSize; x++)
			for (int yy = 0; yy < GRID_SIZE_BY_TILE; yy++)
				for (int xx = 0; xx < GRID_SIZE_BY_TILE; xx++)
				{
					Tile2* tempTile = tileMap2->currentMap->GetTile(xx + x * GRID_SIZE_BY_TILE, yy + y * GRID_SIZE_BY_TILE);
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

	static int a = 0;
	if (a == 0 && viewport->GetRect().left > 100)
	{
		SpawnObject(3, GetCell(5, 1)->tiles.at(5));
		a++;
	}

	return nearbyTiles;
}

void Grid2::SpawnObject(int ObjectID, Tile2* tile)
{
	switch (ObjectID)
	{
	case 1:
	{
		RunningMan* object = new RunningMan(tile->x * TILE_SIZE, tile->y * TILE_SIZE, RunningManType::NORMAL);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	case 2:
	{
		RunningMan* object = new RunningMan(tile->x * TILE_SIZE, tile->y * TILE_SIZE, RunningManType::ONLY_RUN);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	case 3:
	{
		RunningMan* object = new RunningMan(tile->x * TILE_SIZE, tile->y * TILE_SIZE, RunningManType::ONLY_CROUCH);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	case 4:
	{
		Domesto* object = new Domesto(tile->x * TILE_SIZE, tile->y * TILE_SIZE, DemestoType::STAY_FIRE_STRAIGHT);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	case 5:
	{
		Domesto* object = new Domesto(tile->x * TILE_SIZE, tile->y * TILE_SIZE, DemestoType::WALK_FIRE_STAIGHT);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	case 6:
	{
		RedBox* object = new RedBox(tile->x * TILE_SIZE, tile->y * TILE_SIZE);
		OnUpdateObject temp;
		temp.object = object;
		temp.tile = tile;
		tile->bCanSpawn = false;
		listObject.push_back(temp);
	}
	break;
	}
}

bool Grid2::CheckObjectInsideCamera(GameObject* object)
{
	RECT rect = viewport->GetRect();
	if (object->GetPositionX() < rect.left || object->GetPositionX() > rect.right ||
		object->GetPositionY() < rect.bottom || object->GetPositionY() > rect.top)
		return false;
	return true;
}

void Grid2::Update(DWORD dt)
{
	//UpdateCurrentTiles();
	captain->Update(dt);
	//runningMan->Update(dt);
	//domesto->Update(dt);
	boss1->Update(dt);
	//redbox->Update(dt);
	SpawnProjectTile::GetInstance()->UpdateBullet(dt);
	SpawnProjectTile::GetInstance()->UpdateItem(dt);

	for (int i = 0; i < listObject.size(); i++)
	{
		if (listObject.at(i).disable)
			continue;

		listObject.at(i).object->Update(dt);

		if (!CheckObjectInsideCamera(listObject.at(i).object))
			listObject.at(i).disable = true;
	}
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
			//GetCell(x,y)->tiles[0]->SpawnObjectID
		}
	}

	captain->Render();
	//runningMan->Render();
	//domesto->Render();
	//gigi->Render();
	boss1->Render();
	//redbox->Render();
	/*boss2->Render();
	barrel->Render();*/
	SpawnProjectTile::GetInstance()->RenderBullet();
	SpawnProjectTile::GetInstance()->RenderItem();

	for (int i = 0; i < listObject.size(); i++)
	{
		if (listObject.at(i).disable)
			continue;
		listObject.at(i).object->Render();
	}
}
