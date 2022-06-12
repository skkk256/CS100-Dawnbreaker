#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "WorldBase.h"

class GameObject : public ObjectBase {
private:
	bool isDestroyed;
public:
	enum type{ player, alpha, sigma, omega, proj, bproj, tool, star, explosion, HP_T, M_T, U_T, Meter, enemy };
	GameObject(int imageID, int x, int y, int direction, int layer, double size);
	void DestroyIt();
	virtual bool IsEnemy() = 0;
	virtual int GetType() const = 0;
	bool JudgeDestroyed() const;
};

class Dawnbreaker : public GameObject {
private:
	int HP;
	int energy;
	int upgradeTimes = 0;
	int meteors = 0;
	int shoot = 0;
	WorldBase* theWorld;
public:
	Dawnbreaker(int x, int y, WorldBase* worldptr);
	void Update() override;
	bool IsEnemy() override;
	int NeedShoot();
	void Upgrade();
	int GetUpgrade() const;
	void SetHP(int hp);
	int GetHP() const;
	int GetType() const override;
	void IncreaseMeteors();
	int GetMeteors() const;
};

class Star : public GameObject {
public:
	Star(int x, int y, double size);
	bool IsEnemy() override;
	void Update() override;
	int GetType() const override;
};

class Explosion : public GameObject {
private:
	int trick;
public:
	Explosion(int x, int y);
	void Update() override;
	bool IsEnemy() override;
	int GetType() const override;
};


#endif // GAMEOBJECTS_H__