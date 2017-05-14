#ifndef BULLETS__H
#define BULLETS__H

#include <list>
#include "acron.h"

class Bullets {
public:
  Bullets(const std::string &);
  ~Bullets() {};
  void draw() const;
  void update(unsigned __int32 ticks);

  void shoot(const Vector2f& pos, const Vector2f& vel, bool);
  bool colliedWith(const Drawable* obj) const;

  unsigned bulletCount() const { return bulletList.size(); }
  unsigned freeCount() const { return freeList.size(); }
  bool isShooting() const { return bulletList.empty(); }

private:
  std::string name;
  float frameInterval;
  float timeSinceLastFrame;

  mutable std::list<Acron> bulletList;
  mutable std::list<Acron> freeList;
  
};

#endif
