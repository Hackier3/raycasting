#include <raylib.h>
#include <vector>

class Player
{
public:
	Player(const char* texture);
	void drawPlayer();
	void calculateRaysCoords();
	void drawVisionRays();
	void movement();

	float x;
	float y;
	float speed;
	double rotationAngle;

private:
	Texture2D texture;
	const int numberOfRays = 1001;
	const int rayDestributtionDestiny = 12;
	std::vector<Vector2> raysEndCoords;
};