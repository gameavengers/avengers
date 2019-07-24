#pragma once
#include "Item.h"
class BigEnergy : public Item
{
private:
	void LoadResources();

	int state;
public:
	BigEnergy();
	~BigEnergy();
	static BigEnergy * CreateBigEnergy(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


