#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameObjects/Captain.h"

class Captain;
class Bullet : public GameObject
{
private:
	static vector<Animation *> animations;

	BulletType type;
	
	// 1:Left	2:B-L	3:Bottom	4:B-R	5:Right	6:T-R	7:Top	8:T-L
	int direction;
	
	float timeCount;

public:
	static void LoadResources();

	Bullet(float x, float y, int direction,BulletType type);
	~Bullet();

	void Initialize(float x, float y, int direction, BulletType type);

	void BulletNormalUpdate(DWORD dt);
	void BulletTankUpdate(DWORD dt);
	void BulletBoss2Update(DWORD dt);
	void RocketUpdate(DWORD dt);
	void GiGiRocketUpdate(DWORD dt);
	void BulletNormalBoss1Update(DWORD dt);
	void BulletSpecialBoss1Update(DWORD dt);

	bool IsDisable() { return disable; }
	void Disable() { timeCount = 0; disable = true; }

	void Update(DWORD dt) override;
	void Render() override;

	bool disable;
};


