#pragma once
#include "../GameComponents/GameObject.h"

enum BulletType {
	BULLET_NORMAL,
	BULLET_TANK,
	BULLET_BOSS2
};


class Bullet : public GameObject
{
private:
	void LoadResources();

	vector<Animation *> animations;

	BulletType type;
public:
	Bullet();
	~Bullet();

	void Update(DWORD dt) override;
	void Render() override;
};


