#pragma once
#include "../GameComponents/GameObject.h"

class Barrel : public GameObject
{
private:
	void LoadResources();

	vector<Animation *> animations;

public:
	Barrel();
	~Barrel();

	void Update(DWORD dt) override;
	void Render() override;
};


