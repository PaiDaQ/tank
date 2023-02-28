#include "tank.h"
//是否播放音效
bool sound = TRUE;

//兼容内存设备
HDC winDC;
HDC writeDC;
HDC backgroundDC;
HDC player_tankDC;
HDC bulletDC;
HDC blockDC;
HDC fireDC;
//兼容位图
HBITMAP writeBMP;
HBITMAP backgroundBMP;
HBITMAP player_tankBMP;
HBITMAP bulletBMP;
HBITMAP blockBMP;
HBITMAP fireBMP;

//游戏定时器
UINT game_timer;
//游戏状态
int game_state;
//玩家坦克
BaseTank player_tank;
//玩家子弹
vector<Bullet*> player_bullet;
//火花容器
vector<Fire*> fire;
//敌人容器
vector<BaseTank*> enemy_tank;
//敌人炮弹容器
vector<vector<Bullet*>*> enemy_bullet;


//L键按下
bool keyup_L = true;
//关卡
int wintime;
const int wintimemax = 200;
const int stage_max = map_max;
//基地
int base_time;
const int base_timemax = 100;
//玩家生命数
bool player_death = false;
int player_num;
const int player_max = 3;
int player_time;
const int player_timemax = 100;
//玩家属性上限
const int max_life = 40;
const int max_speed = 8;
const int max_fire_speed = 16;
const int max_num = 2;
const int max_bullet_speed = 24;
//敌人数量
int enemy_num;
int enemy_rest;
const int enemy_maxscr = 4;
const int enemy_max = 20;
int enemy_time = 0;
const int enemy_timemax = 100;
//道具
int item;
int item_x;
int item_y;
int invin_time;
const int invin_timemax = 1000;
//砖块循环数据
const int wall_min = 4;
const int wall_max = 6;
const int wall1_min = wall_min + 100;
const int wall1_max = wall_max + 100;
const int wall_timemax = 5;
int wall_time;
//水块循环数据
const int water_min = 12;
const int water_max = 23;
const int water1_min = water_min + 100;
const int water1_max = water_max + 100;
const int water_timemax = 3;
int water_time;
//游戏窗口句柄
HWND hwnd;


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)

{
	
	WNDCLASS wndcls;

	//定义窗口	
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = "Tank";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	//注册窗口
	RegisterClass(&wndcls);
	//屏幕宽和高
	int width, height;
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	//在屏幕中央创建窗口
	hwnd = CreateWindow("Tank", "坦克大战 V1.0", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
		(width - (GAME_W + 6)) / 2, (height - (GAME_H + 28)) / 2 - 10, GAME_W + 6, GAME_H + 28, NULL, NULL, hInstance, NULL);


	//获得窗口设备
	winDC = GetDC(hwnd);

	//创建缓冲内存
	writeDC = CreateCompatibleDC(winDC);
	//创建背景内存
	backgroundDC = CreateCompatibleDC(winDC);
	//创建玩家坦克内存
	player_tankDC = CreateCompatibleDC(winDC);
	//创建炮弹内存
	bulletDC = CreateCompatibleDC(winDC);
	//创建图块内存
	blockDC = CreateCompatibleDC(winDC);
	//创建火花内存
	fireDC = CreateCompatibleDC(winDC);

	//创建缓冲位图
	writeBMP = CreateCompatibleBitmap(winDC, GAME_W, GAME_H);
	//载入背景位图
	backgroundBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(BACK_GROUND), IMAGE_BITMAP, GAME_W, GAME_H, LR_DEFAULTCOLOR);
	//载入坦克位图
	player_tankBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(PLAYER_TANK), IMAGE_BITMAP, 256, 10240, LR_DEFAULTCOLOR);
	//载入炮弹位图
	bulletBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(BULLET), IMAGE_BITMAP, 160, 400, LR_DEFAULTCOLOR);
	//载入图块位图
	blockBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(MAP_BLOCK), IMAGE_BITMAP, 256, 896, LR_DEFAULTCOLOR);
	//载入火花位图
	fireBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(FIRE), IMAGE_BITMAP, 528, 132, LR_DEFAULTCOLOR);

	//选入到对应内存
	SelectObject(writeDC, writeBMP);
	SelectObject(backgroundDC, backgroundBMP);
	SelectObject(player_tankDC, player_tankBMP);
	SelectObject(bulletDC, bulletBMP);
	SelectObject(blockDC, blockBMP);
	SelectObject(fireDC, fireBMP);

	//用系统时间初始化随机数种子
	srand((unsigned)time(NULL));
	//读入预置地图
	MapInit();
	//显示游戏信息
	MessageBox(hwnd, "\
游戏模式：\n\
上下左右方向键移动坦克\n\
WSAD字母键改变炮口方向\n\
L键锁定或取消锁定炮口方向\n\
空格键开火\n\
P键暂停\n\
H键显示帮助\n\
\n\
道具说明：\n\
绿色道具：提升坦克护甲，最多提升3次\n\
红色道具：提升炮弹射速，最多提升4次\n\
蓝色道具：提升坦克速度，最多提升4次\n\
黄色道具：提升炮弹数量，最多提升1次\n\
\n\
", "规则说明", MB_OK);
	if (MessageBox(hwnd, "是否开启游戏音效？", "设置", MB_YESNO) == IDYES)
		sound = true;
	else sound = false;

	//显示窗口
	ShowWindow(hwnd, nCmdShow);
	//更新窗口
	UpdateWindow(hwnd);

	//游戏开始
	Start();
	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return  msg.wParam;

}

//窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//窗口是否激活
	case WM_ACTIVATE:
		if (wParam != WA_INACTIVE)
			SetTimer(hwnd, GAME_ID, GAME_TIME, NULL);
		else
			KillTimer(hwnd, GAME_ID);
		break;
		//窗口最小化和还原
	case WM_SIZE:
		if (wParam == SIZE_RESTORED)
			SetTimer(hwnd, GAME_ID, GAME_TIME, NULL);
		else if (wParam == SIZE_MINIMIZED)
			KillTimer(hwnd, GAME_ID);
		break;
		//定时器响应
	case WM_TIMER:
		switch (wParam)
		{
		case GAME_ID:
			//判断游戏状态	
			switch (game_state)
			{
			case GAME:
				Game();
				break;
			case PAUSE:
				MessageBox(hwnd, "游戏暂停！休息一下！", "", MB_OK);
				game_state = GAME;
				break;
			case GAMEOVER:
				MessageBox(hwnd, "游戏结束！再接再厉！", "", MB_OK);
				Start();
				break;
			case NEXTSTAGE:
				if (++stage == stage_max)
					game_state = WIN;
				else
				{
					game_state = GAME;
					Init();
				}
				break;
			case WIN:
				MessageBox(hwnd, "太厉害了，祝贺通关！", "", MB_OK);
				Start();
				break;
			}
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case 'H':
			MessageBox(hwnd, "\
按键说明：\n\
上下左右方向键移动坦克\n\
WSAD字母键改变炮口方向\n\
L键锁定或取消锁定炮口方向\n\
空格键开火\n\
P键暂停\n\
H键显示帮助\n\
\n\
道具说明：\n\
绿色道具：提升坦克护甲，最多提升3次\n\
红色道具：提升炮弹射速，最多提升4次\n\
蓝色道具：提升坦克速度，最多提升4次\n\
黄色道具：提升炮弹数量，最多提升1次\n\
\n\
", "规则说明", MB_OK);
			break;
		case 'P':
			if (game_state == GAME)
				game_state = PAUSE;
			break;
		}
		break;
		//关闭按钮
	case WM_CLOSE:
		MessageBox(hwnd, "感谢使用！再见！", "", MB_OK);
		break;
		//销毁窗口
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}

//游戏开始
void Start()
{
	SetTimer(hwnd, GAME_ID, GAME_TIME, NULL);
	player_tank = BaseTank(20 / 10 - 1, 20, 0, UP, 5 * 64, 10 * 64 + 64, UP, false, 16, 4, 8, 2, 1, 10, 8);
	stage = 0;
	player_num = player_max;
	game_state = GAME;
	Init();
}

//游戏过程
void Game()
{
	//玩家操作按键响应
	if (player_death == false)
		Key();
	//绘制游戏画面
	DrawGame();
	//基地毁灭
	if (base_time > 0)
	{
		if (--base_time == 0)
			game_state = GAMEOVER;
	}
	//过关
	if (wintime > 0)
	{
		if (--wintime == 0)
			game_state = NEXTSTAGE;
	}
	//玩家死亡
	if (player_death == true)
	{
		if (--player_time == 0)
		{
			if (player_num == 0)
				game_state = GAMEOVER;
			else
			{
				//玩家复活
				player_death = false;
				player_tank = BaseTank(20 / 10 - 1, 20, 0, UP, 5 * 64, 10 * 64 + 64, UP, false, 16, 4, 8, 2, 1, 10, 8);
			}
		}
	}
	//少于屏幕最大敌人数并且剩余敌人数大于零添加敌人
	if (enemy_num < enemy_maxscr && enemy_time == 0 && enemy_rest>0)
	{
		enemy_time = enemy_timemax;
	}
	if (enemy_time > 0)
	{
		--enemy_time;
		if (enemy_time == 0)
		{
			++enemy_num;
			--enemy_rest;
			int r = rand() % 10;
			int x = rand() % 3 * 7 * 64;
			//蓝色坦克
			if (r == 0)
				enemy_tank.push_back(new BaseTank(BLUE, 20, 0, DOWN, x, -64, DOWN, false, 8, 8, 4, 2, 1, 10, 12));
			//红色坦克
			else if (r == 1)
				enemy_tank.push_back(new BaseTank(RED, 50, 0, DOWN, x, -64, DOWN, true, 32, 2, 4, 3, 2, 10, 6));
			//金色坦克
			else if (r == 2)
				enemy_tank.push_back(new BaseTank(GOLD, 70, 0, DOWN, x, -64, DOWN, false, 16, 4, 4, 0, 2, 10, 8));
			//普通坦克
			else
				enemy_tank.push_back(new BaseTank(GREEN, 30, 0, DOWN, x, -64, DOWN, false, 32, 2, 4, 1, 1, 10, 6));
			//添加子弹容器
			enemy_bullet.push_back(new vector<Bullet*>);
		}
	}
}

