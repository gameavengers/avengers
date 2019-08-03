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
}

TankState::~TankState()
{
	delete anim;
}

void TankState::state_bleeding()
{
	anim = tank->GetAnimationsList()[0];

	if (this->timeCount > 500)
	{
		this->timeCount = 0;
		srand((int)time(0));
		this->SetDirection(rand() % 8 + 1);
		return;
	}
}

void TankState::state_left()
{
	anim = tank->GetAnimationsList()[1];
}

void TankState::state_bottom_left()
{
	anim = tank->GetAnimationsList()[2];
}

void TankState::state_bottom()
{
	anim = tank->GetAnimationsList()[3];
}

void TankState::state_bottom_right()
{
	anim = tank->GetAnimationsList()[4];
}

void TankState::state_top()
{
	anim = tank->GetAnimationsList()[7];
}

void TankState::state_top_left()
{
	anim = tank->GetAnimationsList()[8];
}

void TankState::state_top_right()
{
	anim = tank->GetAnimationsList()[6];
}

void TankState::state_right()
{
	anim = tank->GetAnimationsList()[5];
}

void TankState::Colision()
{

}

void TankState::Update(DWORD dt)
{
	this->timeCount += dt;
	this->shootTimeCount += dt;

	//Update state theo direction
	switch (direction)
	{
	case 0:
		this->state_bleeding();
		break;

	case 1:
		this->state_left();
		break;

	case 2:
		this->state_bottom_left();
		break;

	case 3:
		this->state_bottom();
		break;

	case 4:
		this->state_bottom_right();
		break;

	case 5:
		this->state_right();
		break;

	case 6:
		this->state_top_right();
		break;

	case 7:
		this->state_top();
		break;

	case 8:
		this->state_top_left();
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
		//spriteData.isLeft = tank->IsLeft();
		//spriteData.isFlipped = tank->IsFlipped();
	}

	anim->Render(spriteData);
}

