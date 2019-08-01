#pragma once
#include "../GameComponents/GameObject.h"
#include "RunningManState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "../GameComponents/SpawnProjectTile.h"
#include "State.h"


enum RunningManType
{
	NORMAL,
	ONLY_RUN,
	ONLY_CROUCH,
};

class RunningMan : public GameObject
{
	RunningMan();

	static RunningMan *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	RunningManType type;

	bool isGrounded = false;

public:
	RunningMan(float x, float y, RunningManType type = NORMAL);
	void LoadResources();

	static RunningMan *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	bool IsGrounded() { return isGrounded; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	RunningManType GetRunningManType() {return type;}

	void Update(DWORD dt) override;

	void Render() override;
};