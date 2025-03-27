#pragma once
#include "Window.h"
#include "Scarfy.h"
#include "Nebulas.h"
#include "Background.h"

// clasa pentru metodele jocului.
class Game
{
public:
	static bool checkColision(Rectangle rec, Rectangle obs)
	{
		return (rec.x <= obs.x + obs.width)
			&& (rec.x + rec.width >= obs.x)
			&& (rec.y + rec.height >= obs.y)
			&& (rec.y <= obs.y + obs.height);
	}

	static void resetGame(Scarfy& s, Nebulas& n,int window_width,int window_heigth,int num)
	{
		s.initScarfy(window_width, window_heigth);
	}
};