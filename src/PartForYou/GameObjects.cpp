#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"

//GameObject
GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size) : 
	ObjectBase(imageID, x, y, direction, layer, size), isDestroyed(false) {}

void GameObject::DestroyIt() {
	isDestroyed = true;
}

bool GameObject::JudgeDestroyed() const {
	return isDestroyed;
}

//star
Star::Star(int x, int y, double size) : GameObject(IMGID_STAR, x, y, 0, 4, size) {}

bool Star::IsEnemy() {
	return false;
}

void Star::Update() {
	if (JudgeDestroyed()) return;
	if (this->GetY() < 0) {
		DestroyIt();
		return;
	}
	MoveTo(GetX(), GetY() - 1);
}

int Star::GetType() const
{
	return star;
}


//Dawnbreaker
Dawnbreaker::Dawnbreaker(int x, int y, WorldBase* worldptr) : 
	GameObject(IMGID_DAWNBREAKER, x, y, 0, 0, 1.0), HP(100), energy(10), theWorld(worldptr) {}

bool Dawnbreaker::IsEnemy() {
	return false;
}

int Dawnbreaker::NeedShoot() {
	int temp = shoot;
	shoot = 0;
	return temp;
}

void Dawnbreaker::Upgrade() {
	upgradeTimes += 1;
}

int Dawnbreaker::GetUpgrade() const{
	return upgradeTimes;
}

void Dawnbreaker::SetHP(int hp) {
	HP = hp;
}

int Dawnbreaker::GetHP() const {
	return HP;
}

int Dawnbreaker::GetType() const
{
	return player;
}

void Dawnbreaker::IncreaseMeteors()
{
	meteors += 1;
}

int Dawnbreaker::GetMeteors() const
{
	return meteors;
}

void Dawnbreaker::Update() {
	if (JudgeDestroyed()) return;
	if (HP <= 0) {
		DestroyIt();
		return;
	}
	if (energy < 10) energy += 1;
	if ((GameWorld*)theWorld->GetKey(KeyCode::UP)) {
		if (GetY() + 5 <= WINDOW_HEIGHT - 1)
			MoveTo(GetX(), GetY() + 4);
	}
	if (theWorld->GetKey(KeyCode::DOWN)) {
		if (GetY() - 4 >= 50)
			MoveTo(GetX(), GetY() - 4);
	}
	if (theWorld->GetKey(KeyCode::LEFT)) {
		if (GetX() - 4 >= 0)
			MoveTo(GetX() - 4, GetY());
	}
	if (theWorld->GetKey(KeyCode::RIGHT)) {
		if (GetX() + 4 <= WINDOW_WIDTH - 1)
			MoveTo(GetX() + 4, GetY());
	}
	shoot = 0;
	if (theWorld->GetKey(KeyCode::FIRE1) && energy >= 10) {
		energy -= 10;
		shoot = 1;
	}
	if (theWorld->GetKeyDown(KeyCode::FIRE2) && meteors >= 1) {
		meteors -= 1;
		shoot = 2;
	}
}

//Explosion
Explosion::Explosion(int x, int y) :
	GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5), trick(1) {}

void Explosion::Update() {
	if (trick == 20) {
		DestroyIt();
		return;
	}
	trick += 1;
	SetSize(GetSize() - 0.2);
}

bool Explosion::IsEnemy()
{
	return false;
}

int Explosion::GetType() const
{
	return explosion;
}
