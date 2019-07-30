#pragma once
#include "../GameComponents/GameObject.h"

enum RocketState {
	FLYING_HORIZONTAL, //bay ngang
	FLYING_DIAGONAL, //bay x�o l�n
};

class Rocket : public GameObject
{
private:
	void LoadResources();

	vector<Animation *> animations;

	RocketState state;
public:
	Rocket();
	~Rocket();

	void Update(DWORD dt) override;
	void Render() override;
};


