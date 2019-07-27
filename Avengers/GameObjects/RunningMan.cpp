#include "RunningMan.h"

vector<Animation *> RunningMan::animations = vector<Animation *>();
RunningMan *RunningMan::__instance = NULL;


RunningMan::RunningMan()
{
	LoadResources();

	state = RunningManState::GetInstance(this);
	type = RunningManType::NORMAL;

	this->x = 250;
	this->y = 80;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

RunningMan *RunningMan::GetInstance()
{
	if (__instance == NULL)
		__instance = new RunningMan();
	return __instance;
}

void RunningMan::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// RUNNING_MAN_ANI_RUNNING
	Animation * anim = new Animation(100);
	for (int i = 0; i < 3; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_STANDING_SHOOT
	anim = new Animation(100);
	for (int i = 3; i < 4; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite,5000);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_CROUCH_SHOOT
	anim = new Animation(100);
	for (int i = 4; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_DEAD
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void RunningMan::Update(DWORD dt)
{
	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	state->Colision();
	state->Update(dt);
}
void RunningMan::Render()
{
	state->Render();
}