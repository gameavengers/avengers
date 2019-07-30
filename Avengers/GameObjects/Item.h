#pragma once
#include "../GameComponents/GameObject.h"

enum ItemType {
	FIVE_POINT,
	BIG_POWER_STONE,
	SMALL_POWER_STONE,
	BIG_ENERGY,
	SMALL_ENERGY,
	KEY_CRYSTAL
};

class GameObject;
class Item : public GameObject
{
private:
	static int ItemID;
protected:
	int ID;
	vector<Animation *> animations;
	bool Active;

	ItemType Type;

	float timeCount;
public:
	Item();
	~Item();

	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }

	static int GetItemId() { return ItemID++; }
	int GetID() { return this->ID; }

	void SetItemType(ItemType type) { this->Type = type; };
	ItemType GetItemType() { return this->Type; }

	virtual void Update(DWORD dt);
	virtual void Render();
};

