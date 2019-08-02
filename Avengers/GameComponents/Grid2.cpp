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
	boss1->SetPositionX(48);
	//boss2 = Boss2::GetInstance();
	//barrel = new Barrel();
	//redbox = RedBox::GetInstance();
	spawnboss = false;
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
					if (tempTile->SpawnObjectID != 0)
						(listCell + x + y * mapSize)->hasSpawnTiles.push_back(tempTile);
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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

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

		if (captain->GetPositionX() < object->GetPositionX())
			object->setIsLeft(true);
		else
			object->setIsLeft(false);

		listObject.push_back(temp);
	}
	break;
	}
}

bool Grid2::CheckObjectInsideCamera(GameObject* object)
{
	if (timeCount < 2000)
		return true;

	int test = 1;

	RECT rect = viewport->GetRect();
	if (object->GetPositionX() < rect.left - 64* test || object->GetPositionX() > rect.right + 64 * test ||
		object->GetPositionY() < rect.bottom - 64 * test || object->GetPositionY() > rect.top + 64 * test)
		return false;
	return true;
}

void Grid2::Update(DWORD dt)
{
	timeCount += dt;
	//UpdateCurrentTiles();
	captain->Update(dt);
	captain->UpdateCollision(dt);
	//runningMan->Update(dt);
	//domesto->Update(dt);
	if (spawnboss)
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
		{
			listObject.at(i).disable = true;
			// listObject.at(i).tile->bCanSpawn = true;
		}

		/*if (listObject.at(i).disable)
		{
			listObject.at(i).timeCount += dt;
			if (listObject.at(i).timeCount >= listObject.at(i).delaySpawn)
			{
				listObject.at(i).timeCount = 0;
				listObject.at(i).tile->bCanSpawn = true;
			}

		}*/
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
			
			if ((listCell + x + y * mapSize)->hasSpawnTiles.size() > 0)
			{
				for (int i = 0; i < (listCell + x + y * mapSize)->hasSpawnTiles.size(); i++)
				{
					if (!(listCell + x + y * mapSize)->hasSpawnTiles.at(i)->bCanSpawn)
						continue;

					SpawnObject((listCell + x + y * mapSize)->hasSpawnTiles.at(i)->SpawnObjectID, 
								(listCell + x + y * mapSize)->hasSpawnTiles.at(i));
					(listCell + x + y * mapSize)->hasSpawnTiles.at(i)->bCanSpawn = false;
				}
			}

			/*for (int t = 0; t < GRID_SIZE_BY_TILE; t++)
				for (int z = 0; z < GRID_SIZE_BY_TILE; z++)
				{
					if (GetCell(x, y)->tiles.at(z + t * GRID_SIZE_BY_TILE)->bCanSpawn)
					{
						if (!GetCell(x, y)->tiles.at(z + t * GRID_SIZE_BY_TILE)->bCanSpawn)
							continue;
						SpawnObject(GetCell(x, y)->tiles.at(z + t * GRID_SIZE_BY_TILE)->SpawnObjectID, GetCell(x, y)->tiles.at(z + t * GRID_SIZE_BY_TILE));
						GetCell(x, y)->tiles.at(z + t * GRID_SIZE_BY_TILE)->bCanSpawn = false;
					}
				}*/
		}
	}

	//runningMan->Render();
	//domesto->Render();
	//gigi->Render();
	if (spawnboss)
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
	captain->Render();
}
