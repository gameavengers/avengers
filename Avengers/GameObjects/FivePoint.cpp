#include "FivePoint.h"
#include "../GameComponents/Grid.h"

FivePoint::FivePoint()
{
	LoadResources();

	Active = true;

	this->state = ITEM_APPEAR;

	width = FIVE_POINT_ITEM_WIDTH;
	height = FIVE_POINT_ITEM_HEIGHT;

	//Để test thôi
	x = 200;
	y = 200;
	//=========

	vy = -CAPTAIN_GRAVITY;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = FIVE_POINT_ITEM_WIDTH;
	collider.height = FIVE_POINT_ITEM_HEIGHT;
}

void FivePoint::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// APPEAR
	Animation * anim = new Animation(100);
	for (int i = 59; i < 60; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// ALMOST DISAPPEAR
	anim = new Animation(100);

	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[59], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[66], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	
	animations.push_back(anim);

}

void FivePoint::Update(DWORD dt)
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

void FivePoint::Render()
{
	int state = this->state;
	
	SpriteData spriteData;

	spriteData.width = FIVE_POINT_ITEM_WIDTH;
	spriteData.height = FIVE_POINT_ITEM_HEIGHT;
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

FivePoint *  FivePoint::CreateFivePoint(int ItemID, float posx, float posy, float dt)
{
	FivePoint * fivePoint = new FivePoint();
	fivePoint->ID = ItemID;
	fivePoint->Active = true;
	fivePoint->x = posx;
	fivePoint->y = posy;
	fivePoint->SetItemType(ItemType::FIVE_POINT);

	fivePoint->collider.x = posx;
	fivePoint->collider.y = posy;
	fivePoint->dt = dt;

	return fivePoint;
}
FivePoint::~FivePoint()
{
}