﻿#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "RunningMan.h"

class RunningMan;
enum StateRunningMan
{
	RUNNING_MAN_STATE_RUNNING,//Chạy
	RUNNING_MAN_STATE_STANDING_SHOOT,//Đứng bắn
	RUNNING_MAN_STATE_CROUCH_SHOOT,//Ngồi bắn
	RUNNING_MAN_STATE_DEAD,//Chết
};

class RunningManState : public State
{
protected:
	static RunningManState * __instance;
	StateRunningMan stateRunningMan;
	RunningMan *runningMan;
	Animation * anim;
public:
	RunningManState(RunningMan *runningMan);
	~RunningManState();

	static RunningManState * GetInstance(RunningMan *runningMan);

	//Lấy trạng thái
	StateRunningMan GetState();
	//Set trạng thái
	void SetState(StateRunningMan State);

	void state_running();
	void state_standing_shoot();
	void state_crouch_shoot();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
