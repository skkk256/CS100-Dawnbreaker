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

int Projectile::GetHurt() const
{
	return hurt;
}

Projectile::Projectile(const int IMGID, int x, int y, int direction, double size, int hurt, bool isred, Dawnbreaker* player) :
	GameObject(IMGID, x, y, direction, 1, size), hurt(hurt), isRed(isred), player(player) {}

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
	//Åö×²¼ì²â

	//ÒÆ¶¯
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