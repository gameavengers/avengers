#include "TileMap2.h"

TileMap2* TileMap2::_instance = nullptr;

TileMap2 * TileMap2::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TileMap2();

		_instance->LoadTilesData(TILES_MATRIX_STAGE_1, TILES_SET_MATRIX_STAGE_1);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_BOSS_1, TILES_SET_STAGE_BOSS_1);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_2, TILES_SET_MATRIX_STAGE_2);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_BOSS_2, TILES_SET_STAGE_BOSS_2);
	}
	return _instance;
}

void TileMap2::LoadTilesData(LPCWSTR filePath, LPCWSTR tileSetLocation)
{
	MapPack map;

	ifstream tilesData;
	tilesData.open(filePath);

	string data;

	tilesData >> data;
	int size = stoi(data);

	map.size = size;
	
	tilesData >> data;
	map.height = stoi(data);

	map.tiles = new Tile2[size*size];

	for (int y = map.height - 1; y >= 0; y--)
		for (int x = 0; x < map.size; x++)
		{
			tilesData >> data;
			(map.tiles + x + y * size)->tileId = stoi(data);

			if ((map.tiles + x + y * size)->tileId == 10 || (map.tiles + x + y * size)->tileId == 91)
			{
				(map.tiles + x + y * size)->type = ObjectType::BRICK;
			}
			(map.tiles + x + y * size)->x = x;
			(map.tiles + x + y * size)->y = y;
		}

	for (int y = map.size - 1; y > map.height - 1; y--)
		for (int x = 0; x < map.size; x++)
		{
			(map.tiles + x + y * size)->tileId = -1;
			(map.tiles + x + y * size)->x = x;
			(map.tiles + x + y * size)->y = y;
		}
	
	tilesData.close();

	// Load Tile Set
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFile(tileSetLocation, &info);

	for (int i = 0; i < info.Width / TILE_SIZE; i++)
	{
		RECT rect;
		rect.left = i * TILE_SIZE;
		rect.right = rect.left + TILE_SIZE;
		rect.top = 0;
		rect.bottom = rect.top + TILE_SIZE;

		Sprite *tempTile = new Sprite(tileSetLocation, rect, TILES_TRANSCOLOR);
		map.TilesSetSprite.push_back(tempTile);
	}
	mapList.push_back(map);
	currentMap = &mapList.at(0);
}

void TileMap2::SetCurrentMap(int mapID)
{
	currentMap = &mapList[mapID];
}

void TileMap2::Render(int x, int y)
{
	if (currentMap->GetTile(x, y)->tileId == -1)
		return;

	SpriteData spriteData;
	spriteData.width = TILE_SIZE;
	spriteData.height = TILE_SIZE;
	spriteData.x = x * TILE_SIZE;
	spriteData.y = y * TILE_SIZE;
	spriteData.isLeft = true;


	currentMap->GetSpriteByID(currentMap->GetTile(x, y)->tileId)->SetData(spriteData);
	
	Graphics::GetInstance()->Draw(currentMap->GetSpriteByID(currentMap->GetTile(x, y)->tileId));
}

void TileMap2::Render(Tile2* itile)
{
	if (itile->tileId == -1)
		return;

	SpriteData spriteData;
	spriteData.width = TILE_SIZE;
	spriteData.height = TILE_SIZE;
	spriteData.x = itile->x * TILE_SIZE;
	spriteData.y = itile->y * TILE_SIZE;
	
	spriteData.isLeft = true;


	Sprite* temp = currentMap->GetSpriteByID(itile->tileId);
	temp->SetData(spriteData);

	Graphics::GetInstance()->Draw(temp);
}


