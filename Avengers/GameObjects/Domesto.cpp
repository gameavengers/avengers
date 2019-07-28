#include "Domesto.h"

vector<Animation *> Domesto::animations = vector<Animation *>();
Domesto *Domesto::__instance = NULL;

Domesto::Domesto()
{
	LoadResources();

	type = DemestoType::WALK_FIRE_STAIGHT;
	
	if (type == DemestoType::STAY_FIRE_STRAIGHT)
	{
		state = DomestoStayState::GetInstance(this);
	}
	else
	{
		state = DomestoWalkState::GetInstance(this);
	}
	//state = DomestoState::GetInstance(this);
	

	this->x = 280;
	this->y = 85;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

Domesto *Domesto::GetInstance()
{
	if (__instance == NULL)
		__instance = new Domesto();
	return __instance;
}

void Domesto::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// DOMESTO_ANI_WALK
	Animation * anim = new Animation(100);
	for (int i = 10; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_STANDING_SHOOT
	anim = new Animation(100);
	for (int i = 12; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_CROUCH_SHOOT
	anim = new Animation(100);
	for (int i = 13; i < 14; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_DEAD
	anim = new Animation(100);
	for (int i = 14; i < 15; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Domesto::Update(DWORD dt)
{
	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	state->Colision();
	state->Update(dt);
}
void Domesto::Render()
{
	state->Render();
}