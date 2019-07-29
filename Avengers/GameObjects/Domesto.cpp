#include "Domesto.h"

vector<Animation *> Domesto::animations = vector<Animation *>();
Domesto *Domesto::__instance = NULL;

Domesto::Domesto()
{
	LoadResources();

	type = DemestoType::WALK_FIRE_STAIGHT;
	
	if (type == DemestoType::STAY_FIRE_STRAIGHT)
	{
		state = DomestoStayState::GetInstance(this);
	}
	else
	{
		state = DomestoWalkState::GetInstance(this);
	}
	//state = DomestoState::GetInstance(this);
	

	this->x = 280;
	this->y = 85;
	this->width = 24;
	this->height = 46;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 24;
	collider.height = 46;
}

Domesto *Domesto::GetInstance()
{
	if (__instance == NULL)
		__instance = new Domesto();
	return __instance;
}

void Domesto::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// DOMESTO_ANI_WALK
	Animation * anim = new Animation(100);
	for (int i = 10; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_STANDING_SHOOT
	anim = new Animation(100);
	for (int i = 12; i < 13; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_CROUCH_SHOOT
	anim = new Animation(100);
	for (int i = 13; i < 14; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// DOMESTO_ANI_DEAD
	anim = new Animation(100);
	for (int i = 14; i < 15; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Domesto::Update(DWORD dt)
{
	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);


	// Collide with brick
	vector<ColliedEvent*> coEvents;
	vector<ColliedEvent*> coEventsResult;

	vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

	this->SetSpeedY(this->GetSpeedY() - CAPTAIN_GRAVITY);

	coEvents.clear();
	this->SetDt(dt);
	this->UpdateObjectCollider();
	this->MapCollisions(tiles, coEvents);

	if (coEvents.size() != 0)
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

	state->Colision();
	state->Update(dt);
}
void Domesto::Render()
{
	state->Render();
}