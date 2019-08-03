#include "Bullet.h"

Bullet::Bullet(float x, float y, int direction, BulletType type)
{
	LoadResources();
	Initialize(x, y, direction, type);
}

void Bullet::Initialize(float x, float y, int direction, BulletType type)
{
	this->type = type;

	this->direction = direction;

	switch (type)
	{
	case BULLET_NORMAL:
	{
		width = 6;
		height = 6;
	}
		break;
	case BULLET_TANK:
	{
		width = 8;
		height = 8;
	}
		break;
	case BULLET_BOSS2:
	{
		width = 16;
		height = 11;
	}
		break;
	case ROCKET:
	{
		width = 15;
		height = 7;
	}
		break;
	case BULLET_NORMAL_BOSS1:
	{
		width = 8;
		height = 5;
	}
		break;
	case BULLET_SPECIAL_BOSS1:
	{
		width = 16;
		height = 16;
	}
		break;
	}

	this->x = x;
	this->y = y;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = this->width;
	collider.height = this->height;
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

void Bullet::BulletNormalUpdate(DWORD dt)
{
	if (direction == 1)
	{
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
	else
	{
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
}

void Bullet::BulletTankUpdate(DWORD dt)
{
	switch (direction)
	{
	case 1:		//Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 3:		//Bottom
		this->SetSpeedX(0);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 4:		//Bottom-Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 5:		//Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	case 7:		//Top
		this->SetSpeedX(0);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	case 8:		//Top-Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	}
}

void Bullet::BulletBoss2Update(DWORD dt)
{
}

void Bullet::RocketUpdate(DWORD dt)
{
	// 1:Left	2:B-L	3:Bottom	4:B-R	5:Right	6:T-R	7:Top	8:T-L
	switch (direction)
	{
	case 1:		//Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		break;
	case 3:		//Bottom
		break;
	case 4:		//Bottom-Right
		break;
	case 5:		//Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);

		if (timeCount > ROCKET_CHANGE_DIRECTION_TIME)
		{
			this->SetSpeedY(BULLET_NORMAL_SPEED);
		}

		break;
	case 7:		//Top
		break;
	case 8:		//Top-Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);

		if (timeCount > ROCKET_CHANGE_DIRECTION_TIME)
		{
			this->SetSpeedY(BULLET_NORMAL_SPEED);
		}
		break;
	}
}

void Bullet::BulletNormalBoss1Update(DWORD dt)
{
	/*if (direction == 1)
	{
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
	else
	{
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}*/

	switch (direction)
	{
	case 1:		//Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		break;
	case 3:		//Bottom
		break;
	case 4:		//Bottom-Right
		break;
	case 5:		//Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED * 0.5f);

		break;
	case 7:		//Top
		break;
	case 8:		//Top-Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED * 0.5f);
		break;
	}
}

void Bullet::BulletSpecialBoss1Update(DWORD dt)
{
	if (direction == 1)
	{
		this->setIsLeft(true);
		this->SetSpeedX(-ROCKET_SPEED);
		this->SetSpeedY(0);
	}
	else if (direction == 3)
	{
		this->SetSpeedX(0);
		this->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	}
	else
	{
		this->setIsLeft(false);
		this->SetSpeedX(ROCKET_SPEED);
		this->SetSpeedY(0);
	}
}

void Bullet::Update(DWORD dt)
{
	if (this->disable)
		return;

	this->timeCount += dt;

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	UpdateObjectCollider();

	switch (type)
	{
	case BulletType::BULLET_NORMAL:
		BulletNormalUpdate(dt);
		break;
	case BulletType::BULLET_TANK:
		BulletTankUpdate(dt);
		break;
	case BulletType::BULLET_BOSS2:
		break;
	case BulletType::ROCKET:
		RocketUpdate(dt);
		break;
	case BulletType::BULLET_NORMAL_BOSS1:
		BulletNormalBoss1Update(dt);
		break;
	case BulletType::BULLET_SPECIAL_BOSS1:
		BulletSpecialBoss1Update(dt);
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

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	spriteData.isLeft = this->IsLeft();
	spriteData.isFlipped = this->IsFlipped();

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

	case ROCKET:
	{
		switch (direction)
		{
		case 1:
		case 5:
			this->animations[ROCKET]->Render(spriteData);
			break;
		case 6:
		case 8:
			if (timeCount < ROCKET_CHANGE_DIRECTION_TIME)
				this->animations[ROCKET]->Render(spriteData);
			else
				this->animations[4]->Render(spriteData);
			break;
		}
		
	}
	break;

	case BULLET_NORMAL_BOSS1:
	{
		this->animations[5]->Render(spriteData);
	}
	break;

	case BULLET_SPECIAL_BOSS1:
	{
		if (direction == 3)
			this->animations[8]->Render(spriteData);
		else
			this->animations[7]->Render(spriteData);
	}
	break;
	}
}

Bullet::~Bullet()
{
}

