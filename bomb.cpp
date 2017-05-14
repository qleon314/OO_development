#include "gamedata.h"
#include "frameFactory.h"
#include "collisionStrategy.h"
#include "bomb.h"

Bomb::Bomb(const std::string& name, Bee & b) :
  Pendant(name, b),
  isExplode(false),
  runOneTime(false),
  explosion(MultiSprite("explosion")),
  sound()
{
  anchor(); 
}

void Bomb::draw() const {
  if(!isExplode) {
    unsigned __int32 x = static_cast<unsigned __int32>(X());
    unsigned __int32 y = static_cast<unsigned __int32>(Y());
    int zx = bee.getDirection() ? -1 : 1;
    frames[currentFrame]->draw(x, y, 0, zx, 1);
  } else if(!explosion.isDone()) {
    explosion.draw();
  }
}

void Bomb::update(unsigned __int32 ticks) {
  advanceFrame(ticks);

  if(detached) {
    // falling
    velocityY(velocityY() + 0.2 * static_cast<float>(ticks));
    // to ground : start explode
    if(isExplode) {
      if(runOneTime == false) {
        sound[2];
        runOneTime = true;
      }
      explosion.update(ticks);
      if(explosion.isDone()) setFinished(true);
    } else if(Y() > worldHeight - frameHeight - 20) {
      setPosition(Vector2f(X(), worldHeight - frameHeight - 20));
      setVelocity(Vector2f());
      explode();
    }
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}

void Bomb::anchor() {
  setPosition(bee.getPosition() + bee.getAnchorPos());
  setVelocity(bee.getVelocity());
  setDetached(false);
  setFinished(false);
  isExplode = false;
  runOneTime = false;
}

void Bomb::detach() {
  setVelocity(Vector2f(bee.velocityX() / 2, 0));
  setDetached(true);
}

void Bomb::explode() {
  isExplode = true;
  explosion.setVelocity(getVelocity());
  explosion.setPosition(getPosition());
  explosion.X(X()+getFrame()->getWidth()/2-explosion.getFrame()->getWidth()/2);
  explosion.Y( worldHeight - explosion.getFrame()->getHeight() - 20);
  explosion.start();
}

bool Bomb::collidedWith(const Drawable * d) const {
  if(!isExplode) return false;
  PerPixelCollisionStrategy cs; // TODO: rectangular is better
  return cs.execute(explosion, *d);
}

void Bomb::advanceFrame(unsigned __int32 ticks) {
  if(!detached) currentFrame = 0;
  else if(currentFrame < numberOfFrames - 1) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
      currentFrame = currentFrame + 1;
      timeSinceLastFrame = 0;
    }
  }

}
