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
	float x;
	float y;
	static const int numberOfRays = 3001;
	static const int rayDestributtionDestiny = numberOfRays / 88;
private:
	Texture2D texture;
	float speed;
	double rotationAngle;
};

#endif // PLAYER_H

