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
	
	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[99], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1,400);

	Sprite * sprite2 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[100], TEXTURE_TRANS_COLOR);
	sprite2->SetOffSetX(3);
	anim->AddFrame(sprite2, 400);
	
	animations.push_back(anim);

	// BAT_FLYING
	anim = new Animation(100);

	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[101], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);

	Sprite * sprite4 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[102], TEXTURE_TRANS_COLOR);
	sprite4->SetOffSetY(-7);
	anim->AddFrame(sprite4);
	
	animations.push_back(anim);

	// BAT_DEAD
	anim = new Animation(100);

	anim->AddFrame(sprite4);

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

	this->UpdateObjectCollider();

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
	((BatState*)state)->timeCount = 0;
	((BatState*)state)->state_dead();
}
