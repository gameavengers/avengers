#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain *Captain::__instance = NULL;

Captain::Captain()
{
	LoadResources();

	state = CaptainState::GetInstance(this);

	shield = new Shield();

	this->x = 300;
	this->y = 200;
	this->width = CAPTAIN_SPRITE_WIDTH;
	this->height = CAPTAIN_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = CAPTAIN_SPRITE_WIDTH;
	collider.height = CAPTAIN_SPRITE_HEIGHT;
}

Captain *Captain::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Captain();
	}
	return __instance;
}

void Captain::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// CAPTAIN_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_STADING_UP
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_WALK
	anim = new Animation(100);
	for (int i = 1; i < 5; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_JUMP
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_JUMP_ROLE
	anim = new Animation(50);
	for (int i = 8; i < 10; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH
	anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SWIM
	anim = new Animation(100);
	for (int i = 44; i < 46; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_THROW_SHIELD
	anim = new Animation(150);
	for (int i = 11; i < 13; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_PUNCH
	anim = new Animation(100);
	for (int i = 13; i < 15; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_KICK
	anim = new Animation(500);
	for (int i = 10; i < 11; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH_PUNCH
	anim = new Animation(80);
	for (int i = 15; i < 17; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH_SHIELD
	anim = new Animation(300);
	for (int i = 19; i < 20; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DASH
	anim = new Animation(300);
	for (int i = 18; i < 19; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_THROW_SHIELD_2
	anim = new Animation(300);
	for (int i = 11; i < 13; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_BLEEING
	anim = new Animation(300);
	for (int i = 33; i < 34; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DIEING
	anim = new Animation(300);
	for (int i = 34; i < 36; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DIVING
	anim = new Animation(200);
	for (int i = 41; i < 44; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SWING
	anim = new Animation(200);
	for (int i = 27; i < 30; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Captain::Reset()
{
	this->SetPositionX(200);
	this->SetPositionY(200);
	Viewport::GetInstance()->Reset();
}

void Captain::Update(DWORD dt)
{
	// Xử lý chuyển màn
	if (this->GetSpeedX() > 0 && this->GetPositionX() > TileMap2::GetInstance()->currentMap->size*16 - 50)
	{
		if (Game::GetInstance()->GetStage() < 4)
		{
			Game::GetInstance()->SetStage(Game::GetInstance()->GetStage() + 1);
			if (STAGE_BOSS_1 == Game::GetInstance()->GetStage())
			{
				/*this->SetPositionX(50);
				this->SetPositionY(100);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_1);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());*/
			}
			if (STAGE_2 == Game::GetInstance()->GetStage())
			{
				/*this->SetPositionX(280);
				this->SetPositionY(900);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_2);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());*/
			}
			if (STAGE_BOSS_2 == Game::GetInstance()->GetStage())
			{
				/*this->SetPositionX(50);
				this->SetPositionY(100);
				Viewport::GetInstance()->Reset();
				TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_2);
				Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());*/
			}
		}
		else this->SetSpeedX(0);
	}

	static int p = 0;
	if (p == 0)
	{
		Game::GetInstance()->SetStage(STAGE_BOSS_1);
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_1);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
		p++;
	}

	//Chuyển màn nhanh bằng phím
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F1))
	{
		Game::GetInstance()->SetStage(STAGE_1);
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_1);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F2))
	{
		Game::GetInstance()->SetStage(STAGE_BOSS_1);
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_1);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F3))
	{
		Game::GetInstance()->SetStage(STAGE_2);
		this->SetPositionX(280);
		this->SetPositionY(900);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_2);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F4))
	{
		Game::GetInstance()->SetStage(STAGE_BOSS_2);
		this->SetPositionX(50);
		this->SetPositionY(100);
		Viewport::GetInstance()->Reset();
		TileMap2::GetInstance()->SetCurrentMap(STAGE_BOSS_2);
		Grid2::GetInstance()->InitializeMapGrid(TileMap2::GetInstance());
	}
	
	//Colision với state để riêng ra
	vector<ColliedEvent*> coEvents;
	vector<ColliedEvent*> coEventsResult;

#pragma region	Collide with map
	vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

	coEvents.clear();
	this->SetDt(dt);
	this->UpdateObjectCollider();
	this->MapCollisions(tiles, coEvents);

	if (coEvents.size() == 0)
	{
		float moveX = trunc(this->GetSpeedX()* dt);
		float moveY = trunc(this->GetSpeedY()* dt);
		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		Collision::GetInstance()->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				this->SetIsGrounded(true);
			}
		}

		if (coEventsResult[0]->collisionID == 2)
		{
			if (ny == 1)
			{
				this->SetIsGrounded(false);
				this->SetIsSwimming(true);
				this->SetPositionX(this->GetPositionX() - 1);
			}
		}

		if (coEventsResult[0]->collisionID == 3)
		{
			if (ny == 1)
			{
				this->SetIsSwing(true);
			}
		}
	}
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
	shield->Update(dt);
	state->Colision();
	state->Update(dt);
}
void Captain::Render()
{
	state->Render();
	shield->Render();
}