//按键判断
void Key()
{
	//坦克行走
	if (player_tank.get_move() == 0)
	{
		//行走
		if (KEYDOWN(VK_DOWN))
		{
			player_tank.Change(DOWN);
			player_tank.set_move(64 / player_tank.get_speed());
		}
		else if (KEYDOWN(VK_LEFT))
		{
			player_tank.Change(LEFT);
			player_tank.set_move(64 / player_tank.get_speed());
		}
		else if (KEYDOWN(VK_UP))
		{
			player_tank.Change(UP);
			player_tank.set_move(64 / player_tank.get_speed());
		}
		else if (KEYDOWN(VK_RIGHT))
		{
			player_tank.Change(RIGHT);
			player_tank.set_move(64 / player_tank.get_speed());
		}
		if (player_tank.get_move() > 0)
		{
			bool hit = TankHitBlock(player_tank);
			player_tank.set_move(64 / player_tank.get_speed_real());
			if (hit == true)
			{
				player_tank.set_move(0);
				if (++player_tank.move_step > 2)
					player_tank.move_step = 0;
			}
			else
			{
				for (vector<BaseTank*>::iterator iter = enemy_tank.begin(); iter != enemy_tank.end(); ++iter)
				{
					BaseTank& tank = **iter;
					if (TankHitTank(player_tank, tank) == true)
					{
						player_tank.set_move(0);
						if (++player_tank.move_step > 2)
							player_tank.move_step = 0;
						break;
					}
				}
			}
			if (sound)PLAYB(MOTOR);
		}
	}
	if (player_tank.get_move() > 0)
	{
		player_tank.set_move(player_tank.get_move() - 1);
		if (++player_tank.move_step > 2)
			player_tank.move_step = 0;
		player_tank.Move();
		if (player_tank.get_move() == 0)
		{
			player_tank.set_x((player_tank.get_x() + 32) / 64 * 64);
			player_tank.set_y((player_tank.get_y() + 32) / 64 * 64);
		}
	}
	//转动炮台
	if (KEYDOWN('S'))
	{
		if (sound)PLAYB(TURRET);
		player_tank.set_gun_face(DOWN);
	}
	else if (KEYDOWN('A'))
	{
		if (sound)PLAYB(TURRET);
		player_tank.set_gun_face(LEFT);
	}
	else if (KEYDOWN('W'))
	{
		if (sound)PLAYB(TURRET);
		player_tank.set_gun_face(UP);
	}
	else if (KEYDOWN('D'))
	{
		if (sound)PLAYB(TURRET);
		player_tank.set_gun_face(RIGHT);
	}

	//锁定炮台
	if (keyup_L == true && KEYDOWN('L'))
	{
		keyup_L = false;
		if (player_tank.get_gun_lock() == false)player_tank.set_gun_lock(true);
		else player_tank.set_gun_lock(false);
	}
	else if (KEYUP('L'))keyup_L = true;

	//开火
	if (KEYDOWN(VK_SPACE)) {
		if (!player_tank.get_gun_step() && player_tank.get_bullet_num() < player_tank.get_bullet_max())
		{
			if (sound)PLAYA(SHOOT);
			int x = player_tank.get_x() + (64 - 40) / 2;
			int y = player_tank.get_y() + (64 - 40) / 2;
			switch (player_tank.get_gun_face())
			{
			case DOWN:
				y += 47;
				break;
			case LEFT:
				x -= 47;
				break;
			case UP:
				y -= 47;
				break;
			case RIGHT:
				x += 47;
			}
			player_bullet.push_back(new Bullet(player_tank.get_bullet_id(), 100, player_tank.get_gun_face(), x, y,
				player_tank.get_bullet_speed(), player_tank.get_bullet_power()));
			player_tank.set_bullet_num(player_tank.get_bullet_num() + 1);
			player_tank.Fire();
		}
	}
}

