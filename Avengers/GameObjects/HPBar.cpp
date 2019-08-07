#include "HPBar.h"

vector<Animation *> HPBar::animations = vector<Animation *>();
HPBar *HPBar::__instance = NULL;


HPBar::HPBar()
{
	this->x = Viewport::GetInstance()->GetPosX() + 32;
	this->y = Viewport::GetInstance()->GetPosY() - 16;
}

HPBar *HPBar::GetInstance()
{
	if (__instance == NULL)
		__instance = new HPBar();
	return __instance;
}

void HPBar::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	Animation * anim = new Animation(100);
	for (int i = 62; i < 63; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void HPBar::Update(DWORD dt)
{
	

	this->x = Viewport::GetInstance()->GetPosX() + 32;
	this->y = Viewport::GetInstance()->GetPosY() - 16;
}

void HPBar::Render()
{
	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	this->animations[0]->Render(spriteData);
}

