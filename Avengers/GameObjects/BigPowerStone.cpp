#include "BigPowerStone.h"
#include "../GameComponents/Grid2.h"

BigPowerStone::BigPowerStone()
{
	LoadResources();

	Active = true;

	this->state = ITEM_APPEAR;

	width = BIG_POWER_STONE_WIDTH;
	height = BIG_POWER_STONE_HEIGHT;

	//Để test thôi
	x = 200;
	y = 200;
	//=========

	vy = -CAPTAIN_GRAVITY;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = BIG_POWER_STONE_WIDTH;
	collider.height = BIG_POWER_STONE_HEIGHT;
}

void BigPowerStone::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// APPEAR
	Animation * anim = new Animation(100);
	for (int i = 57; i < 59; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// ALMOST DISAPPEAR
	anim = new Animation(50);

	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[58], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[66], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);

	animations.push_back(anim);

}

void BigPowerStone::Update(DWORD dt)
{
	// Cap nhat Delta Time
	this->dt = dt;

	this->timeCount += dt;

	if (this->timeCount > 4000)
		this->state = ITEM_ALMOST_DISAPPEAR;
	if (this->timeCount > 6000)
		this->SetActive(false);
	
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		//this->SetActive(true);
		vector<ColliedEvent*> coEvents;
		vector<ColliedEvent*> coEventsResult;

		vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

		this->SetSpeedY(this->GetSpeedY() - CAPTAIN_GRAVITY);

		coEvents.clear();
		this->SetDt(dt);
		this->UpdateObjectCollider();
		this->MapCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveY = trunc(this->GetSpeedY()* dt);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			Collision::GetInstance()->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;
			this->SetPositionY(this->GetPositionY() + moveY);
			if (ny != 0) this->SetSpeedY(0);
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	/*else
	{
		this->SetActive(false);
		this->SetSpeedX(0);
	}*/
}

void BigPowerStone::Render()
{
	if (!this->IsActive())
		return;
	
	int state = this->state;

	SpriteData spriteData;

	spriteData.width = BIG_POWER_STONE_WIDTH;
	spriteData.height = BIG_POWER_STONE_HEIGHT;
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

BigPowerStone *  BigPowerStone::CreateBigPowerStone(int ItemID, float posx, float posy, float dt)
{
	BigPowerStone * bigPowerStone = new BigPowerStone();
	bigPowerStone->ID = ItemID;
	bigPowerStone->Active = true;
	bigPowerStone->x = posx;
	bigPowerStone->y = posy;
	bigPowerStone->SetItemType(ItemType::BIG_POWER_STONE);

	bigPowerStone->collider.x = posx;
	bigPowerStone->collider.y = posy;
	bigPowerStone->dt = dt;

	return bigPowerStone;
}
BigPowerStone::~BigPowerStone()
{
}