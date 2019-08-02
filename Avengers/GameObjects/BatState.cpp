#include "BatState.h"
#include <math.h>

BatState * BatState::__instance = NULL;

BatState *BatState::GetInstance(Bat *bat)
{
	if (__instance == NULL)
		__instance = new BatState(bat);
	return __instance;
}


BatState::BatState(Bat *bat)
{
	this->bat = bat;

	this->state_flying();

}

BatState::~BatState()
{
	delete anim;
}

//Lấy trạng thái
StateBat BatState::GetState()
{
	return this->stateBat;
}
//Set trạng thái
void BatState::SetState(StateBat state)
{
	this->stateBat = state;
}

void BatState::state_idle()
{
	this->SetState(BAT_STATE_IDLE);
	anim = bat->GetAnimationsList()[BAT_STATE_IDLE];
}

void BatState::state_going_to_fly()
{
	this->SetState(BAT_STATE_GOING_TO_FLY);
	anim = bat->GetAnimationsList()[BAT_STATE_GOING_TO_FLY];
}
void BatState::state_flying()
{
	this->SetState(BAT_STATE_FLYING);
	anim = bat->GetAnimationsList()[BAT_STATE_FLYING];
}

void BatState::Colision()
{

}

void BatState::Update(DWORD dt)
{
	// Cap nhat Delta Time
	this->dt = dt;

	this->timeCount += dt;
	
	//Update theo state
	switch (stateBat)
	{
	case BAT_STATE_IDLE:
		this->state_idle();
		break;

	case BAT_STATE_GOING_TO_FLY:
		this->state_going_to_fly();
		break;

	case BAT_STATE_FLYING:
		this->state_flying();
		break;

	default:
		break;
	}
}

void BatState::Render()
{
	SpriteData spriteData;
	if (this->bat != NULL)
	{
		spriteData.width = bat->GetWidth();
		spriteData.height = bat->GetHeight();;
		spriteData.x = bat->GetPositionX();
		spriteData.y = bat->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = bat->IsLeft();
		spriteData.isFlipped = bat->IsFlipped();
	}

	anim->Render(spriteData);
}

