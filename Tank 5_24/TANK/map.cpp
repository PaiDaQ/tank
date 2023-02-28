#include "map.h"
#include "tank.h"
//全地图初始化
int stage = 0;

vector<int> blockmap;
vector<int> block;
//备用地图容器
int map[block_wide * block_high * map_max] = {
0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 1  , 0  , 1  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 1  , 0  , 1  , 0  ,
0  , 1  , 0  , 1  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 1  , 0  , 1  , 0  ,
0  , 1  , 0  , 1  , 1  , 0  , 1  , 7  , 1  , 0  , 1  , 1  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 0  , 1  , 1  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 1  , 1  , 0  , 7  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 1  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 1  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 1  , 1  , 1  , 0  , 1  , 0  , 1  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 1  , 0  , 7  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  ,
8  , 1  , 0  , 0  , 0  , 0  , 1  , 7  , 1  , 0  , 1  , 7  , 1  , 0  , 7  ,
8  , 8  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 8  , 0  , 0  ,
0  , 1  , 1  , 1  , 1  , 8  , 8  , 8  , 7  , 0  , 0  , 0  , 8  , 1  , 0  ,
0  , 0  , 0  , 0  , 7  , 8  , 1  , 0  , 1  , 0  , 1  , 1  , 8  , 1  , 0  ,
7  , 1  , 1  , 0  , 7  , 0  , 1  , 1  , 1  , 0  , 1  , 0  , 0  , 1  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 7  , 1  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 1  , 0  ,
0  , 1  , 1  , 0  , 1  , 0  , 1  , 10 , 1  , 0  , 0  , 1  , 1  , 1  , 0  ,

0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  ,
1  , 8  , 8  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 8  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 7  , 7  , 7  ,
8  , 8  , 8  , 8  , 0  , 0  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  ,
0  , 8  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 1  , 1  , 0  ,
0  , 1  , 0  , 0  , 0  , 1  , 1  , 7  , 7  , 7  , 0  , 0  , 1  , 8  , 8  ,
1  , 1  , 0  , 7  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 8  , 8  ,
0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 8  , 8  , 8  ,
1  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 8  ,
1  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 1  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 1  , 1  , 0  , 0  , 0  ,

0  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 0  ,
8  , 8  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 8  ,
8  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 7  ,
0  , 0  , 0  , 1  , 0  , 0  , 0  , 7  , 0  , 1  , 1  , 1  , 0  , 0  , 0  ,
12 , 12 , 0  , 1  , 7  , 7  , 0  , 7  , 0  , 0  , 1  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 1  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 12 , 12 , 12 ,
0  , 0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 1  , 1  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  ,
8  , 0  , 0  , 1  , 1  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 8  , 8  ,
7  , 8  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 8  , 8  , 7  ,

0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 7  , 7  , 7  , 7  , 0  , 0  ,
7  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 12 , 12 , 12 , 12 , 0  , 12 ,
0  , 0  , 0  , 0  , 12 , 12 , 12 , 0  , 12 , 12 , 0  , 0  , 0  , 1  , 1  ,
1  , 1  , 1  , 0  , 12 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
12 , 12 , 12 , 0  , 12 , 1  , 1  , 7  , 1  , 1  , 0  , 0  , 0  , 1  , 1  ,
0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  ,
0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 0  ,
1  , 1  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 8  , 8  , 8  , 0  , 0  , 0  ,
0  , 1  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 0  , 1  , 0  ,
0  , 1  , 0  , 7  , 0  , 1  , 0  , 7  , 0  , 1  , 0  , 8  , 0  , 1  , 8  ,
0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 8  , 0  , 1  , 8  ,
1  , 1  , 1  , 0  , 0  , 7  , 8  , 1  , 8  , 1  , 7  , 8  , 1  , 1  , 8  ,
0  , 0  , 0  , 0  , 0  , 0  , 8  , 8  , 8  , 0  , 0  , 0  , 0  , 8  , 8  ,
7  , 7  , 0  , 0  , 1  , 0  , 0  , 8  , 0  , 0  , 1  , 0  , 1  , 1  , 7  ,
0  , 1  , 1  , 0  , 0  , 1  , 1  , 0  , 1  , 1  , 0  , 0  , 7  , 7  , 7  ,
0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 8  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 8  ,
0  , 0  , 1  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 1  , 0  , 0  , 8  , 8  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 7  , 7  , 7  , 0  , 0  , 8  , 0  , 0  , 0  , 7  , 0  , 0  , 0  ,
0  , 7  , 0  , 0  , 0  , 0  , 8  , 7  , 0  , 0  , 7  , 7  , 7  , 0  , 0  ,
0  , 0  , 0  , 0  , 8  , 7  , 7  , 7  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
0  , 7  , 0  , 8  , 7  , 7  , 7  , 7  , 0  , 7  , 0  , 0  , 7  , 7  , 0  ,
0  , 0  , 0  , 7  , 7  , 7  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 0  , 0  ,
7  , 0  , 0  , 0  , 0  , 7  , 0  , 7  , 7  , 7  , 8  , 0  , 0  , 7  , 0  ,
0  , 0  , 7  , 7  , 0  , 0  , 0  , 7  , 8  , 0  , 0  , 0  , 7  , 7  , 0  ,
0  , 7  , 0  , 0  , 7  , 0  , 0  , 8  , 0  , 0  , 0  , 7  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 7  , 7  ,
7  , 7  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 1  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  ,
8  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  ,
8  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 1  , 1  , 0  , 1  , 7  ,
8  , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 0  , 12 ,
0  , 0  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 7  , 0  , 0  , 1  ,
1  , 1  , 0  , 7  , 0  , 0  , 7  , 1  , 8  , 8  , 8  , 8  , 0  , 7  , 0  ,
12 , 12 , 0  , 12 , 12 , 12 , 12 , 12 , 12 , 0  , 12 , 12 , 12 , 12 , 12 ,
8  , 8  , 0  , 0  , 1  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 1  , 0  ,
8  , 8  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 1  , 1  , 0  ,
8  , 7  , 1  , 0  , 1  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 1  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 0  , 0  , 0  ,
1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 7  , 7  , 0  , 0  , 0  , 1  ,
0  , 0  , 0  , 0  , 0  , 8  , 7  , 7  , 0  , 0  , 0  , 8  , 0  , 0  , 0  ,
0  , 0  , 0  , 7  , 7  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 1  , 0  , 8  , 0  , 8  , 8  , 0  , 0  , 0  , 0  , 8  , 0  , 1  , 7  ,
0  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 7  , 7  , 7  , 0  , 0  , 0  , 0  ,
1  , 0  , 0  , 8  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 8  , 0  , 0  , 1  ,
1  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 7  , 7  , 7  , 0  , 0  , 0  , 1  ,
0  , 0  , 1  , 8  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 8  , 1  , 0  , 0  ,
0  , 0  , 1  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 1  , 0  , 0  ,
0  , 0  , 1  , 1  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 1  , 1  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 0  , 8  , 8  , 8  , 8  , 0  , 0  , 1  , 1  , 1  , 0  ,
1  , 1  , 0  , 0  , 1  , 8  , 7  , 7  , 8  , 1  , 1  , 0  , 0  , 0  , 1  ,
1  , 1  , 0  , 1  , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 1  , 0  , 1  , 1  ,
0  , 1  , 1  , 1  , 7  , 7  , 0  , 0  , 7  , 7  , 1  , 1  , 1  , 1  , 0  ,
0  , 0  , 1  , 1  , 7  , 1  , 1  , 1  , 1  , 7  , 1  , 1  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 1  , 1  , 7  , 7  , 1  , 1  , 1  , 0  , 0  , 8  , 0  ,
1  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 1  ,
1  , 0  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 8  , 8  , 8  , 1  ,
0  , 0  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 0  , 0  ,
0  , 0  , 0  , 1  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 1  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 1  , 0  , 0  , 1  , 1  , 0  , 0  ,
0  , 1  , 1  , 1  , 1  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 0  , 0  , 1  , 1  , 0  , 1  , 1  , 0  , 0  , 8  , 8  , 8  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 8  , 8  , 8  , 8  ,
0  , 1  , 0  , 0  , 7  , 1  , 1  , 7  , 1  , 1  , 1  , 8  , 8  , 1  , 7  ,
0  , 1  , 1  , 1  , 1  , 7  , 0  , 0  , 0  , 1  , 0  , 8  , 8  , 0  , 1  ,
0  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 8  , 8  , 0  , 8  , 1  , 0  , 0  ,
7  , 1  , 1  , 0  , 8  , 8  , 8  , 8  , 8  , 7  , 7  , 1  , 1  , 1  , 0  ,
0  , 0  , 1  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  ,
0  , 0  , 0  , 8  , 8  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 8  , 8  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 0  , 0  , 0  ,
0  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 7  ,
0  , 0  , 12 , 12 , 12 , 12 , 12 , 0  , 1  , 1  , 0  , 7  , 0  , 1  , 0  ,
1  , 0  , 1  , 1  , 1  , 1  , 12 , 12 , 12 , 0  , 0  , 12 , 1  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 12 , 7  , 0  , 0  ,
12 , 12 , 12 , 0  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 12 , 12 , 12 , 0  ,
1  , 1  , 1  , 0  , 7  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 1  ,
1  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 0  , 1  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 1  , 1  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 0  , 0  ,
0  , 0  , 7  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
0  , 0  , 1  , 0  , 1  , 1  , 8  , 7  , 8  , 1  , 1  , 0  , 1  , 1  , 1  ,
1  , 0  , 0  , 0  , 1  , 8  , 8  , 8  , 8  , 8  , 1  , 0  , 7  , 0  , 1  ,
1  , 1  , 7  , 0  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 0  , 0  , 0  , 1  ,
1  , 1  , 0  , 0  , 1  , 1  , 8  , 7  , 8  , 1  , 1  , 0  , 7  , 1  , 1  ,
1  , 1  , 7  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 0  ,
1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 7  , 0  , 7  ,
1  , 1  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 1  , 0  , 0  ,
1  , 1  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
8  , 8  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 8  , 8  ,
0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 1  , 8  , 8  , 1  , 8  , 8  , 1  , 0  , 0  , 0  , 0  ,
8  , 8  , 0  , 0  , 0  , 1  , 8  , 1  , 8  , 1  , 0  , 0  , 0  , 8  , 8  ,
12 , 12 , 12 , 12 , 0  , 8  , 1  , 8  , 1  , 8  , 0  , 12 , 12 , 12 , 12 ,
0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  ,
0  , 7  , 0  , 7  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 7  , 0  , 7  , 0  ,
1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 0  , 7  , 0  , 7  , 0  , 1  , 10 , 1  , 0  , 7  , 0  , 7  , 0  , 7  ,

0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  ,
0  , 8  , 8  , 1  , 1  , 8  , 8  , 8  , 8  , 1  , 1  , 0  , 0  , 0  , 0  ,
8  , 8  , 8  , 8  , 8  , 8  , 1  , 1  , 8  , 8  , 8  , 8  , 8  , 1  , 7  ,
8  , 0  , 1  , 0  , 0  , 0  , 0  , 7  , 8  , 8  , 1  , 0  , 0  , 1  , 0  ,
0  , 1  , 1  , 1  , 1  , 1  , 1  , 8  , 8  , 1  , 1  , 1  , 0  , 1  , 0  ,
7  , 7  , 1  , 1  , 0  , 0  , 0  , 8  , 1  , 0  , 0  , 0  , 0  , 8  , 8  ,
0  , 0  , 0  , 1  , 0  , 0  , 7  , 1  , 0  , 0  , 8  , 8  , 1  , 1  , 8  ,
0  , 1  , 0  , 0  , 0  , 1  , 1  , 8  , 0  , 8  , 8  , 1  , 0  , 0  , 8  ,
0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 8  , 1  , 8  , 8  ,
0  , 0  , 1  , 0  , 8  , 0  , 1  , 1  , 1  , 0  , 1  , 8  , 0  , 8  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 8  , 8  , 8  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 7  , 8  , 7  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 8  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 8  , 0  , 0  , 0  , 0  , 0  , 7  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 8  , 8  , 0  , 0  , 0  , 8  , 8  , 8  , 7  , 1  , 0  , 0  , 0  , 0  ,
0  , 8  , 0  , 8  , 0  , 0  , 8  , 0  , 8  , 8  , 8  , 7  , 1  , 0  , 0  ,
0  , 0  , 8  , 0  , 8  , 0  , 0  , 8  , 0  , 0  , 8  , 8  , 8  , 0  , 0  ,
1  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 8  , 0  , 0  , 8  , 8  , 7  , 7  ,
1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 8  , 8  , 8  , 8  , 8  ,
7  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 8  , 0  , 8  , 8  , 8  ,
7  , 7  , 1  , 1  , 0  , 0  , 1  , 10 , 1  , 0  , 8  , 0  , 0  , 8  , 8  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 1  , 1  , 0  , 0  , 1  , 0  , 0  , 9  , 9  , 9  , 1  , 0  , 0  , 0  ,
0  , 1  , 1  , 0  , 1  , 1  , 0  , 7  , 9  , 9  , 9  , 1  , 1  , 1  , 0  ,
9  , 9  , 9  , 9  , 7  , 1  , 0  , 0  , 1  , 9  , 9  , 9  , 9  , 9  , 0  ,
9  , 9  , 9  , 9  , 9  , 9  , 9  , 1  , 1  , 1  , 1  , 9  , 9  , 7  , 7  ,
0  , 0  , 0  , 7  , 1  , 1  , 9  , 9  , 1  , 9  , 9  , 9  , 9  , 1  , 1  ,
1  , 1  , 1  , 1  , 1  , 9  , 9  , 9  , 9  , 9  , 7  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 1  , 0  , 7  , 0  , 7  , 1  , 1  , 1  , 0  , 1  , 0  ,
9  , 9  , 9  , 9  , 1  , 9  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  ,
1  , 9  , 9  , 9  , 9  , 9  , 1  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 0  ,
1  , 1  , 7  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 1  , 0  , 0  , 1  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 7  , 7  , 8  , 0  ,
0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 7  , 0  ,
1  , 1  , 8  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 7  , 0  ,
0  , 0  , 1  , 8  , 1  , 0  , 0  , 1  , 0  , 8  , 8  , 1  , 7  , 7  , 0  ,
0  , 0  , 0  , 1  , 0  , 8  , 7  , 1  , 8  , 8  , 0  , 1  , 0  , 0  , 0  ,
0  , 0  , 1  , 1  , 1  , 7  , 1  , 1  , 7  , 1  , 1  , 1  , 0  , 0  , 0  ,
0  , 0  , 1  , 8  , 0  , 8  , 1  , 7  , 8  , 8  , 0  , 0  , 0  , 0  , 0  ,
7  , 7  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  ,
7  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 7  , 7  , 1  , 0  ,
8  , 7  , 7  , 7  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 7  , 1  , 1  , 7  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 7  , 7  ,

0  , 1  , 0  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  , 1  , 0  ,
0  , 1  , 0  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  , 1  , 0  ,
0  , 7  , 0  , 0  , 7  , 0  , 7  , 0  , 7  , 0  , 7  , 0  , 0  , 7  , 0  ,
0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  ,
7  , 0  , 7  , 1  , 1  , 1  , 0  , 7  , 0  , 1  , 1  , 1  , 7  , 0  , 7  ,
8  , 8  , 8  , 8  , 8  , 7  , 0  , 8  , 0  , 7  , 8  , 8  , 8  , 8  , 8  ,
8  , 8  , 8  , 8  , 8  , 8  , 1  , 8  , 1  , 8  , 8  , 8  , 8  , 8  , 8  ,
1  , 0  , 1  , 0  , 1  , 8  , 8  , 8  , 8  , 8  , 1  , 0  , 1  , 0  , 1  ,
0  , 1  , 0  , 1  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 1  , 0  , 1  , 0  ,
0  , 1  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 1  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 12 , 0  , 1  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 7  , 0  , 0  ,
7  , 0  , 0  , 0  , 12 , 0  , 1  , 7  , 0  , 0  , 1  , 0  , 1  , 0  , 0  ,
0  , 0  , 0  , 0  , 12 , 0  , 7  , 0  , 1  , 1  , 0  , 0  , 1  , 0  , 0  ,
1  , 0  , 0  , 0  , 12 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 1  , 1  , 1  , 12 , 12 , 0  , 12 , 12 , 12 , 12 , 12 , 0  , 0  , 1  ,
0  , 0  , 0  , 1  , 1  , 0  , 0  , 8  , 8  , 8  , 8  , 12 , 0  , 7  , 7  ,
0  , 7  , 0  , 0  , 0  , 0  , 7  , 1  , 1  , 8  , 8  , 12 , 0  , 1  , 1  ,
0  , 1  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 8  , 8  , 8  ,
0  , 1  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 12 , 8  , 8  , 8  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 12 , 0  , 8  , 0  ,

0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  ,
0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  ,
0  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 1  , 1  , 1  , 0  ,
8  , 0  , 7  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 8  , 8  , 8  , 8  , 0  ,
8  , 0  , 7  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 8  , 8  , 8  , 8  , 0  ,
8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 1  , 1  , 1  , 1  , 1  ,
1  , 1  , 8  , 8  , 1  , 1  , 8  , 8  , 8  , 1  , 1  , 1  , 1  , 1  , 0  ,
0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 7  ,
7  , 0  , 1  , 1  , 7  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 7  ,
0  , 7  , 1  , 0  , 0  , 7  , 1  , 1  , 1  , 1  , 1  , 1  , 7  , 7  , 7  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 8  , 7  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 8  , 0  , 0  , 8  , 0  , 0  , 0  , 8  , 8  , 0  , 0  , 8  ,
8  , 0  , 8  , 1  , 8  , 0  , 0  , 8  , 0  , 8  , 1  , 1  , 8  , 8  , 7  ,
1  , 8  , 0  , 8  , 1  , 8  , 8  , 7  , 8  , 0  , 8  , 8  , 8  , 0  , 8  ,
7  , 1  , 8  , 0  , 8  , 0  , 0  , 8  , 0  , 0  , 0  , 8  , 7  , 8  , 0  ,
1  , 8  , 0  , 0  , 0  , 8  , 0  , 0  , 0  , 0  , 8  , 0  , 8  , 0  , 0  ,
8  , 0  , 0  , 0  , 8  , 1  , 8  , 0  , 0  , 8  , 1  , 8  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 8  , 1  , 8  , 0  , 0  , 0  , 8  , 0  , 0  , 8  , 0  ,
0  , 8  , 0  , 0  , 0  , 8  , 1  , 1  , 1  , 0  , 0  , 0  , 8  , 7  , 8  ,
8  , 7  , 8  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 8  , 1  , 8  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 7  , 7  , 7  , 8  , 8  , 1  , 7  , 1  , 8  , 8  , 7  , 7  , 7  , 0  ,
0  , 0  , 0  , 0  , 7  , 8  , 8  , 8  , 8  , 8  , 7  , 0  , 0  , 0  , 0  ,
8  , 0  , 0  , 0  , 7  , 8  , 8  , 8  , 8  , 8  , 7  , 0  , 0  , 0  , 8  ,
7  , 8  , 0  , 0  , 0  , 0  , 7  , 8  , 7  , 0  , 0  , 0  , 0  , 8  , 7  ,
8  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 8  ,
0  , 0  , 0  , 0  , 7  , 0  , 0  , 7  , 0  , 0  , 7  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 7  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 7  , 0  , 0  ,

0  , 0  , 7  , 0  , 0  , 1  , 7  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  ,
0  , 0  , 1  , 0  , 0  , 1  , 8  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 0  ,
8  , 8  , 8  , 8  , 8  , 8  , 8  , 1  , 0  , 0  , 0  , 0  , 0  , 7  , 7  ,
1  , 7  , 8  , 8  , 1  , 1  , 1  , 7  , 1  , 0  , 0  , 0  , 1  , 1  , 0  ,
1  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 1  ,
1  , 0  , 1  , 1  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  ,
0  , 0  , 7  , 0  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  ,
1  , 0  , 1  , 0  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  ,
1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 9  , 9  , 9  , 9  , 9  ,
1  , 0  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 9  , 9  , 9  , 9  ,
0  , 0  , 1  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 9  , 9  , 9  , 9  ,

0  , 0  , 0  , 0  , 7  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  , 7  , 0  ,
0  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  ,
0  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 7  , 7  ,
7  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 1  , 0  , 7  , 0  , 0  , 7  ,
0  , 0  , 0  , 7  , 0  , 1  , 1  , 1  , 7  , 1  , 0  , 1  , 1  , 0  , 0  ,
0  , 7  , 1  , 1  , 0  , 1  , 0  , 0  , 7  , 1  , 0  , 7  , 1  , 0  , 0  ,
0  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 1  ,
0  , 0  , 0  , 0  , 1  , 0  , 1  , 7  , 0  , 0  , 1  , 1  , 0  , 1  , 1  ,
1  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 7  , 0  , 0  , 0  , 0  , 0  , 1  ,
1  , 0  , 1  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 0  , 7  , 7  , 0  , 0  ,
1  , 0  , 1  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 1  , 1  , 1  , 0  ,

0  , 0  , 12 , 12 , 12 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 0  , 0  , 0  , 12 , 8  , 0  , 1  , 0  , 1  , 0  , 12 , 12 , 12 , 0  ,
8  , 7  , 0  , 7  , 7  , 1  , 0  , 7  , 0  , 7  , 8  , 12 , 0  , 0  , 0  ,
8  , 8  , 8  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 7  ,
8  , 8  , 7  , 7  , 7  , 1  , 7  , 1  , 7  , 1  , 7  , 0  , 0  , 7  , 8  ,
8  , 7  , 0  , 0  , 0  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 8  , 8  , 8  ,
0  , 0  , 0  , 12 , 8  , 0  , 7  , 1  , 7  , 1  , 7  , 7  , 7  , 8  , 8  ,
0  , 12 , 12 , 12 , 0  , 1  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 8  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 8  , 12 , 0  , 0  , 0  , 7  ,
7  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 12 , 12 , 12 , 0  , 0  ,
7  , 7  , 7  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 7  ,

0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
7  , 7  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 7  , 7  , 0  , 0  , 0  , 0  ,
0  , 7  , 0  , 0  , 7  , 7  , 7  , 7  , 0  , 0  , 8  , 0  , 7  , 7  , 8  ,
0  , 1  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 7  , 7  , 7  , 7  , 0  , 0  ,
8  , 7  , 7  , 0  , 7  , 7  , 1  , 7  , 1  , 1  , 1  , 0  , 0  , 0  , 0  ,
0  , 0  , 7  , 8  , 7  , 0  , 8  , 0  , 0  , 0  , 1  , 0  , 0  , 7  , 7  ,
0  , 0  , 1  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 7  , 7  , 1  , 7  , 0  ,
8  , 7  , 7  , 7  , 7  , 8  , 8  , 1  , 7  , 7  , 7  , 0  , 1  , 7  , 0  ,
0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 8  , 8  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 7  , 0  , 1  , 1  , 1  , 0  , 0  , 8  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 7  , 0  , 1  , 10 , 1  , 0  , 0  , 7  , 0  , 1  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 7  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 8  , 1  , 0  , 0  , 1  , 1  , 0  , 0  ,
0  , 0  , 0  , 1  , 7  , 7  , 8  , 8  , 8  , 7  , 7  , 1  , 1  , 0  , 0  ,
0  , 0  , 7  , 8  , 8  , 8  , 8  , 9  , 8  , 8  , 8  , 8  , 1  , 0  , 0  ,
0  , 1  , 8  , 8  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 8  , 8  , 1  , 0  ,
7  , 8  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 8  , 8  , 7  ,
8  , 8  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 8  , 0  ,
0  , 8  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 8  , 0  ,
0  , 8  , 9  , 9  , 9  , 0  , 1  , 1  , 1  , 0  , 9  , 9  , 9  , 8  , 0  ,
0  , 8  , 9  , 9  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 9  , 9  , 8  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  ,
0  , 1  , 12 , 12 , 12 , 0  , 7  , 0  , 1  , 1  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 1  , 8  , 8  , 8  , 8  , 12 , 12 , 1  , 7  , 0  ,
0  , 7  , 0  , 0  , 0  , 0  , 8  , 8  , 8  , 8  , 0  , 0  , 0  , 0  , 0  ,
8  , 8  , 1  , 0  , 0  , 12 , 12 , 7  , 0  , 8  , 0  , 0  , 0  , 1  , 0  ,
8  , 8  , 8  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 7  ,
7  , 1  , 12 , 12 , 12 , 8  , 8  , 12 , 12 , 12 , 8  , 8  , 0  , 1  , 0  ,
0  , 0  , 0  , 0  , 0  , 8  , 0  , 12 , 12 , 12 , 8  , 8  , 12 , 12 , 0  ,
0  , 0  , 0  , 7  , 7  , 8  , 0  , 0  , 0  , 0  , 8  , 8  , 12 , 12 , 0  ,
0  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 1  , 1  , 7  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 0  , 0  , 0  , 7  , 7  , 0  , 0  ,
0  , 7  , 7  , 7  , 0  , 1  , 8  , 8  , 7  , 0  , 1  , 8  , 8  , 1  , 0  ,
1  , 8  , 8  , 8  , 1  , 8  , 8  , 8  , 8  , 1  , 8  , 8  , 8  , 8  , 1  ,
8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  ,
7  , 8  , 12 , 12 , 12 , 8  , 8  , 7  , 8  , 12 , 12 , 12 , 12 , 8  , 7  ,
8  , 8  , 8  , 8  , 12 , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 12 , 8  , 8  ,
8  , 8  , 8  , 8  , 8  , 1  , 1  , 1  , 1  , 8  , 8  , 8  , 8  , 8  , 8  ,
7  , 8  , 8  , 8  , 1  , 0  , 0  , 0  , 0  , 1  , 8  , 8  , 8  , 8  , 7  ,
0  , 7  , 1  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 7  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 12 , 0  , 0  , 0  , 0  , 12 , 0  , 0  , 0  , 0  , 0  ,
12 , 12 , 12 , 0  , 12 , 0  , 12 , 12 , 12 , 12 , 0  , 12 , 12 , 12 , 12 ,
8  , 8  , 8  , 1  , 0  , 0  , 1  , 0  , 0  , 12 , 0  , 12 , 8  , 8  , 12 ,
8  , 12 , 12 , 12 , 12 , 12 , 0  , 7  , 0  , 0  , 1  , 8  , 8  , 8  , 8  ,
8  , 0  , 0  , 0  , 12 , 0  , 0  , 12 , 0  , 12 , 12 , 12 , 12 , 8  , 8  ,
12 , 0  , 0  , 1  , 8  , 1  , 0  , 1  , 8  , 0  , 12 , 0  , 0  , 0  , 12 ,
1  , 0  , 12 , 0  , 8  , 0  , 12 , 12 , 0  , 8  , 8  , 1  , 0  , 0  , 12 ,
12 , 0  , 0  , 0  , 12 , 0  , 0  , 12 , 1  , 12 , 12 , 12 , 12 , 0  , 0  ,
0  , 0  , 1  , 0  , 0  , 8  , 8  , 0  , 0  , 8  , 12 , 0  , 0  , 0  , 12 ,
0  , 12 , 12 , 12 , 12 , 8  , 1  , 1  , 1  , 0  , 12 , 0  , 12 , 12 , 12 ,
0  , 12 , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  , 9  ,
9  , 9  , 9  , 9  , 1  , 9  , 9  , 9  , 9  , 9  , 1  , 9  , 9  , 9  , 9  ,
9  , 1  , 0  , 0  , 1  , 0  , 1  , 9  , 1  , 0  , 1  , 0  , 0  , 1  , 9  ,
9  , 1  , 1  , 1  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 1  , 9  ,
9  , 9  , 9  , 0  , 1  , 1  , 1  , 7  , 1  , 1  , 1  , 0  , 9  , 9  , 9  ,
7  , 9  , 9  , 9  , 9  , 0  , 1  , 0  , 1  , 0  , 9  , 9  , 9  , 9  , 7  ,
9  , 9  , 9  , 9  , 9  , 0  , 0  , 1  , 0  , 0  , 9  , 9  , 9  , 9  , 9  ,
9  , 9  , 9  , 9  , 1  , 0  , 7  , 7  , 7  , 0  , 1  , 9  , 9  , 9  , 9  ,
9  , 1  , 9  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 9  , 1  , 9  ,
0  , 1  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 1  , 9  ,
0  , 1  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 1  , 9  ,

0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  , 0  ,
0  , 7  , 7  , 0  , 0  , 0  , 7  , 0  , 0  , 0  , 7  , 8  , 8  , 0  , 0  ,
0  , 0  , 0  , 7  , 0  , 0  , 0  , 0  , 7  , 7  , 8  , 8  , 0  , 7  , 0  ,
0  , 0  , 0  , 0  , 7  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 7  , 7  , 0  ,
0  , 7  , 7  , 8  , 0  , 7  , 7  , 8  , 7  , 7  , 7  , 0  , 0  , 7  , 0  ,
0  , 0  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 7  , 0  , 0  , 0  ,
0  , 7  , 7  , 8  , 0  , 7  , 7  , 8  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
8  , 8  , 8  , 8  , 7  , 0  , 0  , 7  , 0  , 7  , 7  , 0  , 0  , 0  , 7  ,
0  , 0  , 7  , 7  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 7  , 0  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 7  , 7  , 7  , 0  , 0  ,
7  , 0  , 7  , 7  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 1  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  , 0  , 0  ,
1  , 0  , 1  , 0  , 1  , 1  , 0  , 0  , 1  , 0  , 1  , 1  , 0  , 0  , 0  ,
0  , 1  , 0  , 1  , 0  , 1  , 0  , 0  , 1  , 0  , 1  , 1  , 1  , 0  , 0  ,
0  , 1  , 0  , 1  , 0  , 1  , 1  , 0  , 0  , 1  , 0  , 1  , 1  , 0  , 0  ,
0  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 0  , 0  ,
0  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 1  , 1  , 1  , 0  , 1  , 1  , 1  ,
0  , 0  , 1  , 0  , 0  , 1  , 1  , 1  , 0  , 1  , 0  , 0  , 0  , 1  , 1  ,
0  , 1  , 0  , 0  , 1  , 1  , 0  , 1  , 1  , 1  , 1  , 0  , 0  , 1  , 0  ,
0  , 1  , 0  , 1  , 1  , 0  , 1  , 1  , 1  , 0  , 1  , 1  , 0  , 1  , 0  ,
0  , 1  , 0  , 1  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 1  , 1  , 1  , 0  ,

0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  ,
8  , 0  , 0  , 0  , 8  , 1  , 8  , 1  , 8  , 0  , 0  , 0  , 8  , 0  , 0  ,
1  , 8  , 8  , 8  , 1  , 1  , 1  , 1  , 1  , 8  , 8  , 8  , 1  , 8  , 0  ,
1  , 1  , 1  , 1  , 1  , 7  , 1  , 7  , 1  , 1  , 1  , 1  , 1  , 8  , 0  ,
12 , 12 , 12 , 12 , 1  , 1  , 1  , 1  , 1  , 12 , 12 , 12 , 12 , 8  , 0  ,
12 , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 12 , 12 , 8  ,
1  , 1  , 1  , 1  , 12 , 1  , 1  , 1  , 12 , 1  , 1  , 1  , 1  , 8  , 8  ,
1  , 1  , 12 , 12 , 12 , 12 , 1  , 12 , 12 , 12 , 12 , 1  , 1  , 12 , 12 ,
8  , 12 , 12 , 8  , 8  , 8  , 8  , 8  , 8  , 8  , 12 , 12 , 8  , 12 , 8  ,
0  , 8  , 8  , 0  , 0  , 0  , 1  , 1  , 1  , 0  , 8  , 8  , 0  , 8  , 0  ,
0  , 0  , 0  , 0  , 0  , 0  , 1  , 10 , 1  , 0  , 0  , 0  , 0  , 0  , 0
};
void MapInit()
{
	blockmap.assign(map, map + block_wide * block_high * map_max);
}
//载入预置地图
void LoadMap()
{
	block.assign(blockmap.begin() + block_wide * block_high * stage,
		blockmap.begin() + block_wide * block_high * stage + block_wide * block_high);
}

