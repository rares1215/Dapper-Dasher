#include <iostream>
#include "raylib.h"
#include "Window.h"


///////////////////////////////////////////////////////////// functia int main //////////////////////////////////////////////////


int main()
{
	Window window(1024, 600, "Dapper Dasher");
	window.Init();

	// cream personajul.
	Texture2D scarf_img = LoadTexture("textures/scarfy.png");
	Scarfy scarfy(scarf_img,window.width,window.heigth);

	//cream obstacole.
	Texture2D nebula_img = LoadTexture("textures/12_nebula_spritesheet.png");
	const int nebulasNum = 4;
	Nebula* nebulas[nebulasNum];

	for (int i = 0; i < nebulasNum; i++)
	{
		nebulas[i] = new Nebula(nebula_img, window.width + i*400, window.heigth);
	}
	float finish_line = nebulas[nebulasNum - 1]->pos.x;

	// cream backgroundul.
	Texture2D background_img = LoadTexture("textures/far-buildings.png");
	Texture2D midground_img = LoadTexture("textures/back-buildings.png");
	Texture2D foreground_img = LoadTexture("textures/foreground.png");
	Background background(background_img,midground_img,foreground_img);

	bool collision = false;

	// cream loop ul pentru a mentine fereasta deschisa.
	while (!WindowShouldClose())
	{
		// cream variabila pentru a stoca cat timp trece de la un frame la altul pentru a putea obtine miscarile si animatile independete fata de frame rate.
		const float dT = GetFrameTime(); // dT= delta Time.

		BeginDrawing();
		ClearBackground(WHITE);

		// logica pentru backgroundul jocului.
		background.DrawB();
		background.DrawM();
		background.DrawF();
		background.Move(dT);

		for (int i = 0; i < nebulasNum; i++)
		{
			float pad = 20.0f;
			Rectangle nebRec{
				nebulas[i]->pos.x + pad,
				nebulas[i]->pos.y + pad,
				nebulas[i]->rec.width - 2 * pad,
				nebulas[i]->rec.height - 2 * pad
			};

			Rectangle scarfyRec{
				scarfy.pos.x,
				scarfy.pos.y,
				scarfy.rec.width - 2 * pad,
				scarfy.rec.height - 2 * pad
			};

			if (CheckCollisionRecs(scarfyRec, nebRec)) collision = true;
		}

		if (collision)
		{
			DrawText("Game Over!", window.width/2 - 30, window.heigth/2 - 10,30,WHITE);
		}
		else
		{
			// logica lui scarfy(metodele si logica din codul pentru scarfy)
			scarfy.Draw();
			scarfy.Jump(window.heigth, dT);
			scarfy.Animation(dT);
			// logica obstacolelor(metodele si logica din codul pentru nebula).

			for (int i = 0; i < nebulasNum; i++)
			{
				nebulas[i]->Draw(WHITE);
				nebulas[i]->Move(dT, window.width);
				nebulas[i]->Animation(dT);
			}

			finish_line += nebulas[0]->velocity * dT;

			float finish_line = nebulas[nebulasNum - 1]->pos.x;
		}
		EndDrawing();
	}

	//codul pentru a  curata memoria dupa ce inchidem fereastra.
	for (int i = 0; i < nebulasNum; i++)
	{
		delete nebulas[i];
	}
	UnloadTexture(nebula_img);
	UnloadTexture(background_img);
	UnloadTexture(midground_img);
	UnloadTexture(foreground_img);

	return 0;
}












































/////////////////////////////////// logica din spatele animatiei.///////////////////////////////////////////////////////////////////

// update_time = 6.0/12.0 running_time +=deltaTime // update time ne arata la ce interval de timp vrem sa mutam on pe urmatoarea pozitie.
// Running time ne ajuta sa contorizam timpul pentru a afla cand sa mutam in functie de update time.
// 0.5 >= 0.1;0.5 >=0.2;..........0.5>=-0.5 cand update time este egal cu running time, mutam pe urmatoarea pozitie si resetam running time inapoi la 0.
// on         // on ne arata la ce pozitie suntem (adica la ce sprite ne aflam) 
// 0 1 2 3 4 5 // reprezentam pozitiile spriteurilor din sprite sheets(adica 0 este primul sprite,1 este al doilea etc.)
// daca running time creste cu 0.1 secunde per iteratie atunci inseamna ca trebuie sa asteptam 5 iteratii pana cand vom putea muta on pe urmatoarea pozitie.
//