#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <vector>

class Player
{
public:
	Player(const char* texturePath);
	void drawPlayer();
	void calculateRaysCoords();
	void drawVisionRays();
	void movement();

	std::vector<Vector2> raysEndCoords;
	std::vector<int> raysForBlock; // variable indicating how many rays (including me) point to the block
	float x;
	float y;
	static const int numberOfRays = 1001;
	static const int rayDestributtionDestiny = numberOfRays / 88;
	double rotationAngle;

private:
	Texture2D texture;
	float speed;
};

#endif // PLAYER_H

