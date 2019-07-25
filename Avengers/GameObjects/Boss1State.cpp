#include "Boss1State.h"
#include <math.h>

Boss1State * Boss1State::__instance = NULL;

Boss1State *Boss1State::GetInstance(Boss1 *boss1)
{
	if (__instance == NULL)
		__instance = new Boss1State(boss1);
	return __instance;
}


Boss1State::Boss1State(Boss1 *boss1)
{
	this->boss1 = boss1;
	this->state_running();
}

Boss1State::~Boss1State()
{
	delete anim;
}

//Lấy trạng thái
StateBoss1 Boss1State::GetState()
{
	return this->stateBoss1;
}
//Set trạng thái
void Boss1State::SetState(StateBoss1 state)
{
	this->stateBoss1 = state;
}

void Boss1State::state_idle()
{
	this->SetState(BOSS1_STATE_IDLE);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_IDLE];
}

void Boss1State::state_running()
{
	this->SetState(BOSS1_STATE_RUNNING);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_RUNNING];
}

void Boss1State::state_bleeding()
{
	this->SetState(BOSS1_STATE_BLEEDING);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_BLEEDING];
}

void Boss1State::state_dead()
{
	this->SetState(BOSS1_STATE_DEAD);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_DEAD];
}

void Boss1State::state_standing_shoot_1()
{
	this->SetState(BOSS1_STATE_STANDING_SHOOT_1);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_STANDING_SHOOT_1];
}

void Boss1State::state_standing_shoot_2()
{
	this->SetState(BOSS1_STATE_STANDING_SHOOT_2);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_STANDING_SHOOT_2];
}

void Boss1State::state_flying()
{
	this->SetState(BOSS1_STATE_FLYING);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_FLYING];
}

void Boss1State::state_flying_shoot()
{
	this->SetState(BOSS1_STATE_FLYING_SHOOT);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_FLYING_SHOOT];
}

void Boss1State::Colision()
{

}

void Boss1State::Update(DWORD dt)
{

	//Update theo state
	switch (stateBoss1)
	{
	case BOSS1_STATE_IDLE:
		this->state_idle();
		break;

	case BOSS1_STATE_RUNNING:
		this->state_running();
		break;

	case BOSS1_STATE_BLEEDING:
		this->state_bleeding();
		break;

	case BOSS1_STATE_DEAD:
		this->state_dead();
		break;

	case BOSS1_STATE_STANDING_SHOOT_1:
		this->state_standing_shoot_1();
		break;

	case BOSS1_STATE_STANDING_SHOOT_2:
		this->state_standing_shoot_2();
		break;

	case BOSS1_STATE_FLYING:
		this->state_flying();
		break;

	case BOSS1_STATE_FLYING_SHOOT:
		this->state_flying_shoot();
		break;

	default:
		break;
	}
}

void Boss1State::Render()
{
	SpriteData spriteData;
	if (this->boss1 != NULL)
	{
		spriteData.width = BOSS1_SPRITE_WIDTH;
		spriteData.height = BOSS1_SPRITE_HEIGHT;
		spriteData.x = boss1->GetPositionX();
		spriteData.y = boss1->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = boss1->IsLeft();
		spriteData.isFlipped = boss1->IsFlipped();
	}

	anim->Render(spriteData);
}

