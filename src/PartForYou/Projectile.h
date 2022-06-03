#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include "GameObjects.h"
#include "GameWorld.h"
#include <list>

class Projectile : public GameObject {
private:
	int hurt;
	bool isRed = false;
	int flightStrategy = 0;
public:
	Projectile(const int IMGID, int x, int y, int direction, double size, int hurt, bool isred);
	int GetFlightStrategy() const;
	void SetFlightStrategy(int way);
	void Update();
	bool IsEnemy() override;
	int GetType() const override;
};

#endif // !PROJECTILE_H__