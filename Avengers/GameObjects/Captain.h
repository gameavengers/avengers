#pragma once
#include "../GameComponents/GameObject.h"
#include "CaptainState.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "State.h"
#include "Shield.h"

class Captain : public GameObject
{
	Captain();

	static Captain *__instance;

	State *state;

	bool isGrounded = false;
	bool isShield = true;
	bool isSwimming = false;
	bool isSwing = false;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	Shield *shield;

public: 
	void LoadResources();

	static Captain *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsShield(bool isShield) { this->isShield = isShield; }
	void SetIsSwimming(bool isSwimming) { this->isSwimming = isSwimming; }
	void SetIsSwing(bool isSwing) { this->isSwing = isSwing; }

	bool IsGrounded() { return isGrounded; }
	bool IsShield() { return isShield; }
	bool IsSwimming() { return isSwimming; }
	bool IsSwing() { return isSwing; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	void Reset();

	vector<Animation *> GetAnimationsList() { return animations; }

	void Update(DWORD dt) override;

	void UpdateCollision(DWORD dt);

	void Render() override;
};