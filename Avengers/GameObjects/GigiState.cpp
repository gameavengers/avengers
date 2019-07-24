#include "GigiState.h"
#include <math.h>

GigiState * GigiState::__instance = NULL;

GigiState *GigiState::GetInstance(Gigi *gigi)
{
	if (__instance == NULL)
		__instance = new GigiState(gigi);
	return __instance;
}


GigiState::GigiState(Gigi *gigi)
{
	this->gigi = gigi;
	this->state_flying();
}

GigiState::~GigiState()
{
	delete anim;
}

//Lấy trạng thái
StateGigi GigiState::GetState()
{
	return this->stateGigi;
}
//Set trạng thái
void GigiState::SetState(StateGigi state)
{
	this->stateGigi = state;
}

void GigiState::state_flying()
{
	this->SetState(GIGI_STATE_FLYING);
	anim = gigi->GetAnimationsList()[GIGI_STATE_FLYING];
}

void GigiState::Colision()
{

}

void GigiState::Update(DWORD dt)
{

	//Update theo state
	switch (stateGigi)
	{
	case GIGI_STATE_FLYING:
		this->state_flying();
		break;

	default:
		break;
	}
}

void GigiState::Render()
{
	SpriteData spriteData;
	if (this->gigi != NULL)
	{
		spriteData.width = ENEMIES_SPRITE_WIDTH;
		spriteData.height = ENEMIES_SPRITE_HEIGHT;
		spriteData.x = gigi->GetPositionX();
		spriteData.y = gigi->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = gigi->IsLeft();
		spriteData.isFlipped = gigi->IsFlipped();
	}

	anim->Render(spriteData);
}

