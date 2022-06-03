#include "Projectile.h"
#include "utils.h"

//projectile
bool Projectile::IsEnemy() {
	return isRed;
}

int Projectile::GetType() const
{
	return proj;
}

Projectile::Projectile(const int IMGID, int x, int y, int direction, double size, int hurt, bool isred) :
	GameObject(IMGID, x, y, direction, 1, size), hurt(hurt), isRed(isred) {}

int Projectile::GetFlightStrategy() const
{
	return flightStrategy;
}

void Projectile::SetFlightStrategy(int way)
{
	flightStrategy = way;
}


void Projectile::Update() {
	if (JudgeDestroyed()) return;
	if ((GetY() > WINDOW_HEIGHT - 1 && !(isRed)) || (GetY() < 0 && isRed)) {
		DestroyIt();
		return;
	}
	switch (flightStrategy)
	{
	case 0:
		MoveTo(GetX(), GetY() + 6);
		break;
	case 1:
		MoveTo(GetX() - 2, GetY() - 6);
		break;
	case 2:
		MoveTo(GetX(), GetY() - 6);
		break;
	case 3:
		MoveTo(GetX() + 2, GetY() - 6);
		break;
	}
}