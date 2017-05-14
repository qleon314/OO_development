#include "multiwaysprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <iostream>

MultiWaySprite::MultiWaySprite(const std::string& name) :
  Drawable(name, 
           Vector2f(_gd.getXmlInt(name+"/startLoc/x"), 
                    _gd.getXmlInt(name+"/startLoc/y")), 
           Vector2f()
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(_gd.getXmlInt("world/width")),
  worldHeight(_gd.getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( _gd.getXmlInt(name+"/frames") ),
  frameInterval( _gd.getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  zoomx(1),
  zoomy(1),
  v(Vector2f(_gd.getXmlInt(name+"/speedX"),
      _gd.getXmlInt(name+"/speedY")))
{ }

MultiWaySprite::MultiWaySprite(const MultiWaySprite& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  zoomx(s.zoomx),
  zoomy(s.zoomy),
  v(s.v)
{ }

void MultiWaySprite::draw() const { 
  unsigned __int32 x = static_cast<unsigned __int32>(X());
  unsigned __int32 y = static_cast<unsigned __int32>(Y());
  frames[currentFrame]->draw(x, y, 0, zoomx, zoomy);
}

void MultiWaySprite::update(unsigned __int32 ticks) { 
  advanceFrame(ticks);

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

  zoomx = velocityX() > 0 ? 1 : -1;
}

void MultiWaySprite::advanceFrame(unsigned __int32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
  //std::cout << "MultiWaySprite::advanceFrame" << std::endl;
}
