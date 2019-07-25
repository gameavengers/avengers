#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "Boss1.h"

class Boss1;
enum StateBoss1
{
	BOSS1_STATE_IDLE,//Đứng 
	BOSS1_STATE_RUNNING,//Chạy
	BOSS1_STATE_BLEEDING,//
	BOSS1_STATE_DEAD,//Chết
	BOSS1_STATE_STANDING_SHOOT_1,//Đứng bắn kiểu 1
	BOSS1_STATE_STANDING_SHOOT_2,// Đứng bắn kiểu 2
	BOSS1_STATE_FLYING,//Bay
	BOSS1_STATE_FLYING_SHOOT,//Bắn xuống khi bay
};

class Boss1State : public State
{
protected:
	static Boss1State * __instance;
	StateBoss1 stateBoss1;
	Boss1 *boss1;
	Animation * anim;
public:
	Boss1State(Boss1 *boss1);
	~Boss1State();

	static Boss1State * GetInstance(Boss1 *boss1);

	//Lấy trạng thái
	StateBoss1 GetState();
	//Set trạng thái
	void SetState(StateBoss1 State);

	void state_idle();
	void state_running();
	void state_bleeding();
	void state_dead();
	void state_standing_shoot_1();
	void state_standing_shoot_2();
	void state_flying();
	void state_flying_shoot();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
