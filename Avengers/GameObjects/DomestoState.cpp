#include "DomestoState.h"
#include <math.h>

DomestoState * DomestoState::__instance = NULL;

DomestoState *DomestoState::GetInstance(Domesto *domesto)
{
	if (__instance == NULL)
		__instance = new DomestoState(domesto);
	return __instance;
}


DomestoState::DomestoState(Domesto *domesto)
{
	this->domesto = domesto;
	this->state_walking();
}

DomestoState::~DomestoState()
{
	delete anim;
}

//Lấy trạng thái
StateDomesto DomestoState::GetState()
{
	return this->stateDomesto;
}
//Set trạng thái
void DomestoState::SetState(StateDomesto state)
{
	this->stateDomesto = state;
}

void DomestoState::state_walking()
{
	this->SetState(DOMESTO_STATE_WALKING);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_WALKING];
}

void DomestoState::state_standing_shoot()
{
	this->SetState(DOMESTO_STATE_STANDING_SHOOT);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_STANDING_SHOOT];
}

void DomestoState::state_crouch_shoot()
{
	this->SetState(DOMESTO_STATE_CROUCH_SHOOT);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_CROUCH_SHOOT];
}

void DomestoState::state_dead()
{
	this->SetState(DOMESTO_STATE_DEAD);
	anim = domesto->GetAnimationsList()[DOMESTO_STATE_DEAD];
}

void DomestoState::Colision()
{

}

void DomestoState::Update(DWORD dt)
{

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

	default:
		break;
	}
}

void DomestoState::Render()
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

