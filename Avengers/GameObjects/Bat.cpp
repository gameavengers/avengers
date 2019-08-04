#include "Bat.h"

vector<Animation *> Bat::animations = vector<Animation *>();
Bat *Bat::__instance = NULL;


Bat::Bat()
{
	LoadResources();

	state = BatState::GetInstance(this);

	this->x = 250;
	this->y = 150;
	this->width = 24;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = width;
	collider.height = height;
}

Bat::Bat(float x, float y)
{
	LoadResources();

	this->state = new BatState(this);

	this->x = x;
	this->y = y;
	this->width = 24;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 24;
	collider.height = 16;
}

Bat *Bat::GetInstance()
{
	if (__instance == NULL)
		__instance = new Bat();
	return __instance;
}

void Bat::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// BAT_IDLE
	Animation * anim = new Animation(100);
	for (int i = 98; i < 99; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BAT_GOING_TO_FLY
	anim = new Animation(100);
	for (int i = 99; i < 101; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite,400);
	}
	animations.push_back(anim);

	// BAT_FLYING
	anim = new Animation(100);
	for (int i = 101; i < 103; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Bat::Update(DWORD dt)
{
	if (this->disable)
		return;

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	state->Colision();
	state->Update(dt);
}
void Bat::Render()
{
	if (this->disable)
		return;

	state->Render();
}

void Bat::OnCollision()
{
	
}
