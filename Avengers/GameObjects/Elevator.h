#pragma once
#include "../GameComponents/GameObject.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"

enum ElevatorType
{
	
};

class Elevator : public GameObject
{
	Elevator();

	static Elevator *__instance;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	ElevatorType type;

public:
	Elevator(float x, float y, ElevatorType type);
	void LoadResources();

	static Elevator *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	ElevatorType GetElevatorType() { return type; }

	void Update(DWORD dt) override;

	void Render() override;

	void OnCollision();
};