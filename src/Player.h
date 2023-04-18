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
	void checkCollision();

	std::vector<Vector2> raysEndCoords;
	std::vector<int> raysForBlock; // variable indicating how many rays (including me) point to the block
	float x;
	float y;
	static constexpr float numberOfRays = 401;
	
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;

private:
	Texture2D texture;
	float speed;
	const float rayDestributtionDestiny;
	double rotationAngle;
};

#endif // PLAYER_H

