#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  virtual ~MultiSprite() { } 

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[numberOfFrames-1]; 
  }

  void start();
  bool isDone() const { return startFlag && endFlag; }

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

  float angle;
  float scale;

  bool startFlag;
  bool endFlag;

  virtual void advanceFrame(unsigned __int32 ticks);

};

#endif
