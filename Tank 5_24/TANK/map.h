#pragma once
#include <Windows.h>
#include <vector>
#include "tank.h"
using namespace std;
//��ͼ������͸�
//#define block_wide = GAME_W / 64;
//#define block_high = GAME_H / 64;
#define block_wide 15
#define block_high 11
#define map_max 35

extern int stage;

extern vector<int> blockmap;

//��ͼ����
extern vector<int> block;

//����Ԥ�õ�ͼ
void LoadMap();
//ȫ��ͼ��ʼ��
void MapInit();
