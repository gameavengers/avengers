#include "RunningMan.h"

vector<Animation *> RunningMan::animations = vector<Animation *>();
RunningMan *RunningMan::__instance = NULL;


RunningMan::RunningMan()
{
	LoadResources();

	state = RunningManState::GetInstance(this);
	type = RunningManType::NORMAL;

	this->x = 250;
	this->y = 80;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

RunningMan *RunningMan::GetInstance()
{
	if (__instance == NULL)
		__instance = new RunningMan();
	return __instance;
}

void RunningMan::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// RUNNING_MAN_ANI_RUNNING
	Animation * anim = new Animation(100);
	for (int i = 0; i < 3; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_STANDING_SHOOT
	anim = new Animation(100);
	for (int i = 3; i < 4; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite,5000);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_CROUCH_SHOOT
	anim = new Animation(100);
	for (int i = 4; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_DEAD
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void RunningMan::Update(DWORD dt)
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
void RunningMan::Render()
{
	state->Render();
}