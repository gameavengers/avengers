#include "Tank.h"

vector<Animation *> Tank::animations = vector<Animation *>();
Tank *Tank::__instance = NULL;


Tank::Tank()
{
	LoadResources();

	state = TankState::GetInstance(this);

	this->x = 230;
	this->y = 100;
	this->width = TILES_WIDTH_PER_TILE;
	this->height = TILES_HEIGHT_PER_TILE;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = TILES_WIDTH_PER_TILE;
	collider.height = TILES_HEIGHT_PER_TILE;
}

Tank *Tank::GetInstance()
{
	if (__instance == NULL)
		__instance = new Tank();
	return __instance;
}

void Tank::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// TANK_ANI_BLEEDING
	Animation * anim = new Animation(20);
	for (int i = 79; i < 87; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_TOP
	anim = new Animation(100);
	for (int i = 79; i < 80; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_TOP_RIGHT
	anim = new Animation(100);
	for (int i = 80; i < 81; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_RIGHT
	anim = new Animation(100);
	for (int i = 81; i < 82; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Tank::Update(DWORD dt)
{
	state->Colision();
	state->Update(dt);
}
void Tank::Render()
{
	state->Render();
}