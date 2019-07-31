#include "Bullet.h"

Bullet::Bullet(float x, float y, int direction, BulletType type)
{
	LoadResources();
	Initialize(x, y, direction, type);
}

void Bullet::Initialize(float x, float y, int direction, BulletType type)
{
	//this->type = BULLET_BOSS2;
	this->type = type;

	this->direction = direction;

	width = 8;
	height = 8;

	//Để test thôi
	this->x = x;
	this->y = y;
	//=========

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = 8;
	collider.height = 8;
	this->disable = false;
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

	//-----------Rocket------------------------
	// Bay ngang
	anim = new Animation(100);
	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[15], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	Sprite * sprite2 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[17], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite2);
	animations.push_back(anim);

	// Bay xéo lên
	anim = new Animation(100);
	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[16], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);
	Sprite * sprite4 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[18], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite4);
	animations.push_back(anim);
	//-----------------------------------------
}

void Bullet::BulletNormalUpdate(DWORD dt)
{
	if (direction == 1)
	{
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
	}
	else
	{
		this->SetSpeedX(BULLET_NORMAL_SPEED);
	}
}

void Bullet::BulletTankUpdate(DWORD dt)
{
}

void Bullet::BulletBoss2Update(DWORD dt)
{
}

void Bullet::Update(DWORD dt)
{
	if (disable)
		return;

	timeCount += dt;

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	switch (type)
	{
	case BulletType::BULLET_NORMAL:
		BulletNormalUpdate(dt);
		break;
	case BulletType::BULLET_TANK:
		break;
	case BulletType::BULLET_BOSS2:
		break;
	}

	if (timeCount > BULLET_TIME_LIFE)
		Disable();
}

void Bullet::Render()
{
	if (this->disable)
		return;

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

