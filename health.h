#ifndef HEALTH__H
#define HEALTH__H

#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"

class Health {
public:
  Health(const std::string & name);
  Health(int sx, int sy, int tl, int cl, 
         float t, int inc, unsigned __int32 c, float sp);
  void draw() const;
  void update(unsigned __int32);
  void reset() { currentLength = totalLength / 2; }
  void updateValue(int val);
  int getCurrentLength() { return currentLength; }
private:
  SDL_Surface* screen;
  Vector2f start;
  int totalLength;
  int currentLength;
  int thick;
  int increments;
  float interval;
  int deltaTime;
  const unsigned __int32 RED;
  const unsigned __int32 GRAY;
  const unsigned __int32 BLACK;
  const unsigned __int32 color;
  void drawBox() const;
  Health(const Health&);
  Health& operator=(const Health&);
};

#endif
