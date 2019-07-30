#pragma once
#include "../GameComponents/GameObject.h"

enum BulletType {
	BULLET_NORMAL, //đạn của running man
	BULLET_TANK, //đạn của mấy tháp súng
	BULLET_BOSS2, //đạn của con boss 2
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


