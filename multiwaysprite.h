#ifndef MULTIWAYSPRITE__H
#define MULTIWAYSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class MultiWaySprite : public Drawable {
public:
  MultiWaySprite(const std::string&);
  MultiWaySprite(const MultiWaySprite&);
  virtual ~MultiWaySprite() { } 

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  double zoomx;
  double zoomy;

  Vector2f v;

  virtual void advanceFrame(unsigned __int32 ticks);

};

#endif