#include "Rocket.h"

Rocket::Rocket()
{
	LoadResources();

	width = 15;
	height = 7;

	this->state = FLYING_DIAGONAL;

	//Để test thôi
	x = 250;
	y = 200;
	//=========

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = 15;
	collider.height = 7;
}

void Rocket::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// Bay ngang
	Animation * anim = new Animation(100);

	Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[15], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[17], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	
	animations.push_back(anim);

	// Bay xéo lên
	anim = new Animation(100);

	Sprite * sprite2 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[16], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite2);

	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[18], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);

	animations.push_back(anim);
}

void Rocket::Update(DWORD dt)
{

}

void Rocket::Render()
{
	SpriteData spriteData;

	spriteData.width = 15;
	spriteData.height = 7;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	switch (state)
	{
	case FLYING_HORIZONTAL:
	{
		this->animations[FLYING_HORIZONTAL]->Render(spriteData);
	}
	break;

	case FLYING_DIAGONAL:
	{
		this->animations[FLYING_DIAGONAL]->Render(spriteData);
	}
	break;
	}
}

Rocket::~Rocket()
{
}