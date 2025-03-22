#pragma once

#include "Entity.h"

// clasa pentru crearea obstacolelor.
class Nebula : Entity
{
public:
	// cream si intializam variabilele pentru obstacol spriteul, chenarul in care se afla spriteul, si pozitia spriteului.
	Texture2D& sprite;
	Rectangle rec;
	Vector2 pos;

	// variabila pentru velocitatea nebulei(viteza cu care se misa inspre scarfy);
	float velocity;

	// cream variabile pentru a masura timpul pana la urmatoarea animatie si pentru a contoriza cand ajungem la acel timp pentru a schimba imaginea.
	float updateTime;
	float runningTime;
	int frame; // indexul pentru a ne arata la ce frame suntem.

	Nebula(Texture2D& s, int window_width, int window_heigth) : sprite(s), velocity(-300.0f)
	{
		rec = { 0,0,static_cast <float>(sprite.width / 8),static_cast <float>(sprite.height / 8) };
		pos.x = window_width + rec.width;
		pos.y = window_heigth - rec.height;

		updateTime = 1.0f / 12.0f;
		runningTime = 0;
		frame = 0;
	};

	// functie pentru desenarea obstacolului.
	void Draw(Color color);

	//functie pentru miscarea nebulei.
	void Move(float deltaTime, int window_width);

	//functie pentru animarea Nebulei
	void Animation(float deltaTime);

	//functie pentru distrugerea din memorie.
	~Nebula()
	{
	}
};

void Nebula::Draw(Color color)
{
	DrawTextureRec(sprite, rec, pos, color);
}

void Nebula::Move(float deltaTime, int window_width)
{
	pos.x += velocity * deltaTime;
	//if (pos.x + rec.width < 0) pos.x = window_width + rec.width;
}

void Nebula::Animation(float deltaTime)
{
	Animate(updateTime, runningTime, deltaTime, 7, frame, rec);
}

