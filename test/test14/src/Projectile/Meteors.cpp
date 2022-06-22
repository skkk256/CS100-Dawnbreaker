#include "Meteors.h"
#include "utils.h"

Meteors::Meteors(int x, int y, GameWorld* worldptr) :
	GameObject(IMGID_METEOR, x, y, 0, 1, 2.0), theWorld(worldptr), type(Meter) {}

void Meteors::Update()
{
	if (JudgeDestroyed()) return;
	if (this->GetY() >= WINDOW_HEIGHT) {
		DestroyIt();
		return;
	}
	//Åö×²¼ì²â
	if (int type = theWorld->DetectEnemy(this, Meter)) { return; }
	MoveTo(GetX(), GetY() + 2);
	SetDirection((GetDirection() + 5) % 360);
	//ÔÙ´ÎÅö×²¼ì²â
	if (int type = theWorld->DetectEnemy(this, Meter)) { return; }
}

bool Meteors::IsEnemy()
{
	return false;
}

int Meteors::GetType() const
{
	return GameObject::Meter;
}
