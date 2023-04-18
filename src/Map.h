#ifndef MAP_H
#define MAP_H

#include <raylib.h>
#include <cmath>
#include <vector>
#include "Player.h"

void drawMiniMap();
void calculateWallHeight(Player *player, const char* texturePath);
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

#endif // MAP_H