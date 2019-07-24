#include "RedBoxState.h"
#include <math.h>

RedBoxState * RedBoxState::__instance = NULL;

RedBoxState *RedBoxState::GetInstance(RedBox *redbox)
{
	if (__instance == NULL)
		__instance = new RedBoxState(redbox);
	return __instance;
}


RedBoxState::RedBoxState(RedBox *redbox)
{
	this->redbox = redbox;
	this->state_close();
}

RedBoxState::~RedBoxState()
{
	delete anim;
}

//Lấy trạng thái
StateRedBox RedBoxState::GetState()
{
	return this->stateRedBox;
}
//Set trạng thái
void RedBoxState::SetState(StateRedBox state)
{
	this->stateRedBox = state;
}

void RedBoxState::state_close()
{
	this->SetState(RED_BOX_STATE_CLOSE);
	anim = redbox->GetAnimationsList()[RED_BOX_STATE_CLOSE];
}

void RedBoxState::state_open()
{
	this->SetState(RED_BOX_STATE_OPEN);
	anim = redbox->GetAnimationsList()[RED_BOX_STATE_OPEN];
}

void RedBoxState::Colision()
{

}

void RedBoxState::Update(DWORD dt)
{

	//Update theo state
	switch (stateRedBox)
	{
	case RED_BOX_STATE_CLOSE:
		this->state_close();
		break;

	case RED_BOX_STATE_OPEN:
		this->state_open();
		break;

	default:
		break;
	}
}

void RedBoxState::Render()
{
	SpriteData spriteData;
	if (this->redbox != NULL)
	{
		spriteData.width = TILES_WIDTH_PER_TILE;
		spriteData.height = TILES_HEIGHT_PER_TILE;
		spriteData.x = redbox->GetPositionX();
		spriteData.y = redbox->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = redbox->IsLeft();
		spriteData.isFlipped = redbox->IsFlipped();
	}

	anim->Render(spriteData);
}

