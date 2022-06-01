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
	void DecreaseHD();
	void IncreaseHD();
	bool JudgeDestroyed() const;
};

class Enemy : public GameObject {

};

class Projectile : public GameObject {

};

class Dawnbreaker : public GameObject {
private:
	int HP;
	int energy;
	WorldBase* theWorld;
public:
	Dawnbreaker(int x, int y, WorldBase* worldptr);
	bool IsEnemy() override;
	void Update();
};

class Star : public GameObject {
private:

public:
	Star(int x, int y, double size);
	bool IsEnemy() override;
	void Update();
};
#endif // GAMEOBJECTS_H__