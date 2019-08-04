﻿#include "BatState.h"
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

	this->state_idle();
	flyStage = 0;
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

	float distanceX = abs(Captain::GetInstance()->GetPositionX() - bat->GetPositionX());
	float distanceY = abs(Captain::GetInstance()->GetPositionY() - bat->GetPositionY());

	if (distanceX < 64 || distanceY < 64 && timeCount > 300)
	{
		timeCount = 0;
		this->state_going_to_fly();
	}
}

void BatState::state_going_to_fly()
{
	this->SetState(BAT_STATE_GOING_TO_FLY);
	anim = bat->GetAnimationsList()[BAT_STATE_GOING_TO_FLY];

	if (timeCount > 1200)
	{
		timeCount = 0;
		this->state_flying();
	}
}
void BatState::state_flying()
{
	this->SetState(BAT_STATE_FLYING);
	anim = bat->GetAnimationsList()[BAT_STATE_FLYING];

	switch (flyStage)
	{
	case 0:
		bat->SetSpeedX(0);
		bat->SetSpeedY(-0.1f);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 1:
		bat->SetSpeedX(-0.1f);
		bat->SetSpeedY(0);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 2:
		bat->SetSpeedX(0);
		bat->SetSpeedY(-0.1f);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 3:
		bat->SetSpeedX(0.1f);
		bat->SetSpeedY(0);
		if (timeCount >= 1000)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 4:
		bat->SetSpeedX(0);
		bat->SetSpeedY(-0.1f);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 5:
		bat->SetSpeedX(-0.1f);
		bat->SetSpeedY(0);
		if (timeCount >= 1000)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 6:
		bat->SetSpeedX(0);
		bat->SetSpeedY(0.1f);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 7:
		bat->SetSpeedX(0.1f);
		bat->SetSpeedY(0);
		if (timeCount >= 1000)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 8:
		bat->SetSpeedX(0);
		bat->SetSpeedY(0.1f);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 9:
		bat->SetSpeedX(-0.1f);
		bat->SetSpeedY(0);
		if (timeCount >= 500)
		{
			timeCount = 0;
			flyStage++;
		}
		break;
	case 10:
		bat->SetSpeedX(0);
		bat->SetSpeedY(0.1f);
		if (timeCount >= 500)
		{
			bat->SetSpeedX(0);
			bat->SetSpeedY(0);
			timeCount = 0;
			flyStage = 0;
			//this->state_back_to_idle();
			this->state_idle();
		}
		break;
	}
}

void BatState::state_dead()
{
	this->SetState(BAT_STATE_DEAD);
	anim = bat->GetAnimationsList()[BAT_STATE_DEAD];

	bat->SetSpeedX(0);
	bat->SetSpeedY(-GIGI_FLY_SPEED * 2);
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

	case BAT_STATE_DEAD:
		this->state_dead();
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

