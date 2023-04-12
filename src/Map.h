#ifndef MAP_H
#define MAP_H

#include <raylib.h>
#include <cmath>
#include <vector>
#include "Player.h"

void drawMiniMap();
void calculateWallHeight(Player *player);
void draw3DMap();

const int mapWidth = 9;
const int mapHeight = 7;
const char map[] = "#########"
                   "#.......#"
                   "#..##..##"
                   "#.......#"
                   "#....####"
                   "#.......#"
                   "#########";
extern std::vector<float> wallHeight;

#endif // MAP_H