#pragma once
#include "../GameComponents/GameObject.h"
#include "TankState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "../GameComponents/SpawnProjectTile.h"
#include "State.h"

enum TankType {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class Tank : public GameObject
{
	Tank();

	static Tank *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	TankType type;

public:
	Tank(float x, float y, TankType type);
	static void LoadResources();

	int HP = 20;

	TankType GetTankType() { return this->type; }

	static Tank *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	void Update(DWORD dt) override;

	void Render() override;

	void OnCollision();
};