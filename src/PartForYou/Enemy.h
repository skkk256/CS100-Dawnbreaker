#ifndef ENEMY_H__
#define ENEMY_H__
#include "GameObjects.h"

class Enemy : public GameObject {
private:
	int HP;
	int aggressivity;
	int speed;
	int energy;
	int flightTime = 0;
	int flightStrategy = 0;
	int shoot = 0;
public:
	Enemy(const int IMGID, int x, int y, int HP, int aggressivity, int speed, int energy);
	bool IsEnemy() override;
	int NeedShoot();
	void SetFlightTime(int t);
	void SetFlightStrategy(int way);
	int GetFlightTime() const;
	int GetFlightStrategy() const;
	int GetHP() const;
	void SetHP(int m_hp);
	int GetEnergy() const;
	void SetEnergy(int m_energy);
	int GetSpeed() const;
	void SetSpeed(int m_speed);
	int GetAgreesivity();


};

class Alphatron : public Enemy {
public:
	Alphatron(int x, int y, int HP, int agresivity, int speed);
	void Update() override;
};

#endif
