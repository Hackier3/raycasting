#pragma once
#include <raylib.h>

class Player
{
public:
	Player(const char*);
	void drawPlayer();

	float x;
	float y;
	float speed = 1.5;

private:
	Texture2D playerTexture;
};
