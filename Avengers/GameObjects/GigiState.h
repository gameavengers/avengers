#pragma once
#include "../GameComponents/Constants.h"
#include "State.h"
#include "Gigi.h"

class Gigi;
enum StateGigi
{
	GIGI_STATE_FLYING, //Bay
};

class GigiState : public State
{
protected:
	static GigiState * __instance;
	StateGigi stateGigi;
	Gigi *gigi;
	Animation * anim;
public:
	GigiState(Gigi *gigi);
	~GigiState();

	static GigiState * GetInstance(Gigi *gigi);

	//Lấy trạng thái
	StateGigi GetState();
	//Set trạng thái
	void SetState(StateGigi State);

	void state_flying();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
