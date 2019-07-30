#include "Bullet.h"

Bullet::Bullet()
{
	LoadResources();

	this->type = BULLET_BOSS2;

	width = 8;
	height = 8;

	//Để test thôi
	x = 200;
	y = 200;
	//=========

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = 8;
	collider.height = 8;
}

void Bullet::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// BULLET_NORMAL
	Animation * anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BULLET_TANK
	anim = new Animation(100);
	for (int i = 97; i < 98; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	RECT* listSprite1 = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss2.txt");

	// BULLET_BOSS2
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);


	//-----------Đạn boss 1--------------------
	RECT* listSprite2 = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss1.txt");

	// SMALL_BULLET_HORIZONTAL_BOSS1 (đạn nhỏ bay ngang)
	anim = new Animation(100);
	for (int i = 23; i < 24; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// SMALL_BULLET_DIAGONAL_BOSS1 (đạn nhỏ bay xéo lên)
	anim = new Animation(100);
	for (int i = 22; i < 23; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG_BULLET_HORIZONTAL_BOSS1 (đạn lớn bay ngang)
	anim = new Animation(100);
	for (int i = 18; i < 19; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG_BULLET_DOWN_BOSS1 (đạn lớn bay xuống)
	anim = new Animation(100);
	for (int i = 20; i < 21; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------------------------------------
}

void Bullet::Update(DWORD dt)
{
	
}

void Bullet::Render()
{
	SpriteData spriteData;

	spriteData.width = 8;
	spriteData.height = 8;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	switch (type)
	{
	case BULLET_NORMAL:
	{
		this->animations[BULLET_NORMAL]->Render(spriteData);
	}
	break;

	case BULLET_TANK:
	{
		this->animations[BULLET_TANK]->Render(spriteData);
	}
	break;

	case BULLET_BOSS2:
	{
		this->animations[BULLET_BOSS2]->Render(spriteData);
	}
	break;
	}
}

Bullet::~Bullet()
{
}