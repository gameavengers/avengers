#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "Domesto.h"

class Domesto;
enum StateDomesto
{
	DOMESTO_STATE_WALKING,//Đi
	DOMESTO_STATE_STANDING_SHOOT,//Đứng bắn
	DOMESTO_STATE_CROUCH_SHOOT,//Ngồi bắn
	DOMESTO_STATE_DEAD,//Chết
};

class DomestoState : public State
{
protected:
	static DomestoState * __instance;
	StateDomesto stateDomesto;
	Domesto *domesto;
	Animation * anim;
public:
	DomestoState(Domesto *domesto);
	~DomestoState();

	static DomestoState * GetInstance(Domesto *domesto);

	//Lấy trạng thái
	StateDomesto GetState();
	//Set trạng thái
	void SetState(StateDomesto State);

	void state_walking();
	void state_standing_shoot();
	void state_crouch_shoot();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
