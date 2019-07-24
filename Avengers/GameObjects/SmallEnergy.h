#pragma once
#include "Item.h"
class SmallEnergy : public Item
{
private:
	void LoadResources();

	int state;
public:
	SmallEnergy();
	~SmallEnergy();
	static SmallEnergy * CreateSmallEnergy(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


