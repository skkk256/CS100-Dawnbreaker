#include "GameObjects.h"
#include "GameWorld.h"
#include "utils.h"

//GameObject
GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size) : 
	ObjectBase(imageID, x, y, direction, layer, size), isDestroyed(false) {}

void GameObject::DestroyIt() {
	isDestroyed = true;
}

void GameObject::DecreaseHD() {

}

void GameObject::IncreaseHD() {

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
	if (this->GetY() < 0) DestroyIt();
	MoveTo(GetX(), GetY() - 1);
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

}

int Dawnbreaker::GetUpgrade() const{
	return upgradeTimes;
}

void Dawnbreaker::Update() {
	if (JudgeDestroyed()) return;
	if (HP == 0) DestroyIt();
	if (energy < 10) energy += 1;
	if (theWorld->GetKey(KeyCode::UP)) {
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
	if (theWorld->GetKey(KeyCode::FIRE1) && energy >= 10) {
		energy -= 10;
		shoot = 1;
	}
}

//projectile
bool Projectile::IsEnemy() {
	return isRed;
}

Projectile::Projectile(int x, int y, double size, int hurt, bool isred) :
	GameObject(IMGID_RED_BULLET, x, y, 0, 1, size), hurt(hurt), isRed(isred) {}

Projectile::Projectile(int x, int y, double size, int hurt) : 
	GameObject(IMGID_BLUE_BULLET, x, y, 0, 1, size), hurt(hurt) {}

void Projectile::Update(){
	if (JudgeDestroyed()) return;
	if (this->GetY() > WINDOW_HEIGHT - 1) DestroyIt();
	MoveTo(GetX(), GetY() + 6);
}

