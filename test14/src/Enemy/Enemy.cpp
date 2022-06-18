#include "Enemy.h"
#include "utils.h"
#include "Projectile.h"
#include "Tools.h"
#include <cmath>

//Enemy
Enemy::Enemy(const int IMGID, int x, int y, int HP, int aggressivity, int speed, int energy, GameWorld* worldptr) :
	GameObject(IMGID, x, y, 180, 0, 1.0), HP(HP), aggressivity(aggressivity), speed(speed), energy(energy), theWorld(worldptr) {}

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

int Enemy::GetAgreesivity() const {
	return aggressivity;
}

bool Enemy::CollDetect() {
	Dawnbreaker* player = theWorld->GetDawnbreaker();
	if (theWorld->DetectPlayer(this, enemy)) {
		return true;
	}
	if (int hurt = theWorld->DetectHurt(this)) {
		SetHP(GetHP() - hurt);
		if (GetHP() <= 0) {
			theWorld->AddIn(new Explosion(GetX(), GetY()));
			DestroyIt();
			theWorld->IncreasDestroyed(1);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Enemy::SetHP(int hp) {
	HP = hp;
}

//Alphatron
Alphatron::Alphatron(int x, int y, int HP, int agresivity, int speed, GameWorld* worldptr) :
	Enemy(IMGID_ALPHATRON, x, y, HP, agresivity, speed, 25, worldptr) {}

int Alphatron::GetType() const {
	return alpha;
}

void Alphatron::Update() {
	Dawnbreaker* player = theWorld->GetDawnbreaker();
	//�ƻ����
	if (JudgeDestroyed()) return;
	//�Ƿ���Ҫ�ƻ�
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.��ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(50);
		return;
	}
	//4.����
	SetShoot(0);
	if ((player->GetX() - GetX() <= 10 && player->GetX() - this->GetX() >= -10) && GetEnergy() >= 25) {
		if (randInt(1, 4) == 1) {
			SetShoot(1);
			SetEnergy(GetEnergy() - 25);
		}
	}
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
	//�ٴ���ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(50);
		return;
	}
}

//Sigmatron
Sigmatron::Sigmatron(int x, int y, int HP, int speed, GameWorld* worldptr) :
	Enemy(IMGID_SIGMATRON, x, y, HP, 0, speed, 0, worldptr) {}


int Sigmatron::GetType() const {
	return sigma;
}


void Sigmatron::Update() {
	Dawnbreaker* player = theWorld->GetDawnbreaker();
	//�ƻ����
	if (JudgeDestroyed()) return;
	//�Ƿ���Ҫ�ƻ�
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.��ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(100);
		if (randInt(1, 5) == 1) {
			theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::HP_T, IMGID_HP_RESTORE_GOODIE, theWorld));
		}
		return;
	}
	//4.����
	if (player->GetX() - this->GetX() <= 10 && player->GetX() - this->GetX() >= -10) {
		SetFlightStrategy(2);
		SetFlightTime(WINDOW_HEIGHT);
		SetSpeed(10);
		SetShoot(1);
	}
	//6.���в���
	if (GetFlightTime() == 0 && NeedShoot() != 1) {
		SetFlightStrategy(randInt(1, 3));
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() < 0 && NeedShoot() != 1) {
		SetFlightStrategy(3);
		SetFlightTime(randInt(10, 50));
	}
	if (GetX() >= WINDOW_WIDTH && NeedShoot() != 1) {
		SetFlightStrategy(1);
		SetFlightTime(randInt(10, 50));
	}
	//7.����
	if (NeedShoot() != 1) {
		SetFlightTime(GetFlightTime() - 1);
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
	//8.�ٴ���ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(100);
		if (randInt(1, 5) == 1) {
			theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::HP_T, IMGID_HP_RESTORE_GOODIE, theWorld));
		}
		return;
	}
}

//Omegatron
Omegatron::Omegatron(int x, int y, int HP, int agresivity, int speed, GameWorld* worldptr) :
	Enemy(IMGID_OMEGATRON, x, y, HP, agresivity, speed, 50, worldptr) {}

int Omegatron::GetType() const {
	return omega;
}

void Omegatron::Update() {
	Dawnbreaker* player = theWorld->GetDawnbreaker();
	//�ƻ����
	if (JudgeDestroyed()) return;
	//�Ƿ���Ҫ�ƻ�
	if (GetHP() == 0 || GetY() < 0) {
		DestroyIt();
		return;
	}
	//3.��ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(200);
		int probability = randInt(1, 5);
		if (probability == 1 ||  probability == 2) {
			if (randInt(1, 5) == 1) {
				theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::M_T, IMGID_METEOR_GOODIE, theWorld));
			}
			else {
				theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::U_T, IMGID_POWERUP_GOODIE, theWorld));
			}
		}
		return;
	}
	//4.����
	SetShoot(0);
	if (GetEnergy() >= 50) {
		SetShoot(1);
		SetEnergy(GetEnergy() - 50);
	}
	//5.�����ظ�
	if (GetEnergy() < 50) SetEnergy(GetEnergy() + 1);
	//6.���в���
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
	//7.����
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
	//�ٴ���ײ���
	if (CollDetect()) {
		theWorld->IncreaseScore(200);
		int probability = randInt(1, 5);
		if (probability == 1 || probability == 2) {
			if (randInt(1, 5) == 1) {
				theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::M_T, IMGID_METEOR_GOODIE, theWorld));
			}
			else {
				theWorld->AddIn(new Tools(GetX(), GetY(), GameObject::U_T, IMGID_POWERUP_GOODIE, theWorld));
			}
		}
		return;
	}
}
