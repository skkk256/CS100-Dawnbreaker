#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "WorldBase.h"

class GameObject : public ObjectBase {
private:
	bool isDestroyed;
public:
	GameObject(int imageID, int x, int y, int direction, int layer, double size);
	void DestroyIt();
	virtual bool IsEnemy() = 0;
	bool JudgeDestroyed() const;
};

class Projectile : public GameObject {
private:
	int hurt;
	bool isRed = false;
public:
	Projectile(int x, int y, double size, int hurt, bool isred);
	Projectile(int x, int y, double size, int hurt);
	void Update();
	bool IsEnemy() override;
};

class Dawnbreaker : public GameObject {
private:
	int HP;
	int energy;
	int upgradeTimes = 1;
	WorldBase* theWorld;
	int shoot = 0;
public:
	Dawnbreaker(int x, int y, WorldBase* worldptr);
	void Update();
	bool IsEnemy() override;
	int NeedShoot();
	void Upgrade();
	int GetUpgrade() const;
	void SetHP(int hp);
};

class Star : public GameObject {
private:

public:
	Star(int x, int y, double size);
	bool IsEnemy() override;
	void Update();
};
#endif // GAMEOBJECTS_H__