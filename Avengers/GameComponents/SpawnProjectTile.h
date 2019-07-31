#pragma once
#include "GameObject.h"
#include "../GameObjects/Bullet.h"

class SpawnProjectTile
{
private:
	static SpawnProjectTile* _instance;
public:
	static SpawnProjectTile* GetInstance();

	vector<Bullet*> listBullet;

	void SpawnBullet(float x, float y, int direction, BulletType type);
	void UpdateBullet(DWORD dt);
	void RenderBullet();
};