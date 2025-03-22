#pragma once

#include <iostream>
#include "raylib.h"
// facem o clasa pentru functiile comune din codul nostru.
class Entity
{
protected:
	void Animate(float uTime, float& rTime, float deltaTime, int maxFrame, int& fr, Rectangle& r)
	{
		rTime += deltaTime;
		if (rTime > uTime)
		{
			rTime = 0;
			r.x = r.width * fr;
			fr++;
			if (fr > maxFrame) fr = 0;
		}
	}
};