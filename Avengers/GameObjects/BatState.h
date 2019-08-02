#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "Bat.h"

class Bat;
enum StateBat
{
	BAT_STATE_IDLE,//đứng yên
	BAT_STATE_GOING_TO_FLY,//chuẩn bị bay
	BAT_STATE_FLYING,//bay
};

class BatState : public State
{
protected:
	static BatState * __instance;
	StateBat stateBat;
	Bat *bat;
	Animation * anim;
	DWORD dt;

public:
	float timeCount;
	BatState(Bat *bat);
	~BatState();

	static BatState * GetInstance(Bat *bat);

	//Lấy trạng thái
	StateBat GetState();
	//Set trạng thái
	void SetState(StateBat State);

	void state_idle();
	void state_going_to_fly();
	void state_flying();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
