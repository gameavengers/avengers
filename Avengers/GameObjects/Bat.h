#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameObjects/BatState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "State.h"

class Bat : public GameObject
{
	Bat();

	static Bat *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	Bat(float x, float y);
	void LoadResources();

	static Bat *GetInstance();

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