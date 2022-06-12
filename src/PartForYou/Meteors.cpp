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
		}
	}
	MoveTo(GetX(), GetY() + 2);
	SetDirection((GetDirection() + 5) % 360);
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
		}
	}
}

bool Meteors::IsEnemy()
{
	return false;
}

int Meteors::GetType() const
{
	return GameObject::Meter;
}
