#include "SmallEnergy.h"
#include "../GameComponents/Grid.h"

SmallEnergy::SmallEnergy()
{
	LoadResources();

	Active = true;

	this->state = ITEM_APPEAR;

	width = SMALL_ENERGY_WIDTH;
	height = SMALL_ENERGY_HEIGHT;

	//Để test thôi
	x = 200;
	y = 200;
	//=========

	vy = -CAPTAIN_GRAVITY;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = SMALL_ENERGY_WIDTH;
	collider.height = SMALL_ENERGY_HEIGHT;
}

void SmallEnergy::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// APPEAR
	Animation * anim = new Animation(100);
	for (int i = 60; i < 61; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// ALMOST DISAPPEAR
	anim = new Animation(100);

	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[60], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[66], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);

	animations.push_back(anim);

}

void SmallEnergy::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		this->SetActive(true);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		vector<Tile *> tiles = Grid::GetInstance()->GetCollisionTiles();

		this->SetSpeedY(this->GetSpeedY() - CAPTAIN_GRAVITY);

		coEvents.clear();
		this->SetDt(dt);
		this->CalcPotentialCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveY = trunc(this->GetSpeedY()* dt);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;
			this->SetPositionY(this->GetPositionY() + moveY);
			if (ny != 0) this->SetSpeedY(0);
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		this->SetActive(false);
		this->SetSpeedX(0);
	}
}

void SmallEnergy::Render()
{
	int state = this->state;

	SpriteData spriteData;

	spriteData.width = SMALL_ENERGY_WIDTH;
	spriteData.height = SMALL_ENERGY_HEIGHT;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	switch (state)
	{
	case ITEM_APPEAR:
	{
		this->animations[ITEM_APPEAR]->Render(spriteData);
	}
	break;
	case ITEM_ALMOST_DISAPPEAR:
	{
		this->animations[ITEM_ALMOST_DISAPPEAR]->Render(spriteData);
	}
	break;
	}
}

SmallEnergy *  SmallEnergy::CreateSmallEnergy(int ItemID, float posx, float posy, float dt)
{
	SmallEnergy * smallEnergy = new SmallEnergy();
	smallEnergy->ID = ItemID;
	smallEnergy->Active = true;
	smallEnergy->x = posx;
	smallEnergy->y = posy;
	smallEnergy->SetItemType(ItemType::SMALL_ENERGY);

	smallEnergy->collider.x = posx;
	smallEnergy->collider.y = posy;
	smallEnergy->dt = dt;

	return smallEnergy;
}
SmallEnergy::~SmallEnergy()
{
}