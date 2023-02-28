#pragma once
#include <Windows.h>
#include <vector>
#include "tank.h"
using namespace std;
//地图块数宽和高
//#define block_wide = GAME_W / 64;
//#define block_high = GAME_H / 64;
#define block_wide 15
#define block_high 11
#define map_max 35

extern int stage;

extern vector<int> blockmap;

//地图容器
extern vector<int> block;

//载入预置地图
void LoadMap();
//全地图初始化
void MapInit();
