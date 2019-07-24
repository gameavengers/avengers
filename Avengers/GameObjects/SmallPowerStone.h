#pragma once
#include "Item.h"
class SmallPowerStone : public Item
{
private:
	void LoadResources();

	int state;
public:
	SmallPowerStone();
	~SmallPowerStone();
	static SmallPowerStone * CreateSmallPowerStone(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


