#pragma once
#include <Windows.h>

#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3

class BaseTank
{
private:
	int id;
	int life;
	int armor;
	int face;
	int x;
	int y;
	int gun_face;
	bool gun_lock;
	int delay;
	int bullet_id;
	int bullet_num;
	int bullet_speed;
	int gun_step;
	int fire_speed;
	int speed;
	int move;
	int speed_real;
	int bullet_max;
	int bullet_power;
	int fire_step;
public:
	int move_step;
	void set_id(int ID) { id = ID; }
	void set_life(int LIFE) { life = LIFE; }
	void set_armor(int ARMOR) { armor = ARMOR; }
	void set_face(int FACE) { face = FACE; }
	void set_x(int X) { x = X; }
	void set_y(int Y) { y = Y; }
	void set_fire_step(int FIRE_STEP) { fire_step = FIRE_STEP; }
	void set_bullet_max(int BULLET_MAX) { bullet_max = BULLET_MAX; }
	void set_gun_face(int GUN_FACE) { gun_face = GUN_FACE; }
	void set_gun_lock(bool LOCK) { gun_lock = LOCK; }
	void set_delay(int DELAY) { delay = DELAY; }
	void set_move(int MOVE) { move = MOVE; }
	void set_fire_speed(int FIRE_SPEED) { fire_speed = FIRE_SPEED; }
	void set_bullet_id(int BULLET_ID) { bullet_id = BULLET_ID; }
	void set_bullet_num(int BULLET_NUM) { bullet_num = BULLET_NUM; }
	void set_gun_step(int GUN_STEP) { gun_step = GUN_STEP; }
	void set_speed(int SPEED) { speed = SPEED; }
	void set_bullet_speed(int BULLET_SPEED) { bullet_speed = BULLET_SPEED; }
	void set_speed_real(int SPEED_REAL) { speed_real = SPEED_REAL; }
	void set_bullet_power(int BULLET_POWER) { bullet_power = BULLET_POWER; }
	int get_id() { return id; }
	int get_bullet_power() { return bullet_power; }
	int get_speed() { return speed; }
	int get_move() { return move; }
	int get_life() { return life; }
	int get_armor() { return armor; }
	int get_face() { return face; }
	int get_x() { return x; }
	int get_bullet_max() { return bullet_max; }
	int get_speed_real() { return speed_real; }
	int get_y() { return y; }
	int get_gun_face() { return gun_face; }
	bool get_gun_lock() { if (gun_lock) return true; else return false; }
	int get_delay() { return delay; }
	int get_bullet_id() { return bullet_id; }
	int get_bullet_num() { return bullet_num; }
	int get_fire_speed() { return fire_speed; }
	int get_gun_step() { return gun_step; }
	int get_bullet_speed() { return bullet_speed; }
	int get_fire_step() { return fire_step; }
	BaseTank(
		int _id = 0,
		int _life = 20,
		int _armor = 0,
		int _face = DOWN,
		int _x = 0,
		int _y = 0,
		int _gun_face = DOWN,
		bool _gun_lock = false,
		int _move = 32,
		int _speed = 2,
		int _fire_speed = 2,
		int _bullet_id = 0,
		int _bullet_max = 1,
		int _bullet_power = 10,
		int _bullet_speed = 5);
	~BaseTank();
	void Move();
	void Change(int _face);
	void Fire();
	void Death();
	void Draw(HDC&, HDC&, bool);
};
