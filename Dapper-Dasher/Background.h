#pragma once
#include <raylib.h>

//clasa pentru backgroundul jocului.

class Background : Entity
{
public:
	//background. Variabilele necesare pentru background(Textura,pozitiile pe axa x,y,daca vream sa se roteasca,si marimea acestuia)
	Texture2D img;
	Vector2 posB;
	Vector2 pos2B;
	float rotation;
	float scale;

	//Midground . Variabilele necesare pentru Midground(Textura,pozitiile pe axa x,y,daca vream sa se roteasca,si marimea acestuia)
	Texture2D imgMid;
	Vector2 posM;
	Vector2 posM2;	
	//Foreground. Variabilele necesare pentru foreground(Textura,pozitiile pe axa x,y,daca vream sa se roteasca,si marimea acestuia)
	Texture2D imgFore;
	Vector2 posF;
	Vector2 posF2;	

	Background(Texture2D i, Texture2D m, Texture2D f) : img(i), imgMid(m), imgFore(f)
	{
		//pozitiile pentru background
		posB = { 0,0 };
		pos2B = { 0,0 };
		//for all.
		rotation = 0;
		scale = 4.0f;

		//pozitiile pentru midground
		posM= { 0,0 };
		posM2 = { 0,0 };
		//pozitiile pentru foreground
		posF = { 0,0 };
		posF2 = { 0,0 };

	};

	// functiile pentru a desena backgroundul,foregroundul si midgroungdul
	void Draw_Background()
	{
		DrawTextureEx(img, posB, rotation, scale, WHITE);
		DrawTextureEx(img, pos2B, rotation, scale, WHITE);
	}

	void Draw_Midground()
	{
		DrawTextureEx(imgMid, posM, rotation, scale, WHITE);
		DrawTextureEx(imgMid, posM2, rotation, scale, WHITE);
	}

	void Draw_Foreground()
	{
		DrawTextureEx(imgFore, posF, rotation, scale, WHITE);
		DrawTextureEx(imgFore, posF2, rotation, scale, WHITE);
	}

	// metoda pentru animatia backgroundruilor.
	void Move(float deltaTime)
	{
		Move_Background(deltaTime, img.width, -20.0f, posB, pos2B, scale);
		Move_Background(deltaTime, imgMid.width, -40.0f, posM, posM2,scale);
		Move_Background(deltaTime, imgFore.width, -80.0f, posF, posF2,scale);
	}
};