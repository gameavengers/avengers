#pragma once
#include "Item.h"
class FivePoint : public Item
{
private:
	void LoadResources();

	int state;
public:
	FivePoint();
	~FivePoint();
	static FivePoint * CreateFivePoint(int ItemID, float posx, float posy, float dt);

	void Update(DWORD dt) override;
	void Render() override;
};


