#pragma once
#include "Entity.h"

//clasa pentru crearea personajului.
class Scarfy : Entity
{
public:
	// cream si intializam variabilele pentru personaj. spriteul, chenarul in care se afla spriteul, si pozitia spriteului.
	Texture2D sprite;
	Rectangle rec;
	Vector2 pos;

	// cream variabilele pentru velocitate si gravitatea lui scarfy pentru  a l face sa sara.(in pixel/s)
	float velocity;
	float jumpVelocity;
	float gravity;
	bool isInAir; // verificam daca scarfy este in aer sau nu
	// cream variabile pentru a masura timpul pana la urmatoarea animatie si pentru a contoriza cand ajungem la acel timp pentru a schimba imaginea.
	float updateTime;
	float runningTime;
	int frame;// sa aflam in ce frame suntem mai exact(este un index).

	Scarfy(Texture2D s, int window_width, int window_heigth) : sprite(s), velocity(0), gravity(1500.0f), jumpVelocity(-600.0f)
	{
		rec = { 0,0,static_cast <float>(sprite.width / 6),static_cast <float>(sprite.height) }; // convertim din int in float.
		pos.x = window_width / 2 - rec.width / 2; // pozitia pe axa x.
		pos.y = window_heigth - sprite.height;

		isInAir = false;

		updateTime = 1.3f / 12.0f;
		runningTime = 0;
		frame = 0;
	};

	//functie pentru desenarea si afisarea lui Scarfy.
	void Draw();

	//Functie pentru a il face pe scarfy sa sara!.
	void Jump(int window_heigth, float deltaTime);

	//funcite pentru animatia lui Scarfy.
	void Animation(float deltaTime);

	//Distrugem texture ul din memorie.
	~Scarfy()
	{
		UnloadTexture(sprite);
	}
};

void Scarfy::Draw()
{
	DrawTextureRec(sprite, rec, pos, WHITE);
}

void Scarfy::Jump(int window_heigth, float deltaTime)
{
	isInAir = pos.y < window_heigth - rec.height;
	if (!isInAir) velocity = 0;
	else velocity += gravity * deltaTime;
	if (IsKeyPressed(KEY_SPACE) && !isInAir) velocity = jumpVelocity;
	pos.y += velocity * deltaTime;
}

void Scarfy::Animation(float deltaTime)
{
	if (!isInAir)
	{
		Animate(updateTime, runningTime, deltaTime, 5, frame, rec);
	}
}