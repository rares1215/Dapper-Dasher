#pragma once
#include "Scarfy.h"
#include "Nebula.h"


// Clasa pentru fereasta jocului.
class Window
{
public:
	// cream si initializam variabilele pentru fereasta.
	int width, heigth;
	const char* name;

	Window(int w, int h, const char* n) : width(w), heigth(h), name(n)
	{
		//Verificam daca sunt valori valabile.
		if (width <= 200 || heigth <= 200)
		{
			std::printf("Invalid size!\n");
			exit(1);
		}
	};

	// Initializam fereasta.
	void Init()
	{
		InitWindow(width, heigth, name);
		SetTargetFPS(60);
	}

	// distrugem fereasta.
	~Window()
	{
		CloseWindow();
	}
};


// o clasa pentru background ul jocului.

class Background
{
public:
	Texture2D background;
	Texture2D midground;
	Texture2D foreground;
	Vector2 pos1; // pozitia pentru primul background
	Vector2 pos2; // pozitia pentru al doilea background;
	Vector2 mid_pos1; 
	Vector2 mid_pos2; 
	Vector2 fore_pos1; 
	Vector2 fore_pos2; 
	float rotate;
	float scale;

	Background(Texture2D b, Texture2D m, Texture2D f) : background(b), midground(m), foreground(f)
	{
		pos1.x = 0.0f;
		pos1.y = 0.0f;
		rotate = 0.0f;
		scale = 4.0f;
		pos2 = { 0.0,0.0f };

		mid_pos1 = { 0.0,0.0 };
		mid_pos2 = { midground.width * scale, 0.0f };
		fore_pos1 = { 0.0,0.0 };
		fore_pos2 = { foreground.width * scale, 0.0f };
	};

	// functie pentru desenarea backgroundului.
	void DrawB();

	// functie pentru midground.
	void DrawM();

	//functie pentru foreground.
	void DrawF();

	//functie pentru miscarea backgroundului.
	void Move(float deltaTime);
};

void Background::DrawB()
{
	DrawTextureEx(background, pos1, rotate, scale, WHITE);
	DrawTextureEx(background, pos2, rotate, scale, WHITE);
}

void Background :: DrawM()
{
	DrawTextureEx(midground, mid_pos1, rotate, scale, WHITE);
	DrawTextureEx(midground, mid_pos2, rotate, scale, WHITE);
}

void Background::DrawF()
{
	DrawTextureEx(foreground, fore_pos1, rotate, scale, WHITE);
	DrawTextureEx(foreground, fore_pos2, rotate, scale, WHITE);
}

void Background::Move(float deltaTime)
{
	pos1.x -= 20 * deltaTime;
	mid_pos1.x -= 40 * deltaTime;
	fore_pos1.x -= 80 * deltaTime;

	pos2.x = pos1.x + background.width * scale;
	mid_pos2.x = mid_pos1.x + background.width * scale;
	fore_pos2.x = fore_pos1.x + background.width * scale;

	if (pos1.x <= -background.width * scale) pos1.x = 0;
	if (mid_pos1.x <= -midground.width * scale) mid_pos1.x = 0;
	if (fore_pos1.x <= -foreground.width * scale) fore_pos1.x = 0;
}