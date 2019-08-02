#pragma once
#include "../GameComponents/GameObject.h"
#include "RedBoxState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "State.h"
#include "../GameComponents/SpawnProjectTile.h"

class RedBox : public GameObject
{
	RedBox();

	static RedBox *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	RedBox(float x, float y);
	void LoadResources();

	static RedBox *GetInstance();

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