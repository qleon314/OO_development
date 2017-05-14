#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

MultiSprite::MultiSprite(const std::string& name) :
  Drawable(name, 
          Vector2f(_gd.getXmlInt(name+"/startLoc/x"),
                    _gd.getXmlInt(name+"/startLoc/y")),
          Vector2f(_gd.getXmlInt(name+"/speedX"),
                    _gd.getXmlInt(name+"/speedY"))
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
  angle(0),
  scale(1),
  startFlag(false),
  endFlag(false)
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
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
  angle( s.angle ),
  scale( s.scale ),
  startFlag(s.startFlag),
  endFlag(s.endFlag)
{ }

void MultiSprite::draw() const { 
  if(startFlag && !endFlag) {
    unsigned __int32 x = static_cast<unsigned __int32>(X());
    unsigned __int32 y = static_cast<unsigned __int32>(Y());
    frames[currentFrame]->draw(x, y, angle, scale, scale);    
  }
}

void MultiSprite::update(unsigned __int32 ticks) { 
  if(startFlag && !endFlag) {
   advanceFrame(ticks);
  }
}

void MultiSprite::advanceFrame(unsigned __int32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = currentFrame + 1;
    timeSinceLastFrame = 0;
  }
  if(currentFrame == numberOfFrames) {
    endFlag = true;
  }
}

void MultiSprite::start() {
  startFlag = true;
  endFlag = false;
  currentFrame = 0;
}