//画背景
void DrawBG()
{
	BitBlt(writeDC, 0, 0, GAME_W, GAME_H, backgroundDC, 0, 0, SRCCOPY);
}

//输出缓冲区到屏幕
void Print()
{
	BitBlt(winDC, 0, 0, GAME_W, GAME_H, writeDC, 0, 0, SRCCOPY);
}

//游戏单位绘制
void DrawGame()
{
	//绘制背景
	DrawBG();
	//绘制地图块
	DrawBlock();
	//处理和绘制道具
	Item();
	//处理和绘制敌人坦克
	EnemyTank();
	//处理和绘制玩家坦克
	if (player_death == false)
		player_tank.Draw(writeDC, player_tankDC, false);
	//绘制草块
	DrawGrass();
	//处理和绘制敌人炮弹
	EnemyBullet();
	//处理和绘制玩家炮弹
	PlayerBullet();
	//处理和绘制开火闪光
	player_tank.Draw(writeDC, player_tankDC, true);
	//绘制火花
	DrawFire();
	//输出到屏幕
	Print();
}

//初始化
void Init()
{
	//显示关卡
	char s[100];
	if (game_state == GAME)
	{
		sprintf_s(s, "准备进入第%d关", stage + 1);
		if (sound)PLAYA(START);
	}
	MessageBox(hwnd, s, "", MB_OK);
	//玩家坦克
	player_tank = BaseTank(
		player_tank.get_id(),
		player_tank.get_life(),
		player_tank.get_armor(),
		UP,
		5 * 64,
		10 * 64 + 64,
		UP,
		player_tank.get_gun_lock(),
		64 / player_tank.get_speed(),
		player_tank.get_speed(),
		player_tank.get_fire_speed(),
		player_tank.get_bullet_id(),
		player_tank.get_bullet_max(),
		player_tank.get_bullet_power(),
		player_tank.get_bullet_speed());
	//以下为动态资源的释放
	//玩家子弹清空
	for (vector<Bullet*>::iterator i = player_bullet.begin(); i != player_bullet.end(); i++)
		delete* i;
	player_bullet.clear();
	//火花容器清空
	for (vector<Fire*>::iterator it = fire.begin(); it != fire.end(); it++)
		delete* it;
	fire.clear();
	//敌人容器清空
	for (vector<BaseTank*>::iterator it = enemy_tank.begin(); it != enemy_tank.end(); it++)
		delete* it;
	enemy_tank.clear();
	//敌人炮弹容器清空
	for (vector<vector<Bullet*>*>::iterator i = enemy_bullet.begin(); i != enemy_bullet.end(); ++i)
	{
		for (vector<Bullet*>::iterator j = (**i).begin(); j != (**i).end(); ++j)
			delete* j;
		(**i).clear();
		delete* i;
	}
	enemy_bullet.clear();
	//关卡
	wintime = 0;
	//基地
	base_time = 0;
	//玩家恢复
	player_death = false;
	player_time = 0;
	//敌人数量
	enemy_num = 0;
	enemy_rest = enemy_max;
	enemy_time = 1;
	//砖块和水循环延时清零
	wall_time = 0;
	water_time = 0;
	//道具清零
	item = NONE;
	invin_time = 0;
	LoadMap();
}

