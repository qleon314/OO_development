#include "gamedata.h"
#include "frameFactory.h"
#include "collisionStrategy.h"  
#include "jar.h"

Jar::Jar(const std::string& name, Bee & b) :
  Pendant(name, b),
  runOneTime(false),
  exploded(false),
  explosion(),
  collided(false)
{
  anchor(); 
}

void Jar::draw() const {
  if(!exploded && !collided) {
    unsigned __int32 x = static_cast<unsigned __int32>(X());
    unsigned __int32 y = static_cast<unsigned __int32>(Y());
    int zx = bee.getDirection() ? -1 : 1;
    frames[currentFrame]->draw(x, y, 0, zx, 1);
  } else if(exploded) {
    explosion->draw();
  }
}

void Jar::update(unsigned __int32 ticks) {
  if(detached) {
    // falling
    velocityY(velocityY() + 0.2 * static_cast<float>(ticks));

    if(collided) {
      setFinished(true);
    } else {
       if(exploded) {
        explosion->update(ticks);
        if ( static_cast<ExplodingSprite*>(explosion)->chunkCount() == 0 ) {
          setFinished(true);
        }
      } else if(Y() > worldHeight - frameHeight - 20) {
        setPosition(Vector2f(X(), worldHeight - frameHeight - 20));
        setVelocity(Vector2f());
        explode();
      }
    }
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}

void Jar::anchor() {
  setPosition(bee.getPosition() + bee.getAnchorPos());
  setVelocity(bee.getVelocity());
  setDetached(false);
  setFinished(false);
  exploded = false;
  collided = false;
}

void Jar::detach() {
  setVelocity(Vector2f(bee.velocityX(), 0));
  setDetached(true);
}

void Jar::explode() {
  exploded = true;
  if( !runOneTime ) {
    runOneTime = true;
    //sound[];
  }
  if(explosion) delete explosion;
  Sprite sprite("jar", getPosition(), v); // v inherits from MultiWaySprite
  explosion = new ExplodingSprite(sprite);

}

bool Jar::collidedWith(const Drawable * d) const {
  if(exploded) return false;
  MidPointCollisionStrategy cs;
  return cs.execute(*this, *d);
}
