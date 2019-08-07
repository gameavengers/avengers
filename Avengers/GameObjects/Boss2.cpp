#include "Boss2.h"

vector<Animation *> Boss2::animations = vector<Animation *>();
Boss2 *Boss2::__instance = NULL;


Boss2::Boss2()
{
	//LoadResources();

	state = Boss2State::GetInstance(this);

	this->x = 50;
	this->y = 71;
	this->width = BOSS2_SPRITE_WIDTH;
	this->height = BOSS2_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = BOSS2_SPRITE_WIDTH;
	collider.height = BOSS2_SPRITE_HEIGHT;

	this->HP = 4;
}

Boss2 *Boss2::GetInstance()
{
	if (__instance == NULL)
		__instance = new Boss2();
	return __instance;
}

void Boss2::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss2.txt");

	// BOSS2_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_RUNNING
	anim = new Animation(100);
	for (int i = 0; i < 3; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_STANDING_PUNCH
	anim = new Animation(100);
	for (int i = 4; i < 5; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		sprite->SetOffSetX(8);
		anim->AddFrame(sprite, 500);
	}

	Sprite * sprite4 = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[6], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite4);

	animations.push_back(anim);

	// BOSS2_ANI_HOLD_BOX
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_THROW_BOX
	anim = new Animation(100);
	for (int i = 8; i < 9; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		sprite->SetOffSetX(8);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_BLEEDING
	anim = new Animation(100);

	Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[6], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[9], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	
	animations.push_back(anim);

	// BOSS2_ANI_LOSS_HEAD_IDLE
	anim = new Animation(100);
	for (int i = 15; i < 16; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_LOSS_HEAD_RUNNING
	anim = new Animation(100);
	for (int i = 16; i < 19; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BOSS2_ANI_DEAD
	anim = new Animation(50);
		
	Sprite * sprite2 = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[15], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite2);

	Sprite * sprite3 = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite[41], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);
	
	animations.push_back(anim);
}

void Boss2::Update(DWORD dt)
{
	if (this->disable)
		return;

	this->UpdateObjectCollider();
	
	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	state->Colision();
	state->Update(dt);
}
void Boss2::Render()
{
	if (this->disable)
		return;
	
	state->Render();
}

void Boss2::OnCollision()
{
	if (((Boss2State*)state)->GetState() == StateBoss2::BOSS2_STATE_BLEEDING
		|| ((Boss2State*)state)->GetState() == StateBoss2::BOSS2_STATE_DEAD)
		return;

	this->HP -= 1;
	((Boss2State*)state)->timeCount = 0;

	if (this->HP > 2)
	{
		((Boss2State*)state)->SetState(BOSS2_STATE_BLEEDING);
		return;
	}
	if (this->HP = 2)
	{
		((Boss2State*)state)->SetState(BOSS2_STATE_LOSS_HEAD_IDLE);
		return;
	}
	if (this->HP = 0)
	{
		((Boss2State*)state)->SetState(BOSS2_STATE_DEAD);
		return;
	}
}