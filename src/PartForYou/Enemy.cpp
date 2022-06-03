#include "Enemy.h"
#include "utils.h"

//Enemy
Enemy::Enemy(const int IMGID, int x, int y, int HP, int aggressivity, int speed, int energy, Dawnbreaker* player) :
	GameObject(IMGID, x, y, 180, 0, 1.0), HP(HP), aggressivity(aggressivity), speed(speed), energy(energy), player(player) {}

bool Enemy::IsEnemy() {
	return true;
}

void Enemy::SetShoot(int flag)
{
	shoot = flag;
}

int Enemy::NeedShoot() const {
	return shoot;
}

void Enemy::SetFlightTime(int t)
{
	flightTime = t;
}

void Enemy::SetFlightStrategy(int way)
{
	flightStrategy = way;
}

int Enemy::GetFlightTime() const
{
	return flightTime;
}

int Enemy::GetFlightStrategy() const
{
	return flightStrategy;
}

int Enemy::GetHP() const {
	return HP;
}

int Enemy::GetEnergy() const
{
	return energy;
}

void Enemy::SetEnergy(int m_energy)
{
	energy = m_energy;
}

int Enemy::GetSpeed() const
{
	return speed;
}

void Enemy::SetSpeed(int m_speed) {
	speed = m_speed;
}

int Enemy::GetAgreesivity()
{
	return aggressivity;
}

void Enemy::SetHP(int hp) {
	HP = hp;
}


Alphatron::Alphatron(int x, int y, int HP, int agresivity, int speed, Dawnbreaker* player) :
	Enemy(IMGID_ALPHATRON, x, y, HP, agresivity, speed, 25, player) {}

//Alphatron
int Alphatron::GetType() const
{
	return alpha;
}

void Alphatron::Update() {
	//破坏检测
	if (JudgeDestroyed()) return;
	//是否需要破环
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.碰撞检查
	
	//4.攻击
	SetShoot(0);
	if ((player->GetX() - GetX() <= 10 && player->GetX() - this->GetX() >= -10) && GetEnergy() >= 25) {
		if (randInt(1, 4) == 1) {
			SetShoot(1);
			SetEnergy(GetEnergy() - 25);
		}
	}
	//5.能量回复
	if (GetEnergy() < 25) SetEnergy(GetEnergy() + 1);
	//6.飞行策略
	if (GetFlightTime() == 0) {
		SetFlightStrategy(randInt(1,3));
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() < 0) {
		SetFlightStrategy(3);
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() >= WINDOW_WIDTH) {
		SetFlightStrategy(1);
		SetFlightTime(randInt(10, 50));
	}
	//7.飞行
	SetFlightTime(GetFlightTime() - 1);
	switch (GetFlightStrategy())
	{
	default:
		break;
	case 1:
		MoveTo(GetX() - GetSpeed(), GetY() - GetSpeed());
		break;
	case 2:
		MoveTo(GetX(), GetY() - GetSpeed());
		break;
	case 3:
		MoveTo(GetX() + GetSpeed(), GetY() - GetSpeed());
		break;
	}
}

//Sigmatron
Sigmatron::Sigmatron(int x, int y, int HP, int speed, Dawnbreaker* player) :
	Enemy(IMGID_SIGMATRON, x, y, HP, 0, speed, 0, player) {}


int Sigmatron::GetType() const
{
	return sigma;
}


void Sigmatron::Update() {
	//破坏检测
	if (JudgeDestroyed()) return;
	//是否需要破环
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.碰撞检查
	// 
	//4.攻击
	SetShoot(0);
	if (player->GetX() - this->GetX() <= 10 && player->GetX() - this->GetX() >= -10) {
		SetFlightStrategy(2);
		SetSpeed(10);
		SetShoot(1);
	}
	//6.飞行策略
	if (GetFlightTime() == 0) {
		SetFlightStrategy(randInt(1, 3));
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() < 0) {
		SetFlightStrategy(3);
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() >= WINDOW_WIDTH) {
		SetFlightStrategy(1);
		SetFlightTime(randInt(10, 50));
	}
	//7.飞行
	if (NeedShoot() != 1) {
		SetFlightTime(GetFlightTime() - 1);
	}
	else {
		SetFlightTime(99);
	}
	switch (GetFlightStrategy())
	{
	default:
		break;
	case 1:
		MoveTo(GetX() - GetSpeed(), GetY() - GetSpeed());
		break;
	case 2:
		MoveTo(GetX(), GetY() - GetSpeed());
		break;
	case 3:
		MoveTo(GetX() + GetSpeed(), GetY() - GetSpeed());
		break;
	}
}

//Omegatron
Omegatron::Omegatron(int x, int y, int HP, int agresivity, int speed, Dawnbreaker* player) :
	Enemy(IMGID_OMEGATRON, x, y, HP, agresivity, speed, 50, player) {}

int Omegatron::GetType() const
{
	return omega;
}

void Omegatron::Update() {
	//破坏检测
	if (JudgeDestroyed()) return;
	//是否需要破环
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.碰撞检查

	//4.攻击
	SetShoot(0);
	if (GetEnergy() >= 50) {
		SetShoot(1);
		SetEnergy(GetEnergy() - 50);
	}
	//5.能量回复
	if (GetEnergy() < 50) SetEnergy(GetEnergy() + 1);
	//6.飞行策略
	if (GetFlightTime() == 0) {
		SetFlightStrategy(randInt(1, 3));
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() < 0) {
		SetFlightStrategy(3);
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() >= WINDOW_WIDTH) {
		SetFlightStrategy(1);
		SetFlightTime(randInt(10, 50));
	}
	//7.飞行
	SetFlightTime(GetFlightTime() - 1);
	switch (GetFlightStrategy())
	{
	default:
		break;
	case 1:
		MoveTo(GetX() - GetSpeed(), GetY() - GetSpeed());
		break;
	case 2:
		MoveTo(GetX(), GetY() - GetSpeed());
		break;
	case 3:
		MoveTo(GetX() + GetSpeed(), GetY() - GetSpeed());
		break;
	}
}
