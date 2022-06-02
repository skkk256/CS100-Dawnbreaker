#include "Enemy.h"
#include "utils.h"

//Enemy
Enemy::Enemy(const int IMGID, int x, int y, int HP, int aggressivity, int speed, int energy) : 
	GameObject(IMGID, x, y, 180, 0, 1.0), HP(HP), aggressivity(aggressivity), speed(speed), energy(energy) {}

bool Enemy::IsEnemy() {
	return true;
}

int Enemy::NeedShoot(){
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


Alphatron::Alphatron(int x, int y, int HP, int agresivity, int speed) : 
	Enemy(IMGID_ALPHATRON, x, y, HP, agresivity, speed, 25) {}

//Alphatron
void Alphatron::Update() {
	//�ƻ����
	if (JudgeDestroyed()) return;
	//�Ƿ���Ҫ�ƻ�
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.��ײ���
	
	//4.����
	
	//5.�����ظ�
	if (GetEnergy() < 25) SetEnergy(GetEnergy() + 1);
	//6.���в���
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
	//7.����
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
