#include "Boss2State.h"
#include <math.h>

Boss2State * Boss2State::__instance = NULL;

Boss2State *Boss2State::GetInstance(Boss2 *boss2)
{
	if (__instance == NULL)
		__instance = new Boss2State(boss2);
	return __instance;
}


Boss2State::Boss2State(Boss2 *boss2)
{
	this->boss2 = boss2;
	this->state_running();
}

Boss2State::~Boss2State()
{
	delete anim;
}

//Lấy trạng thái
StateBoss2 Boss2State::GetState()
{
	return this->stateBoss2;
}
//Set trạng thái
void Boss2State::SetState(StateBoss2 state)
{
	this->stateBoss2 = state;
}

void Boss2State::state_idle()
{
	this->SetState(BOSS2_STATE_IDLE);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_IDLE];
}

void Boss2State::state_running()
{
	this->SetState(BOSS2_STATE_RUNNING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_RUNNING];
}

void Boss2State::state_bleeding()
{
	this->SetState(BOSS2_STATE_BLEEDING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_BLEEDING];
}

void Boss2State::state_standing_punch()
{
	this->SetState(BOSS2_STATE_STANDING_PUNCH);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_STANDING_PUNCH];
}

void Boss2State::state_hold_barrel()
{
	this->SetState(BOSS2_STATE_HOLD_BARREL);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_HOLD_BARREL];
}

void Boss2State::state_throw_barrel()
{
	this->SetState(BOSS2_STATE_THROW_BARREL);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_THROW_BARREL];
}

void Boss2State::state_loss_head_idle()
{
	this->SetState(BOSS2_STATE_LOSS_HEAD_IDLE);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_LOSS_HEAD_IDLE];
}

void Boss2State::state_loss_head_running()
{
	this->SetState(BOSS2_STATE_LOSS_HEAD_RUNNING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_LOSS_HEAD_RUNNING];
}

void Boss2State::state_dead()
{
	this->SetState(BOSS2_STATE_DEAD);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_DEAD];
}

void Boss2State::Colision()
{

}

void Boss2State::Update(DWORD dt)
{

	//Update theo state
	switch (stateBoss2)
	{
	case BOSS2_STATE_IDLE:
		this->state_idle();
		break;

	case BOSS2_STATE_RUNNING:
		this->state_running();
		break;

	case BOSS2_STATE_BLEEDING:
		this->state_bleeding();
		break;

	case BOSS2_STATE_STANDING_PUNCH:
		this->state_standing_punch();
		break;

	case BOSS2_STATE_HOLD_BARREL:
		this->state_hold_barrel();
		break;

	case BOSS2_STATE_THROW_BARREL:
		this->state_throw_barrel();
		break;

	case BOSS2_STATE_LOSS_HEAD_IDLE:
		this->state_loss_head_idle();
		break;

	case BOSS2_STATE_LOSS_HEAD_RUNNING:
		this->state_loss_head_running();
		break;

	case BOSS2_STATE_DEAD:
		this->state_dead();
		break;

	default:
		break;
	}
}

void Boss2State::Render()
{
	SpriteData spriteData;
	if (this->boss2 != NULL)
	{
		spriteData.width = BOSS2_SPRITE_WIDTH;
		spriteData.height = BOSS2_SPRITE_HEIGHT;
		spriteData.x = boss2->GetPositionX();
		spriteData.y = boss2->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = boss2->IsLeft();
		spriteData.isFlipped = boss2->IsFlipped();
	}

	anim->Render(spriteData);
}

