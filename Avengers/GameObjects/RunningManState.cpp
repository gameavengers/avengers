#include "RunningManState.h"
#include <math.h>

RunningManState * RunningManState::__instance = NULL;

RunningManState *RunningManState::GetInstance(RunningMan *runningMan)
{
	if (__instance == NULL)
		__instance = new RunningManState(runningMan);
	return __instance;
}


RunningManState::RunningManState(RunningMan *runningMan)
{
	this->runningMan = runningMan;
	this->state_running();
}

RunningManState::~RunningManState()
{
	delete anim;
}

//Lấy trạng thái
StateRunningMan RunningManState::GetState()
{
	return this->stateRunningMan;
}
//Set trạng thái
void RunningManState::SetState(StateRunningMan state)
{
	this->stateRunningMan = state;
}

void RunningManState::state_running()
{
	this->SetState(RUNNING_MAN_STATE_RUNNING);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_RUNNING];
}

void RunningManState::state_standing_shoot()
{
	this->SetState(RUNNING_MAN_STATE_STANDING_SHOOT);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_STANDING_SHOOT];
}

void RunningManState::state_crouch_shoot()
{
	this->SetState(RUNNING_MAN_STATE_CROUCH_SHOOT);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_CROUCH_SHOOT];
}

void RunningManState::state_dead()
{
	this->SetState(RUNNING_MAN_STATE_DEAD);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_DEAD];
}

void RunningManState::Colision()
{

}

void RunningManState::Update(DWORD dt)
{
	
	//Update theo state
	switch (stateRunningMan)
	{
	case RUNNING_MAN_STATE_RUNNING:
		this->state_running();
		break;

	case RUNNING_MAN_STATE_STANDING_SHOOT:
		this->state_standing_shoot();
		break;

	case RUNNING_MAN_STATE_CROUCH_SHOOT:
		this->state_crouch_shoot();
		break;

	case RUNNING_MAN_STATE_DEAD:
		this->state_dead();
		break;

	default:
		break;
	}
}

void RunningManState::Render()
{
	SpriteData spriteData;
	if (this->runningMan != NULL)
	{
		spriteData.width = ENEMIES_SPRITE_WIDTH;
		spriteData.height = ENEMIES_SPRITE_HEIGHT;
		spriteData.x = runningMan->GetPositionX();
		spriteData.y = runningMan->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = runningMan->IsLeft();
		spriteData.isFlipped = runningMan->IsFlipped();
	}

	anim->Render(spriteData);
}

