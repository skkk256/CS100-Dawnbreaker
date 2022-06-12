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

Projectile::Projectile(const int IMGID, int x, int y, int direction, double size, int hurt, bool isred, GameWorld* worldptr) :
	GameObject(IMGID, x, y, direction, 1, size), hurt(hurt), isRed(isred), theWorld(worldptr) {}

int Projectile::GetFlightStrategy() const
{
	return flightStrategy;
}

void Projectile::SetFlightStrategy(int way)
{
	flightStrategy = way;
}


void Projectile::Update() {
	Dawnbreaker* player = theWorld->GetDawnbreaker();
	if (JudgeDestroyed()) return;
	if ((GetY() > WINDOW_HEIGHT - 1 && !(isRed)) || (GetY() < 0 && isRed)) {
		DestroyIt();
		return;
	}
	//Åö×²¼ì²â
	if (IsEnemy()) {
		if (theWorld->Detect(this, GameObject::player)) {
			player->SetHP(player->GetHP() - GetHurt());
			DestroyIt();
			return;
		}
	}
	else {
		if (int type = theWorld->Detect(this, enemy)) {
			switch (type)
			{
			case GameObject::alpha:
				theWorld->IncreaseScore(50);
				theWorld->IncreasDestroyed(1);
				break;
			case GameObject::sigma:
				theWorld->IncreaseScore(100);
				theWorld->IncreasDestroyed(1);
				break;
			case GameObject::omega:
				theWorld->IncreaseScore(200);
				theWorld->IncreasDestroyed(1);
				break;
			default:
				break;
			}
		}
	}
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
	//ÔÙ´ÎÅö×²¼ì²â
	if (IsEnemy()) {
		if (theWorld->Detect(this, GameObject::player)) {
			player->SetHP(player->GetHP() - GetHurt());
			DestroyIt();
			return;
		}
	}
	else {
		if (int type = theWorld->Detect(this, enemy)) {
			switch (type)
			{
			case GameObject::alpha:
				theWorld->IncreaseScore(50);
				theWorld->IncreasDestroyed(1);
				break;
			case GameObject::sigma:
				theWorld->IncreaseScore(100);
				theWorld->IncreasDestroyed(1);
				break;
			case GameObject::omega:
				theWorld->IncreaseScore(200);
				theWorld->IncreasDestroyed(1);
				break;
			default:
				break;
			}
		}
	}
}