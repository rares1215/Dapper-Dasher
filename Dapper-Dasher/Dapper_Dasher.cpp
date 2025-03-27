#include "Game.h"


///////////////////////////////////////////////////////////// functia main //////////////////////////////////////////////////


int main()
{
	Window window(1024, 600, "Dapper Dasher");
	window.Init_Window();

	// textura pentru scarfy
	Texture2D scarfy_sheets = LoadTexture("textures/scarfy.png");
	Scarfy scarfy(scarfy_sheets);

	// Cream personajul
	scarfy.initScarfy(window.width, window.heigth);

	// textura pentru nebula
	Texture2D nebula_sheets = LoadTexture("textures/12_nebula_spritesheet.png");
	const int nebulaNum = 3;

	//Cream obstacolele.
	Nebulas* nebula[nebulaNum];

	for (int i = 0; i < nebulaNum; i++)
	{
		 nebula[i] = new Nebulas(nebula_sheets);
		 nebula[i]->initNebulas(window.width + 500*i, window.heigth);
	}

	// textura pentru background midground si foreground.
	Texture2D background_sheet = LoadTexture("textures/far-buildings.png");
	Texture2D midground_sheet = LoadTexture("textures/back-buildings.png");
	Texture2D foreground_sheet = LoadTexture("textures/foreground.png");

	//Cream backgroundul,midgroundul si foregroundul
	Background background(background_sheet,midground_sheet,foreground_sheet);

	// Verificam daca jocul s a incheiat sau nu(verficiam daca personajul a intrat in coliziune cu unul din obstacole,stocam asta intr o variabila).
	bool isGameOver = false;

	// loop ul pentru a tine fereastra deschisa.
	while (!WindowShouldClose())
	{
		// stocam intr o variabila durata de timp dintre frame uri.
		const float dT = GetFrameTime();

		// variabila pentru determinarea terminarii jocului.
		float finish_line = nebula[nebulaNum - 1]->pos.x;
		BeginDrawing();
		ClearBackground(WHITE);

		//logica pentru background.
		background.Draw_Background();
		background.Draw_Midground();
		background.Draw_Foreground();
		background.Move(dT);

		// cream 2 rec uri pentru personaj si obstacole pentru a putea verifica coliziunea dintre ele.
		for (int i = 0; i < nebulaNum; i++)
		{
			// cream o spatiere pentru a putea micsora dimensiunile obstacolelor pentru a face coliziunea mai precisa.
			float pad = 30.0f;
			// recul pentru obstacole.
			Rectangle nebulaRec;
			nebulaRec.x = nebula[i]->pos.x + pad;
			nebulaRec.y = nebula[i]->pos.y + pad;
			nebulaRec.width = nebula[i]->rec.width - 2 * pad;
			nebulaRec.height = nebula[i]->rec.height - 2 * pad;

			// recul pentru personaj
			Rectangle scarfyRec;
			scarfyRec.x = scarfy.pos.x;
			scarfyRec.y = scarfy.pos.y;
			scarfyRec.width = scarfy.rec.width;
			scarfyRec.height = scarfy.rec.height;

			// verficiam daca obiecteze s au ciocnit, daca este adevarat atunci variabila devine true.
			if(Game::checkColision(scarfyRec, nebulaRec)) isGameOver = true;
		}

		// verificam daca jocul s a terminat ( cu victore, adica am depasit toate obstacolele fara a le lovii).
		if (finish_line > scarfy.pos.x -500)
		{
			// verificam daca jocul s a terminat(cu infrangere, adica daca am lovit unul din obstacole)
			if (isGameOver)
			{
				// daca este true( personajul si unul din obstacole s au ciocnit) atunci afisam pe ecran textul "Game Over".
				DrawText("Game Over!", window.width / 2 - 100, window.heigth / 2, 30, PINK);
				// Posibilitatea de a reseta jocul si a incerca din nou sa treci de toate obstacolele apasand tasta r. 
				if (IsKeyPressed(KEY_R))
				{
					// initializam personajul la pozitia initiala si cu valoriile initiale.
					scarfy.initScarfy(window.width, window.heigth);

					// initializam obstacolul la pozitia initiala si cu valoriile initiale.
					for (int i = 0; i < nebulaNum; i++)
					{
						nebula[i]->initNebulas(window.width + 500 * i, window.heigth);
						nebula[i]->velocity = -450.0f;
					}
					// setam starea jocului la fals din nou pentru a putea relua jocul.
					isGameOver = false;
				}
			}
			// Daca nu am lovit nici un obstacol atunci jocul continua normal.
			else
			{
				//Logica pentru personaj
				scarfy.Draw();
				scarfy.Animate(dT);
				scarfy.Jump(window.heigth, dT);

				//logica pentru obstacol.
				for (int i = 0; i < nebulaNum; i++)
				{
					nebula[i]->Draw();
					nebula[i]->Move(dT);
					nebula[i]->Animate(dT);
				}
			}
		}
		// daca jocul s a terminat cu victorie dupa ce am depasit obstacolele afisam textul de mai jos si oprim jocul.
		else
		{
			DrawText("Congrats! You Win!", window.width / 2 - 200, window.heigth / 2, 30, GREEN);
			DrawText("Press enter proceed to the next level", window.width / 2 - 200, window.heigth / 2 + 50, 30, GREEN);
			if (IsKeyPressed(KEY_ENTER))
			{
				// initializam personajul la pozitia initiala si cu valoriile initiale.
				scarfy.initScarfy(window.width, window.heigth);

				// initializam obstacolul la pozitia initiala si cu valoriile initiale.
				for (int i = 0; i < nebulaNum; i++)
				{
					nebula[i]->initNebulas(window.width + 500 * i, window.heigth);
					nebula[i]->velocity -= 50.0f;
				}
			}
		}

		EndDrawing();
	}


	// codul pentru curatarea memoriei (stergem texturile si memoria alocata inainte de terminarea programului).
	for (int i = 0; i < nebulaNum; i++)
	{
		delete nebula[i];
	}
	UnloadTexture(scarfy_sheets);
	UnloadTexture(nebula_sheets);
	UnloadTexture(background_sheet);
	UnloadTexture(midground_sheet);
	UnloadTexture(foreground_sheet);
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