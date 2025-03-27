#pragma once
#include "Entity.h"

// clasa pentru obstacole.

class Nebulas : Entity
{
public:
	Texture2D sprite;
	Rectangle rec;
	Vector2 pos;
	float velocity = 0;
	float updateTime = 0;
	float runningTime = 0;
	int frame = 0;

	Nebulas(Texture2D s) : sprite(s) 
	{
		rec = { 0,0,0,0 };
		pos = { 0,0 };
	};

	void initNebulas(int window_width, int window_heigth)
	{
		velocity = -450.f;

		updateTime = 1.0f / 12.0f;

		rec = { 0,0,static_cast <float>(sprite.width / 8),static_cast<float>(sprite.height / 8) };
		pos = { static_cast<float>(window_width) ,window_heigth - rec.height};
	}

	void Draw()
	{
		DrawTextureRec(sprite, rec, pos, WHITE);
	}

	void Move(float deltaTime)
	{
		pos.x += velocity * deltaTime;
	}

	void Animate(float deltaTime)
	{
		Animation(updateTime, runningTime, rec, frame, 7, deltaTime);
	}
};