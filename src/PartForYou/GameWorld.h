#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>
#include "GameObjects.h"
#include "WorldBase.h"

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

private:
	std::list<GameObject> ObjectList;
};

#endif // !GAMEWORLD_H__
