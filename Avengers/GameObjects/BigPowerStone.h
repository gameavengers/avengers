#pragma once
#include "Item.h"
class BigPowerStone : public Item
{
private:
	void LoadResources();

	int state;
public:
	BigPowerStone();
	~BigPowerStone();
	static BigPowerStone * CreateBigPowerStone(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


