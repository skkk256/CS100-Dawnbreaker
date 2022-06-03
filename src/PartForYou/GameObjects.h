#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "WorldBase.h"

class GameObject : public ObjectBase {
private:
	bool isDestroyed;
public:
	enum { player, alpha, sigma, omega, proj, tool, star };
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
	int GetType() const override;
};

class Star : public GameObject {
private:

public:
	Star(int x, int y, double size);
	bool IsEnemy() override;
	void Update();
	int GetType() const override;
};
#endif // GAMEOBJECTS_H__