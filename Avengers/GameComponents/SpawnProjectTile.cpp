#include "SpawnProjectTile.h"

SpawnProjectTile* SpawnProjectTile::_instance;


SpawnProjectTile* SpawnProjectTile::GetInstance()
{
	if (_instance == nullptr)
		_instance = new SpawnProjectTile();
	return _instance;
}

void SpawnProjectTile::SpawnBullet(float x, float y, int direction, BulletType type)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->IsDisable())
		{
			listBullet.at(i)->Initialize(x, y, direction, type);
			return;
		}
	}

	Bullet* newBullet = new Bullet(x, y, direction, type);

	listBullet.push_back(newBullet);
}

void SpawnProjectTile::UpdateBullet(DWORD dt)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet.at(i)->Update(dt);
	}
}

void SpawnProjectTile::RenderBullet()
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet.at(i)->Render();
	}
}

