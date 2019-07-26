#pragma once
struct ColliedEvent
{
	int collisionID;
	float time;
	float nx;
	float ny;
	ColliedEvent(int id, float t, float nx, float ny)
	{
		this->collisionID = id;
		this->time = t;
		this->nx = nx;
		this->ny = ny;
	}
};