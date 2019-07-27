#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "Tank.h"

class Tank;
enum StateTank
{
	TANK_STATE_BLEEDING,
	TANK_STATE_TOP,
	TANK_STATE_TOP_RIGHT,
	TANK_STATE_RIGHT,
};

class TankState : public State
{
protected:
	static TankState * __instance;
	StateTank stateTank;
	Tank *tank;
	Animation * anim;
public:
	TankState(Tank *tank);
	~TankState();

	static TankState * GetInstance(Tank *tank);

	//Lấy trạng thái
	StateTank GetState();
	//Set trạng thái
	void SetState(StateTank State);

	void state_bleeding();
	void state_top();
	void state_top_right();
	void state_right();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
