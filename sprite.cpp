#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(_gd.getXmlInt(name+"/startLoc/x"), 
                _gd.getXmlInt(name+"/startLoc/y")), 
           Vector2f(_gd.getXmlInt(name+"/speedX"), 
                _gd.getXmlInt(name+"/speedY"))),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(_gd.getXmlInt("world/width")),
  worldHeight(_gd.getXmlInt("world/height"))
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(_gd.getXmlInt("world/width")),
  worldHeight(_gd.getXmlInt("world/height"))
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(_gd.getXmlInt("world/width")),
  worldHeight(_gd.getXmlInt("world/height"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(_gd.getXmlInt("world/width")),
  worldHeight(_gd.getXmlInt("world/height"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Sprite::draw() const { 
  unsigned __int32 x = static_cast<unsigned __int32>(X());
  unsigned __int32 y = static_cast<unsigned __int32>(Y());
  frame->draw(x, y); 
}

int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(unsigned __int32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
