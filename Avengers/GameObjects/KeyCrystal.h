#pragma once
#include "Item.h"
class KeyCrystal : public Item
{
private:
	void LoadResources();

	int state;
public:
	KeyCrystal();
	~KeyCrystal();
	static KeyCrystal * CreateKeyCrystal(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


