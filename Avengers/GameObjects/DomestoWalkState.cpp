#include "DomestoWalkState.h"
#include <math.h>

DomestoWalkState * DomestoWalkState::__instance = NULL;

DomestoWalkState *DomestoWalkState::GetInstance(Domesto *domesto)
{
	if (__instance == NULL)
		__instance = new DomestoWalkState(domesto);
	return __instance;
}


DomestoWalkState::DomestoWalkState(Domesto *domesto)
{
	this->domesto = domesto;
	switch (domesto->GetType())
	{
	case DemestoType::STAY_FIRE_STRAIGHT:
		this->state_standing_shoot();
		break;
	case DemestoType::WALK_FIRE_STAIGHT:
		this->state_walking();
		break;
	}
}

DomestoWalkState::~DomestoWalkState()
{
	delete anim;
}

//Lấy trạng thái
StateDomesto DomestoWalkState::GetState()
{
	return this->stateDomesto;
}
//Set trạng thái
void DomestoWalkState::SetState(StateDomesto state)
{
	if (this->stateDomesto != state)
		previousStateDomesto = this->stateDomesto;
	this->stateDomesto = state;
}

// Chuyển state khi timeCount qua mốc thời gian xác định
bool DomestoWalkState::ChangeStateOverTime(StateDomesto state, float timeOut)
{
	if (this->timeCount > timeOut)
	{		
		this->timeCount = 0;
		switch (state)
		{
		case DOMESTO_STATE_WALKING:
			this->state_walking();
			break;

		case DOMESTO_STATE_STANDING_SHOOT:
			this->state_standing_shoot();
			break;

		case DOMESTO_STATE_CROUCH_SHOOT:
			this->state_crouch_shoot();
			break;

		case DOMESTO_STATE_DEAD:
			this->state_dead();
			break;

		default:
			break;
		}
		return true;
	}
	return false;
}


void DomestoWalkState::state_walking()
{
	this->SetState(StateDomesto::DOMESTO_STATE_WALKING);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_WALKING];

	
	domesto->SetSpeedX(CAPTAIN_WALK_SPEED * (domesto->IsLeft() ? -1 : 1));

	if (!Captain::GetInstance()->IsShield() && ((domesto->IsLeft() && !Captain::GetInstance()->IsLeft() && domesto->GetPositionX() > Captain::GetInstance()->GetPositionX()) || (!domesto->IsLeft() && Captain::GetInstance()->IsLeft() && domesto->GetPositionX() < Captain::GetInstance()->GetPositionX())))
	{
		domesto->SetSpeedY(CAPTAIN_JUMP_SPEED_Y * 2);
		domesto->SetIsGrounded(false);
		this->state_jumping();
		return;
	}

	if (this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_STANDING_SHOOT,
								DOMESTO_TIME_OUT_WALK))
	{
		domesto->setIsLeft(!domesto->IsLeft());
	}
}

void DomestoWalkState::state_standing_shoot()
{
	this->SetState(StateDomesto::DOMESTO_STATE_STANDING_SHOOT);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_STANDING_SHOOT];

	domesto->SetSpeedX(0);

	if (previousStateDomesto == StateDomesto::DOMESTO_STATE_WALKING)
	{		
		this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_CROUCH_SHOOT,
			DOMESTO_TIME_OUT_STAND);	
	}
	else
	{
		this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_WALKING,
									DOMESTO_TIME_OUT_STAND);
	}
}

void DomestoWalkState::state_crouch_shoot()
{
	this->SetState(StateDomesto::DOMESTO_STATE_CROUCH_SHOOT);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_CROUCH_SHOOT];

	this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_STANDING_SHOOT,
								DOMESTO_TIME_OUT_CROUCH + DOMESTO_TIME_OUT_CROUCH_SHOOT);
}

void DomestoWalkState::state_dead()
{
	this->SetState(StateDomesto::DOMESTO_STATE_DEAD);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_DEAD];
}

void DomestoWalkState::state_jumping()
{
	this->SetState(DOMESTO_STATE_JUMPING);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_CROUCH_SHOOT];

	if (domesto->IsGrounded())
	{
		this->SetState(DOMESTO_STATE_STANDING_SHOOT);
		return;
	}
}

void DomestoWalkState::Colision()
{

}

void DomestoWalkState::Update(DWORD dt)
{
	timeCount += dt;
	//Update theo state
	switch (stateDomesto)
	{
	case DOMESTO_STATE_WALKING:
		this->state_walking();
		break;

	case DOMESTO_STATE_STANDING_SHOOT:
		this->state_standing_shoot();
		break;

	case DOMESTO_STATE_CROUCH_SHOOT:
		this->state_crouch_shoot();
		break;

	case DOMESTO_STATE_DEAD:
		this->state_dead();
		break;

	case DOMESTO_STATE_JUMPING:
		this->state_jumping();
		break;

	default:
		break;
	}
}

void DomestoWalkState::Render()
{
	SpriteData spriteData;
	if (this->domesto != NULL)
	{
		spriteData.width = ENEMIES_SPRITE_WIDTH;
		spriteData.height = ENEMIES_SPRITE_HEIGHT;
		spriteData.x = domesto->GetPositionX();
		spriteData.y = domesto->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = domesto->IsLeft();
		spriteData.isFlipped = domesto->IsFlipped();
	}

	anim->Render(spriteData);
}

