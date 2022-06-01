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
Star::Star(int x, int y, double size) : GameObject(IMGID_STAR, x, y, 0, 0, size) {}

bool Star::IsEnemy() {
	return false;
}

void Star::Update() {
	if (this->GetY() < 0) DestroyIt();
	if (JudgeDestroyed()) return;
	MoveTo(GetX(), GetY() - 1);
}


//Dawnbreaker
Dawnbreaker::Dawnbreaker(int x, int y, WorldBase* worldptr) : 
	GameObject(IMGID_DAWNBREAKER, x, y, 0, 0, 1.0), HP(100), energy(10), theWorld(worldptr) {}

bool Dawnbreaker::IsEnemy() {
	return false;
}

void Dawnbreaker::Update() {
	if (HP == 0) DestroyIt();
	if (JudgeDestroyed()) return;
	if (energy < 10) energy += 1;
	if (theWorld->GetKey(KeyCode::UP)) {
		if (GetY() + 5 <= WINDOW_HEIGHT - 1)
			MoveTo(GetX(), GetY() + 4);
	}
	if (theWorld->GetKey(KeyCode::DOWN)) {
		if (GetY() - 4 >= 0)
			MoveTo(GetX(), GetY() - 4);
	}
	if (theWorld->GetKey(KeyCode::LEFT)) {
		if (GetX() - 4 >= 0)
			MoveTo(GetX() - 4, GetY());
	}
	if (theWorld->GetKey(KeyCode::UP)) {
		if (GetY() + 4 <= WINDOW_WIDTH - 1)
			MoveTo(GetX(), GetY() + 4);
	}
}

