#include "TankState.h"
#include <math.h>

TankState * TankState::__instance = NULL;

TankState *TankState::GetInstance(Tank *tank)
{
	if (__instance == NULL)
		__instance = new TankState(tank);
	return __instance;
}


TankState::TankState(Tank *tank)
{
	this->tank = tank;
	this->state_top();
}

TankState::~TankState()
{
	delete anim;
}

//Lấy trạng thái
StateTank TankState::GetState()
{
	return this->stateTank;
}
//Set trạng thái
void TankState::SetState(StateTank state)
{
	this->stateTank = state;
}

void TankState::state_bleeding()
{
	this->SetState(TANK_STATE_BLEEDING);
	anim = tank->GetAnimationsList()[TANK_STATE_BLEEDING];
}

void TankState::state_top()
{
	this->SetState(TANK_STATE_TOP);
	anim = tank->GetAnimationsList()[TANK_STATE_TOP];
}

void TankState::state_top_right()
{
	this->SetState(TANK_STATE_TOP_RIGHT);
	anim = tank->GetAnimationsList()[TANK_STATE_TOP_RIGHT];
}

void TankState::state_right()
{
	this->SetState(TANK_STATE_RIGHT);
	anim = tank->GetAnimationsList()[TANK_STATE_RIGHT];
}

void TankState::Colision()
{

}

void TankState::Update(DWORD dt)
{

	//Update theo state
	switch (stateTank)
	{
	case TANK_STATE_BLEEDING:
		this->state_bleeding();
		break;

	case TANK_STATE_TOP:
		this->state_top();
		break;

	case TANK_STATE_TOP_RIGHT:
		this->state_top_right();
		break;

	case TANK_STATE_RIGHT:
		this->state_right();
		break;

	default:
		break;
	}
}

void TankState::Render()
{
	SpriteData spriteData;
	if (this->tank != NULL)
	{
		spriteData.width = TILES_WIDTH_PER_TILE;
		spriteData.height = TILES_HEIGHT_PER_TILE;
		spriteData.x = tank->GetPositionX();
		spriteData.y = tank->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = tank->IsLeft();
		spriteData.isFlipped = tank->IsFlipped();
	}

	anim->Render(spriteData);
}

