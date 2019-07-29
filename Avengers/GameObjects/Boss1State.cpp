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
	this->state_standing_shoot_1();
	this->behaviorBoss1 = Fly;
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

#pragma region  State

void Boss1State::state_idle()
{
	this->SetState(BOSS1_STATE_IDLE);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_IDLE];
	boss1->SetSpeedX(0);
}

void Boss1State::state_running()
{
	this->SetState(BOSS1_STATE_RUNNING);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_RUNNING];
	boss1->SetSpeedX(CAPTAIN_WALK_SPEED * (boss1->IsLeft() ? -1 : 1));
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
	boss1->SetSpeedX(0);
}

void Boss1State::state_standing_shoot_1()
{
	this->SetState(BOSS1_STATE_STANDING_SHOOT_1);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_STANDING_SHOOT_1];
	boss1->SetSpeedX(0);
}

void Boss1State::state_standing_shoot_2()
{
	this->SetState(BOSS1_STATE_STANDING_SHOOT_2);
	anim = boss1->GetAnimationsList()[BOSS1_STATE_STANDING_SHOOT_2];
	boss1->SetSpeedX(0);
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

#pragma endregion

void Boss1State::Behavior_Shoot()
{
	switch (behaviorState)
	{
	case 0:
		this->state_standing_shoot_1();
		this->NextStateIn(BOSS1_TIME_STANDING_SHOOT_1);
		break;
	case 1:
		behaviorState = 0;
		behaviorBoss1 = BehaviorBoss1::Fly;
		break;
	default:
		break;
	}
}

void Boss1State::Behavior_ComboShoot()
{	
	switch (behaviorState)
	{
	case 0:
		this->state_running();	
		this->NextStateIn(BOSS1_TIME_RUN);
		break;
	case 1:
		this->state_standing_shoot_2();
		this->NextStateIn(BOSS1_TIME_STANDING_SHOOT_2);
		break;
	case 2:
		this->state_standing_shoot_2();
		this->NextStateIn(BOSS1_TIME_STANDING_SHOOT_2);
		break;
	case 3:
		this->state_standing_shoot_2();
		this->NextStateIn(BOSS1_TIME_STANDING_SHOOT_2);
		break;
	default:
		behaviorState = 0;
		behaviorBoss1 = BehaviorBoss1::Shoot;
		break;
	}
}

void Boss1State::Behavior_FlyAndShoot()
{
	// Behavior Flow
	// 0->	1->	|->	2->	3->	End
	//			|->	4->	|->	3->	End
	//					|-> 1->	3->	End
	switch (behaviorState)
	{
	case 0:
		this->state_flying();
		boss1->SetSpeedX(0);
		boss1->SetSpeedY(BOSS1_FLY_SPEED);
		this->NextStateIn(BOSS1_TIME_FLY_UP_N_DOWN);
		break;
	case 1:
		this->state_flying();
		boss1->SetSpeedX(CAPTAIN_WALK_SPEED * (boss1->IsLeft() ? -1 : 1));
		boss1->SetSpeedY(0);

		if (boss1->GetPositionX() == Captain::GetInstance()->GetPositionX())
		{
			behaviorState = 4;
		}

		this->NextStateIn(BOSS1_TIME_FLY);
		//behaviorBoss1 = BehaviorBoss1::ComboShoot;
		break;
	case 2:
		this->state_flying();
		boss1->SetSpeedX(0);
		boss1->SetSpeedY(-BOSS1_FLY_SPEED);
		this->NextStateIn(BOSS1_TIME_FLY_UP_N_DOWN);
		break;
	case 3:
		boss1->SetSpeedX(0);
		boss1->SetSpeedY(0);
		behaviorState = 0;
		break;
	case 4:
		this->state_flying_shoot();

		boss1->SetSpeedX(CAPTAIN_WALK_SPEED * (boss1->IsLeft() ? -1 : 1));
		boss1->SetSpeedY(0);

		if (anim->IsDone())
		{
			behaviorState = 1;
		}
		
		this->SetStateIn(2, BOSS1_TIME_FLY);
		break;
	}
}

void Boss1State::Behavior_Fly()
{
	float walkSpeed = CAPTAIN_WALK_SPEED * (boss1->IsLeft() ? -1 : 1);
	float acceleration = (timeCount / BOSS1_TIME_FLY_UP_N_DOWN) * (BOSS1_FLY_SPEED / 2);
	float acceleration2 = (timeCount / BOSS1_TIME_FLY_UP_N_DOWN);
	switch (behaviorState)
	{
	case 0:
		this->state_flying();
		boss1->SetSpeedX(walkSpeed * acceleration2 *2);
		boss1->SetSpeedY(BOSS1_FLY_SPEED - acceleration);
		this->NextStateIn(BOSS1_TIME_FLY_UP_N_DOWN);
		break;
	case 1:
		this->state_flying();
		boss1->SetSpeedX(walkSpeed);
		boss1->SetSpeedY(0);
		this->NextStateIn(500);
		break;
	case 2:
		this->state_flying();
		boss1->SetSpeedX(walkSpeed * acceleration2);
		boss1->SetSpeedY(-BOSS1_FLY_SPEED + acceleration);
		this->NextStateIn(BOSS1_TIME_FLY_UP_N_DOWN);
		break;
	case 3:
		boss1->SetSpeedX(0);
		boss1->SetSpeedY(0);
		behaviorState = 0;
		break;
	}
}

void Boss1State::RandomNextState()
{
}

bool Boss1State::NextStateIn(float time)
{
	if (timeCount > time)
	{
		timeCount = 0;
		behaviorState++;
		return true;
	}
	return false;
}

bool Boss1State::SetStateIn(int behaviorState, float time)
{
	if (timeCount > time)
	{
		timeCount = 0;
		this->behaviorState = behaviorState;
		return true;
	}
	return false;
}

void Boss1State::Colision()
{

}

void Boss1State::Update(DWORD dt)
{
	timeCount += dt;

	switch (this->behaviorBoss1)
	{
	case Shoot:
		this->Behavior_Shoot();
		break;
	case ComboShoot:
		this->Behavior_ComboShoot();
		break;
	case FlyNShoot:
		this->Behavior_FlyAndShoot();
		break;
	case Fly:
		this->Behavior_Fly();
		break;
	}

	//Update theo state
	/*switch (stateBoss1)
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
	}*/
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

