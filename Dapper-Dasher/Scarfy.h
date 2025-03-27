#pragma once
#include "Entity.h"

// clasa pentru personaj.
class Scarfy : Entity
{
public:
	Texture2D sprite;
	Rectangle rec;
	Vector2 pos;

	float updateTime;
	float runningTime;
	int frame;

	float velocity=0;
	float jumpVelocity=0;
	float gravity=0;
	bool isInAir = true;

	Scarfy(Texture2D s) : sprite(s) 
	{
		rec = { 0,0,0,0 };
		pos = { 0,0 };

		updateTime = 0;
		runningTime = 0;
		frame = 0;
	};

	void initScarfy(int window_width, int window_heigth)
	{
		jumpVelocity = -700.f;
		gravity = 1500.f;
		isInAir = false;

		updateTime = 1.3f / 12.0f;
		rec = { 0,0,static_cast <float>(sprite.width / 6),static_cast <float>(sprite.height) };
		pos = { static_cast<float>(window_width / 2) - rec.width / 2, static_cast<float>(window_heigth) - rec.height };
	}

	void Draw()
	{
		DrawTextureRec(sprite, rec, pos, WHITE);
	}

	void Jump(int window_heigth,float deltaTime)
	{
		isInAir = pos.y < window_heigth - rec.height;
		if (!isInAir) velocity = 0;
		else velocity += gravity * deltaTime;
		if (IsKeyPressed(KEY_SPACE) && !isInAir) velocity = jumpVelocity;
		pos.y += velocity * deltaTime;
	}

	void Animate(float deltaTime)
	{
		if(!isInAir)
		Animation(updateTime, runningTime, rec, frame, 5, deltaTime);
	}
};