//绘制地图块
void DrawBlock()
{
	int i;
	int x;
	int y;
	int x1;
	int y1;
	for (vector<int>::iterator iter = block.begin(); iter != block.end(); iter++)
	{
		int& id = *iter;
		if (id == GRASS || id == FLOOR )continue;
		//砖块循环
		if (wall_time == wall_timemax && id >= wall_min && id <= wall_max)
		{
			if (++id > wall_max)id = wall_min;
		}
		else if (wall_time == wall_timemax && id >= wall1_min && id <= wall1_max)
		{
			if (--id == wall1_min)id = wall_min;
		}
		//水块循环
		else if (water_time == water_timemax && id >= water_min && id <= water_max)
		{
			if (++id >= water_max)id = water1_max;
		}
		else if (water_time == water_timemax && id >= water1_min && id <= water1_max)
		{
			if (--id == water1_min)id = water_min;
		}
		//不等于雪块和草块就进行绘制
		i = iter - block.begin();
		x = i % block_wide * 64;
		y = i / block_wide * 64;
		x1 = id % 100 % 4 * 64;
		y1 = id % 100 / 4 * 128;
		BitBlt(writeDC, x, y, 64, 64, blockDC, x1, y1 + 64, SRCPAINT);
		BitBlt(writeDC, x, y, 64, 64, blockDC, x1, y1, SRCAND);
	}
	if (++wall_time > wall_timemax)wall_time = 0;
	if (++water_time > water_timemax)water_time = 0;
}
//处理玩家炮弹
void PlayerBullet()
{
	for (vector<Bullet*>::iterator it_bullet = player_bullet.begin(); it_bullet != player_bullet.end();)
	{
		Bullet& bullet = **it_bullet;
		bullet.Move();
		bool erase_bullet = false;
		//炮弹是否越界
		if (bullet.x + 76 - 1 < 0 || bullet.x - 36 > GAME_W - 1 || bullet.y + 76 - 1 < 0 || bullet.y - 36 > GAME_H - 1)
		{
			delete* it_bullet;
			player_tank.set_bullet_num(player_tank.get_bullet_num() - 1);
			it_bullet = player_bullet.erase(it_bullet);
			erase_bullet = true;
		}
		//是否击中砖块
		else if (BulletHitBlock(bullet) == true)
		{
			if (sound)PLAYA(HIT);
			fire.push_back(new Fire(bullet.x - (66 - 40) / 2, bullet.y - (66 - 40) / 2));
			delete* it_bullet;
			player_tank.set_bullet_num(player_tank.get_bullet_num() - 1);
			it_bullet = player_bullet.erase(it_bullet);
			erase_bullet = true;
		}
		//是否击中敌人
		else
		{
			vector<BaseTank*>::iterator iter_tank;
			vector<vector<Bullet*>*>::iterator iter_enemy_bullet;
			for (iter_tank = enemy_tank.begin(), iter_enemy_bullet = enemy_bullet.begin();
				iter_tank != enemy_tank.end(); ++iter_tank, ++iter_enemy_bullet)
			{
				BaseTank& tank = **iter_tank;
				vector<Bullet*>& b = **iter_enemy_bullet;
				if (BulletHitTank(bullet, tank) == true)
				{
					fire.push_back(new Fire(bullet.x - (66 - 40) / 2, bullet.y - (66 - 40) / 2));
					tank.set_life(tank.get_life() - bullet.power + tank.get_armor());
					if (tank.get_life() <= 0)
					{
						//爆炸
						if (sound)PLAYA(BOMB);
						fire.push_back(new Fire(tank.get_x() - 1, tank.get_y() - 1));
						//添加道具
						switch (tank.get_id())
						{
						case GREEN:
							if (rand() % 7 == 0)
							{
								item = LIFE;
								item_x = tank.get_x();
								item_y = tank.get_y();
							}
							break;
						case BLUE:
							if (rand() % 2 == 0)
							{
								item = SPEED;
								item_x = tank.get_x();
								item_y = tank.get_y();
							}
							break;
						case RED:
							if (rand() % 2 == 0)
							{
								item = POWER;
								item_x = tank.get_x();
								item_y = tank.get_y();
							}
							break;
						case GOLD:
							if (rand() % 2 == 0)
							{
								item = WEAPON;
								item_x = tank.get_x();
								item_y = tank.get_y();
							}
						}
						delete* iter_tank;
						//先释放空间
						for (vector<Bullet*>::iterator it = b.begin(); it != b.end(); it++)
							delete* it;
						b.clear();
						delete* iter_enemy_bullet;
						iter_tank = enemy_tank.erase(iter_tank);
						iter_enemy_bullet = enemy_bullet.erase(iter_enemy_bullet);
						if (--enemy_num == 0 && enemy_rest == 0)
							wintime = wintimemax;
					}
					else if (sound) PLAYA(HIT);
					delete* it_bullet;
					player_tank.set_bullet_num(player_tank.get_bullet_num() - 1);
					it_bullet = player_bullet.erase(it_bullet);
					erase_bullet = true;
					break;
				}
				//是否击中敌人炮弹
				else
				{
					for (vector<Bullet*>::iterator it = b.begin(); it != b.end(); it++)
					{
						Bullet& bullet1 = **it;
						if (BulletHitBullet(bullet, bullet1) == true)
						{
							if (sound)PLAYA(HIT);
							fire.push_back(new Fire(bullet.x - (66 - 40) / 2, bullet.y - (66 - 40) / 2));
							delete* it_bullet;
							player_tank.set_bullet_num(player_tank.get_bullet_num() - 1);
							it_bullet = player_bullet.erase(it_bullet);
							erase_bullet = true;
							fire.push_back(new Fire(bullet1.x - (66 - 40) / 2, bullet1.y - (66 - 40) / 2));
							delete* it;
							tank.set_bullet_num(tank.get_bullet_num() - 1);
							it = b.erase(it);
							break;
						}
					}
					if (erase_bullet == true)
						break;
				}
			}
		}
		//若炮弹没有爆炸就绘制出来
		if (erase_bullet == false)
			(*(it_bullet++))->Draw(writeDC, bulletDC);
	}
}

