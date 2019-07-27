#include "Barrel.h"

Barrel::Barrel()
{
	LoadResources();

	width = 22;
	height = 14;

	//Để test thôi
	x = 200;
	y = 200;
	//=========

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = 22;
	collider.height = 14;
}

void Barrel::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss2.txt");

	// 
	Animation * anim = new Animation(100);
	for (int i = 10; i < 11; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Barrel::Update(DWORD dt)
{

}

void Barrel::Render()
{
	SpriteData spriteData;

	spriteData.width = 22;
	spriteData.height = 14;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	this->animations[0]->Render(spriteData);
}

Barrel::~Barrel()
{
}