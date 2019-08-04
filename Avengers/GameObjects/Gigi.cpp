#include "Gigi.h"

vector<Animation *> Gigi::animations = vector<Animation *>();
Gigi *Gigi::__instance = NULL;


Gigi::Gigi()
{
	LoadResources();

	state = GigiState::GetInstance(this);

	this->x = 250;
	this->y = 150;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

Gigi::Gigi(float x, float y)
{
	this->state = new GigiState(this);

	this->posx = x;
	this->posy = y;

	this->x = x;
	this->y = y;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

Gigi *Gigi::GetInstance()
{
	if (__instance == NULL)
		__instance = new Gigi();
	return __instance;
}

void Gigi::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	//FLY
	Animation * anim = new Animation(100);

	Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[22], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[30], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	
	animations.push_back(anim);

	//DEAD
	anim = new Animation(20);

	anim->AddFrame(sprite);

	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[104], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);

	animations.push_back(anim);
}

void Gigi::Update(DWORD dt)
{
	if (this->GetPositionX() > Captain::GetInstance()->GetPositionX())
		this->setIsLeft(true);
	else
		this->setIsLeft(false);

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	state->Colision();
	state->Update(dt);
}
void Gigi::Render()
{
	state->Render();
}

void Gigi::OnCollision()
{
	((GigiState*)state)->timeCount = 0;
	((GigiState*)state)->state_dead();
}
