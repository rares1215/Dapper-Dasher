#pragma once
#include <iostream>
#include "raylib.h"

// Clasa pentru ferastra.
class Window
{
public:
	int width, heigth;
	const char* name;

	Window(int w, int h, const char* n) : width(w), heigth(h), name(n) 
	{
		if (width <= 200 || heigth <= 200)
		{
			std::cout << "Invalid Size\n";
			exit(1);
		}
	};

	void Init_Window()
	{
		InitWindow(width, heigth, name);
		SetTargetFPS(60);
	}

	~Window()
	{
		CloseWindow();
	}
};