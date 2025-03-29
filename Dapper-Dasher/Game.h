#pragma once
// am creat un header separat in care sa includem tot restul codului pentru a include doar acest header in fuctia main.
#include "Window.h"
#include "Scarfy.h"
#include "Nebulas.h"
#include "Background.h"

// clasa pentru metodele jocului.
class Game
{
public:
	static int level;
	//  metoda prin care verficiam daca obiectele s au ciocnit
	static bool checkColision(Rectangle rec, Rectangle obs)
	{
		return (rec.x <= obs.x + obs.width)
			&& (rec.x + rec.width >= obs.x)
			&& (rec.y + rec.height >= obs.y)
			&& (rec.y <= obs.y + obs.height);
	}
};

int Game::level = 1;