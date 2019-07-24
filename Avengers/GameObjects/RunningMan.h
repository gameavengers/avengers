#pragma once
#include "../GameComponents/GameObject.h"
#include "RunningManState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "State.h"

class RunningMan : public GameObject
{
	RunningMan();

	static RunningMan *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	void LoadResources();

	static RunningMan *GetInstance();

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
};