//绘制草块
void DrawGrass()
{
	int i;
	int x;
	int y;
	int x1;
	int y1;
	for (vector<int>::iterator iter = block.begin(); iter != block.end(); ++iter)
		if (*iter == GRASS)
		{
			//草块绘制
			i = iter - block.begin();
			x = i % block_wide * 64;
			y = i / block_wide * 64;
			x1 = GRASS % 4 * 64;
			y1 = GRASS / 4 * 128;
			BitBlt(writeDC, x, y, 64, 64, blockDC, x1, y1 + 64, SRCPAINT);
			BitBlt(writeDC, x, y, 64, 64, blockDC, x1, y1, SRCAND);
		}
}
//绘制火花
void DrawFire()
{
	for (vector<Fire*>::iterator iter = fire.begin(); iter != fire.end();)
	{
		(*iter)->Draw(writeDC, fireDC);
		bool erase = false;
		if ((*iter)->end == true)
		{
			delete (*iter);
			iter = fire.erase(iter);
			erase = true;
		}
		if (erase == false)++iter;
	}
}
//炮弹击中砖块
bool BulletHitBlock(Bullet& bullet)
{
	int x = bullet.x;
	int y = bullet.y;
	x = (x + 20) / 64;
	y = (y + 20) / 64;
	if (x < 0 || y < 0 || x >= block_wide || y >= block_high)
		return false;
	int& id = *(block.begin() + y * block_wide + x);
	int id1 = id % 100;
	if (id1 == STONE)
	{
		//if(bullet.power==max_power)
		//	id=FLOOR;
		return true;
	}
	if (id1 == BASE)
	{
		if (sound)PLAYA(BOMB);
		fire.push_back(new Fire(x * 64, y * 64));
		id = FLOOR;
		base_time = base_timemax;
		return true;
	}
	if (id1 >= WALL + 3 && id1 <= WALLMAX)
	{
		id = FLOOR;
		return true;
	}
	if (id1 >= WALL && id1 <= WALL + 2)
	{
		id += bullet.power / 10;
		if (id > WALL + 3)id = FLOOR;
		return true;
	}
	return false;
}
//坦克碰撞砖块
bool TankHitBlock(BaseTank& tank)
{
	int x = tank.get_x() / 64;
	int y = tank.get_y() / 64;
	switch (tank.get_face())
	{
	case DOWN:
		++y;
		break;
	case LEFT:
		--x;
		break;
	case UP:
		--y;
		break;
	case RIGHT:
		++x;
	}
	if (x < 0 || y < 0 || x >= block_wide || y >= block_high)
		return true;
	int& id = *(block.begin() + y * block_wide + x);
	int id1 = id % 100;
	tank.set_speed_real(tank.get_speed());
	switch (id1)
	{
	case ICE:
		tank.set_speed_real(tank.get_speed_real() * 2);
		break;
	case SAND:
		tank.set_speed_real(1);
	}
	if (id1 == FLOOR || id1 == GRASS || id1 == ICE || id1 == SAND)
		return false;
	return true;
}
//炮弹击中坦克
bool BulletHitTank(Bullet& bullet, BaseTank& tank)
{
	int x1 = bullet.x + 20;
	int y1 = bullet.y + 20;
	int x2 = tank.get_x() + 32;
	int y2 = tank.get_y() + 32;
	if (abs(x1 - x2) < 32 && abs(y1 - y2) < 32)
		return true;
	return false;
}
//坦克碰撞坦克
bool TankHitTank(BaseTank& tank1, BaseTank& tank2)
{
	int x1 = tank1.get_x();
	int y1 = tank1.get_y();
	int x2 = tank2.get_x();
	int y2 = tank2.get_y();
	switch (tank1.get_face())
	{
	case DOWN:
		if ((x1 == x2 && y1 < y2 && y2 - y1 < 128 && y2 - y1 >= 64) || (y2 - y1 == 64 && abs(x1 - x2) < 64))
			return true;
		break;
	case LEFT:
		if ((y1 == y2 && x1 > x2 && x1 - x2 < 128 && x1 - x2 >= 64) || (x1 - x2 == 64 && abs(y1 - y2) < 64))
			return true;
		break;
	case UP:
		if ((x1 == x2 && y1 > y2 && y1 - y2 < 128 && y1 - y2 >= 64) || (y1 - y2 == 64 && abs(x1 - x2) < 64))
			return true;
		break;
	case RIGHT:
		if ((y1 == y2 && x1 < x2 && x2 - x1 < 128 && x2 - x1 >= 64) || (x2 - x1 == 64 && abs(y1 - y2) < 64))
			return true;
	}
	return false;
}
//炮弹碰撞炮弹
bool BulletHitBullet(Bullet& bullet1, Bullet& bullet2)
{
	int x1 = bullet1.x + 20;
	int y1 = bullet1.y + 20;
	int x2 = bullet2.x + 20;
	int y2 = bullet2.y + 20;
	switch (bullet1.face)
	{
	case DOWN:
	case UP:
		switch (bullet2.face)
		{
		case DOWN:
		case UP:
			if (abs(x1 - x2) < 20 && abs(y1 - y2) < 40)
				return true;
			break;
		case LEFT:
		case RIGHT:
			if (abs(x1 - x2) < 30 && abs(y1 - y2) < 30)
				return true;
			break;
		}
		break;
	case LEFT:
	case RIGHT:
		switch (bullet2.face)
		{
		case DOWN:
		case UP:
			if (abs(x1 - x2) < 30 && abs(y1 - y2) < 30)
				return true;
			break;
		case LEFT:
		case RIGHT:
			if (abs(x1 - x2) < 40 && abs(y1 - y2) < 20)
				return true;
		}
	}
	return false;
}
//处理和绘制敌人坦克
void EnemyTank()
{
	vector<BaseTank*>::iterator iter_tank;
	vector<vector<Bullet*>*>::iterator iter_bullet;
	//按顺序处理所有敌方坦克
	for (iter_tank = enemy_tank.begin(), iter_bullet = enemy_bullet.begin(); iter_tank != enemy_tank.end(); ++iter_tank, ++iter_bullet)
	{
		BaseTank& t = **iter_tank;
		//随机转动炮台
		int r = t.get_gun_face();
		if (t.get_gun_lock() == true && t.get_fire_step() == 0 && rand() % 50 == 0 || (((r == DOWN && GAME_H - t.get_y() == 64) || (r == LEFT && t.get_x() == 0) ||
			(r == UP && t.get_y() == 0) || (r == RIGHT && GAME_W - t.get_x() == 64)) && t.get_fire_step() == 0))
		{
			r = rand() % 4;
			t.set_gun_face(r);
			while ((r == DOWN && GAME_H - t.get_y() == 64) || (r == LEFT && t.get_x() == 0) ||
				(r == UP && t.get_y() == 0) || (r == RIGHT && GAME_W - t.get_x() == 64))
			{
				r = rand() % 4;
				t.set_gun_face(r);
			}
		}
		//开火
		if (t.get_gun_step() == 0 && t.get_bullet_num() < t.get_bullet_max() && rand() % 20 == 0)
		{
			//PLAYA(SHOOT)
			int x = t.get_x() + (64 - 40) / 2;
			int y = t.get_y() + (64 - 40) / 2;
			switch (t.get_gun_face())
			{
			case DOWN:
				y += 47;
				break;
			case LEFT:
				x -= 47;
				break;
			case UP:
				y -= 47;
				break;
			case RIGHT:
				x += 47;
			}
			(**iter_bullet).push_back(new Bullet(t.get_bullet_id(), 100, t.get_gun_face(), x, y,
				t.get_bullet_speed(), t.get_bullet_power()));
			t.set_bullet_num(t.get_bullet_num() + 1);
			t.Fire();
		}
		int oldface = t.get_face();
		//当步数减为零并且炮口闪光消失时随机生成移动方向和步数
		if (t.get_delay() > 0)
		{
			if (++t.move_step > 2)
				t.move_step = 0;
			t.set_delay(t.get_delay() - 1);
		}
		if (t.get_move() == 0 && t.get_delay() == 0)
		{
			r = t.get_face();
			if (t.get_fire_step() == 0 && rand() % 4 == 0 || (((r == DOWN && GAME_H - t.get_y() == 64) || (r == LEFT && t.get_x() == 0) ||
				(r == UP && t.get_y() == 0) || (r == RIGHT && GAME_W - t.get_x() == 64)) && t.get_fire_step() == 0))
			{
				r = rand() % 4;
				t.Change(r);
				while ((r == DOWN && GAME_H - t.get_y() == 64) || (r == LEFT && t.get_x() == 0) ||
					(r == UP && t.get_y() == 0) || (r == RIGHT && GAME_W - t.get_x() == 64))
				{
					r = rand() % 4;
					t.Change(r);
				}

			}
			t.set_move(64 / t.get_speed());
			//撞到砖块
			if (TankHitBlock(t) == true)
			{
				t.set_move(0);
				t.set_delay(5);
			}
			//撞到玩家坦克
			else if (player_death == false && TankHitTank(t, player_tank) == true)
			{
				//t.Change(oldface);
				t.set_move(0);
				t.set_delay(5);
			}
			//如果撞到敌方任意非己坦克……
			else
			{
				for (vector<BaseTank*>::iterator i = enemy_tank.begin(); i != enemy_tank.end(); ++i)
					//如果不是自己本身并且撞到对方
					if (i != iter_tank && TankHitTank(t, **i) == true)
					{
						//t.Change(oldface);
						t.set_move(0);
						break;
					}
			}
			if (t.get_move() > 0)
				t.set_move(64 / t.get_speed_real());
		}
		if (t.get_move() > 0)
		{
			t.set_move(t.get_move() - 1);
			if (++t.move_step > 2)
				t.move_step = 0;
			t.Move();
		}
		t.Draw(writeDC, player_tankDC, false);
	}
}
//处理和绘制敌人炮弹和炮口闪光
void EnemyBullet()
{
	vector<BaseTank*>::iterator iter_tank;
	vector<vector<Bullet*>*>::iterator iter_bullet;
	//按顺序处理所有敌方坦克炮弹
	for (iter_tank = enemy_tank.begin(), iter_bullet = enemy_bullet.begin();
		iter_tank != enemy_tank.end(); ++iter_tank, ++iter_bullet)
	{
		BaseTank& tank = **iter_tank;
		vector<Bullet*>& b = **iter_bullet;
		for (vector<Bullet*>::iterator it = b.begin(); it != b.end();)
		{
			Bullet& bullet = **it;
			bullet.Move();
			int x = bullet.x;
			int y = bullet.y;
			bool erase = false;
			//炮弹是否越界
			if (bullet.x + 76 - 1 < 0 || bullet.x - 36 > GAME_W - 1 || bullet.y + 76 - 1 < 0 || bullet.y - 36 > GAME_H - 1)
			{
				delete* it;
				tank.set_bullet_num(tank.get_bullet_num() - 1);
				it = b.erase(it);
				erase = true;
			}
			//击中砖块
			else if (BulletHitBlock(bullet) == true)
			{
				//PLAYA(HIT)
				fire.push_back(new Fire(bullet.x - (66 - 40) / 2, bullet.y - (66 - 40) / 2));
				delete* it;
				tank.set_bullet_num(tank.get_bullet_num() - 1);
				it = b.erase(it);
				erase = true;
			}
			//击中玩家
			else if (player_death == false && BulletHitTank(bullet, player_tank) == true)
			{
				fire.push_back(new Fire(bullet.x - (66 - 40) / 2, bullet.y - (66 - 40) / 2));
				player_tank.set_life(player_tank.get_life() - bullet.power + player_tank.get_armor());
				//玩家颜色改变									
				if (player_tank.get_life() <= 0)
				{
					//玩家死亡
					if (sound)PLAYA(BOMB);
					fire.push_back(new Fire(player_tank.get_x() - 1, player_tank.get_y() - 1));
					player_death = true;
					--player_num;
					player_time = player_timemax;
				}
				else
					player_tank.set_id(player_tank.get_life() / 10 - 1);
				delete* it;
				tank.set_bullet_num(tank.get_bullet_num() - 1);
				it = b.erase(it);
				erase = true;
			}
			//若炮弹没有爆炸就绘制出来
			if (erase == false)
				(*it++)->Draw(writeDC, bulletDC);
		}
		//绘制炮口闪光
		tank.Draw(writeDC, player_tankDC, true);
	}
}
//处理和绘制道具
void Item()
{
	if (item != NONE)
	{
		BitBlt(writeDC, item_x, item_y, 64, 64, blockDC, item * 64, 768 + 64, SRCPAINT);
		BitBlt(writeDC, item_x, item_y, 64, 64, blockDC, item * 64, 768, SRCAND);
		if (player_death == false && abs(player_tank.get_x() - item_x) <= 32 && abs(player_tank.get_y() - item_y) <= 32)
		{
			switch (item)
			{
				//坦克生命
			case LIFE:
				if (player_tank.get_life() < max_life)
				{
					player_tank.set_life(player_tank.get_life() + 10);
					player_tank.set_id(player_tank.get_life() / 10 - 1);
				}
				break;
				//子弹射速
			case POWER:
				if (player_tank.get_bullet_speed() < max_bullet_speed)
				{
					player_tank.set_fire_speed(player_tank.get_fire_speed() + 2);
					player_tank.set_bullet_speed(player_tank.get_bullet_speed() + 4);
				}
				break;
				//坦克速度
			case SPEED:
				if (player_tank.get_speed() < max_speed)
				{
					player_tank.set_speed(player_tank.get_speed() + 1);
				}
				break;
				//武器弹数
			case WEAPON:
				if (player_tank.get_bullet_max() < max_num)
					player_tank.set_bullet_max(player_tank.get_bullet_max() + 1);
			}
			item = NONE;
		}
	}
}

