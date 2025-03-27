#pragma once
#include "raylib.h"

//clasa pentru entitatile din joc(Scarfy,Nebula)

class Entity
{
protected:
	void Animation(float uTime, float& rTime,Rectangle& r, int& frame, int maxFrame, float deltaTime)
	{
		rTime += deltaTime;
		if (rTime >= uTime)
		{
			rTime = 0;
			r.x = r.width * frame;
			frame++;
			if (frame > maxFrame) frame = 0;
		}
	}

	void Move_Background(float deltaTime,int width,float velocity, Vector2& pos1, Vector2& pos2,float scale)
	{
		pos1.x += velocity * deltaTime;
		pos2.x = pos1.x + width* scale;
		if (pos2.x <= -width * scale) pos1.x = 0;
	}
};
