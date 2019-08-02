#pragma once
#include "../GameComponents/GameObject.h"

enum BulletType {
	BULLET_NORMAL, //đạn của running man
	BULLET_TANK, //đạn của mấy tháp súng
	BULLET_BOSS2, //đạn của con boss 2
	ROCKET, //tên lửa
	BULLET_NORMAL_BOSS1, //đạn thường (nhỏ) của boss 1
	BULLET_SPECIAL_BOSS1, //đạn đặc biệt (lớn) của boss 1
};


class Bullet : public GameObject
{
private:
	void LoadResources();

	vector<Animation *> animations;

	BulletType type;
	
	// 1:Left	2:B-L	3:Bottom	4:B-R	5:Right	6:T-R	7:Top	8:T-L
	int direction;
	
	float timeCount;

public:
	Bullet(float x, float y, int direction,BulletType type);
	~Bullet();

	void Initialize(float x, float y, int direction, BulletType type);

	void BulletNormalUpdate(DWORD dt);
	void BulletTankUpdate(DWORD dt);
	void BulletBoss2Update(DWORD dt);
	void RocketUpdate(DWORD dt);
	void BulletNormalBoss1Update(DWORD dt);
	void BulletSpecialBoss1Update(DWORD dt);

	bool IsDisable() { return disable; }
	void Disable() { timeCount = 0; disable = true; }

	void Update(DWORD dt) override;
	void Render() override;

	bool disable;
};


