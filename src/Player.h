#include <raylib.h>
#include "Defines.h"

class Player
{
public:
	Player(const char* texturePath);
	void drawPlayer();

	float x;
	float y;
	float speed;
	double rotationAngle;
	Texture2D texture;

private:
};