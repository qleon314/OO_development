#include "gamedata.h"
#include "frameFactory.h"
#include "bee.h" 

Bee::Bee(const std::string& name, const Player & p) :
  MultiWaySprite(name),
  status(),
  flag(0),
  direction(0),
  anchorPos(getPosition()),
  pendant()
  ,enemy(p)
{
  initialize();
}

void Bee::draw() const {
  unsigned __int32 x = static_cast<unsigned __int32>(X());
  unsigned __int32 y = static_cast<unsigned __int32>(Y());
  int zx = direction ? -1 : 1;
  frames[currentFrame]->draw(x, y, 0, zx, 1);
}

void Bee::update(unsigned __int32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  //!!!!!!!!!!!!!!!!!!!!!!!!TO MODIFY FOR AI
 /* if(pendant && pendant->getName() == "bomb" && status == NORMAL) {
    float px = X();
    float ex = enemy.X();
    if( px- ex > 0)  {
      velocityX(-abs(velocityX()));
      direction = 1;
    }
    else {
      velocityX(abs(velocityX()));
      direction = 0;
    }
  }*/

  if(!flag && status == BLOWUP) {
    flag = 1;
    if(pendant) notify(BLOWUP);
    velocityX(1.5 * velocityX());
    velocityY(-abs(v[1]));
  }

  if(!pendant) {
    reInit();
  } else {
    if(!pendant->isDetach()) reInit();
    else if (pendant->isFinish()) reInit();
  }
}

void Bee::reInit() {
  float upperBound = - 3 * frameHeight;
  float leftBound  = - 3 * frameWidth;
  float rightBound = worldWidth + 3 * frameWidth;
  if (Y() < upperBound || X() < leftBound || X() > rightBound) initialize();
}

void Bee::initialize() {
  // default: towards right
  status = NORMAL;
  flag = 0;
  direction = false;
  setVelocity(Vector2f(_gd.getRandFloat(100, v[0]), 0));
  setPosition(Vector2f(-frameWidth, _gd.getRandFloat(0, worldHeight / 3)));

  int toLeft = _gd.getRandInRange(0, 2);
  if(toLeft) {
    direction = true;
    velocityX(-abs(velocityX()));
    X(worldWidth + frameWidth);
  }

  if(pendant) notify(NORMAL);
}

void Bee::notify(BeeStatus status) {
  if (status == NORMAL) {
    pendant->anchor();
  } else {
    pendant->detach();
  }
}
