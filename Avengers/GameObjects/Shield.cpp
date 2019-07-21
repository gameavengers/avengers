#include "Shield.h"
#include "../GameComponents/Grid.h"

Shield * Shield::__instance = NULL;

Shield * Shield::GetInstance()
{
	if (__instance == NULL)
		__instance = new Shield();
	return __instance;
}

Shield::Shield()
{
	LoadResources();

	width = SHIELD_WIDTH;
	height = SHIELD_HEIGHT;

	vx = SHIELD_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = SHIELD_WIDTH;
	collider.height = SHIELD_HEIGHT;

	maxDistance = SCREEN_WIDTH / 2;
}

void Shield::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");
	Animation * anim = new Animation(100);
	//SHIELD_SIDE
	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[46], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_CENTER
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[47], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_UP
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[48], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_DOWN
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[49], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_HIDE
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[66], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);
}

void Shield::Update(DWORD dt)
{
	this->SetSpeedY(0);
	Captain* captain = Captain::GetInstance();
	CaptainState* capstate = CaptainState::GetInstance(captain);
	if (!captain->IsShield())
	{
		this->state = SHIELD_UP;
		ShieldFlying();
	}
	else
	{
		if (capstate->GetState() == STATE_STANDING || capstate->GetState() == STATE_WALKING)
		{
			this->state = SHIELD_SIDE;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() - 2);
			else
				this->SetPositionX(captain->GetPositionX() + 12);
			this->SetPositionY(captain->GetPositionY() - 8);
		}
		if (capstate->GetState() == STATE_JUMPING)
		{
			this->state = SHIELD_CENTER;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX());
			else
				this->SetPositionX(captain->GetPositionX() + 8);
			this->SetPositionY(captain->GetPositionY() - 4);
		}
		if (capstate->GetState() == STATE_CROUCH)
		{
			this->state = SHIELD_SIDE;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() - 2);
			else
				this->SetPositionX(captain->GetPositionX() + 12);
			this->SetPositionY(captain->GetPositionY() - 26);
		}
		if (capstate->GetState() == STATE_STANDING_UP)
		{
			this->state = SHIELD_UP;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX());
			else
				this->SetPositionX(captain->GetPositionX() + 8);
			this->SetPositionY(captain->GetPositionY() + 2);
		}
		if (capstate->GetState() == STATE_JUMPING_KICK)
		{
			this->state = SHIELD_SIDE;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() + 28);
			else
				this->SetPositionX(captain->GetPositionX() - 18);
			this->SetPositionY(captain->GetPositionY() - 5);
		}
		if (capstate->GetState() == STATE_CROUCH_PUNCH)
		{
			this->state = SHIELD_CENTER;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() + 6);
			else
				this->SetPositionX(captain->GetPositionX() + 3);
			this->SetPositionY(captain->GetPositionY() - 25);
		}
		if (capstate->GetState() == STATE_CROUCH_SHIELD)
		{
			this->state = SHIELD_DOWN;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() + 6);
			else
				this->SetPositionX(captain->GetPositionX() + 3);
			this->SetPositionY(captain->GetPositionY() - 25);
		}
		if (capstate->GetState() == STATE_DASH)
		{
			this->state = SHIELD_SIDE;
			this->SetSpeedX(0);
			if (captain->IsLeft())
				this->SetPositionX(captain->GetPositionX() - 2);
			else
				this->SetPositionX(captain->GetPositionX() + 11);
			this->SetPositionY(captain->GetPositionY() - 22);
		}
		if (capstate->GetState() == STATE_SWIMMING || capstate->GetState() == STATE_JUMPING_ROLE || capstate->GetState() == STATE_DIVING)
		{
			this->state = SHIELD_HIDE;
		}
	}

	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt*(isLeft == true ? -1 : 1)));
	this->SetPositionY((float)(this->GetPositionY() + this->GetSpeedY()* dt));
}

void Shield::ShieldFlying()
{
	Captain* captain = Captain::GetInstance();
	if (isStartThrow)
	{
		this->isCaptainLeft = captain->IsLeft();
		if (captain->IsLeft())
			this->SetPositionX(captain->GetPositionX() + 20);
		else
			this->SetPositionX(captain->GetPositionX() - 14);
		this->distance = captain->GetPositionX() + maxDistance * (isCaptainLeft ? -1 : 1);
		this->SetSpeedX(SHIELD_SPEED * 1 * (isCaptainLeft ? -1 : 1));
		this->SetPositionY(captain->GetPositionY() - 6);

		this->isStartThrow = false;
		captain->SetIsShield(false);
	}
	else
	{

		int cpos = captain->GetPositionY() - 20;
		if ((isCaptainLeft ? (this->GetPositionX() < this->distance) : (this->GetPositionX() >= this->distance) && isReturn))
		{
			this->SetSpeedX(SHIELD_SPEED * -1 * (isCaptainLeft ? -1 : 1));
			isReturn = false;
		}
		if (abs(this->GetPositionY() - cpos) >= 1)
		{
			if (this->GetPositionY() > cpos)
			{
				float temp = this->GetPositionY() - 1.25;
				this->SetPositionY(temp);
			}
			else
			{
				float temp = this->GetPositionY() + 1.25;
				this->SetPositionY(temp);
			}
		}
		if (!isReturn && abs(this->GetPositionX() - captain->GetPositionX()) <= 30)
		{

			isStartThrow = true;
			isReturn = true;
			captain->SetIsShield(true);

		}
	}
}

void Shield::Render()
{
	int state = this->state;
	Captain * captain = Captain::GetInstance();
	CaptainState * capstate = CaptainState::GetInstance(captain);
	if (capstate->GetState() == STATE_JUMPING_KICK)
	{
		SpriteData spriteData;

		spriteData.width = SHIELD_WIDTH;
		spriteData.height = SHIELD_HEIGHT;
		spriteData.x = this->GetPositionX();
		spriteData.y = this->GetPositionY();

		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = !captain->IsLeft();
		spriteData.isFlipped = !captain->IsFlipped();

		this->animations[SHIELD_SIDE]->Render(spriteData);
	}
	else
	{
		SpriteData spriteData;

		spriteData.width = SHIELD_WIDTH;
		spriteData.height = SHIELD_HEIGHT;
		spriteData.x = this->GetPositionX();
		spriteData.y = this->GetPositionY();

		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = captain->IsLeft();
		spriteData.isFlipped = captain->IsFlipped();

		switch (state)
		{
		case SHIELD_SIDE:
		{
			this->animations[SHIELD_SIDE]->Render(spriteData);
		}
		break;
		case SHIELD_CENTER:
		{
			this->animations[SHIELD_CENTER]->Render(spriteData);
		}
		break;
		case SHIELD_UP:
		{
			this->animations[SHIELD_UP]->Render(spriteData);
		}
		break;
		case SHIELD_DOWN:
		{
			this->animations[SHIELD_DOWN]->Render(spriteData);
		}
		case SHIELD_HIDE:
		{
			this->animations[SHIELD_HIDE]->Render(spriteData);
		}
		break;
		}
	}
}

Shield::~Shield()
{
}
