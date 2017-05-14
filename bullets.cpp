#include "bullets.h"
#include "collisionStrategy.h"
#include "gamedata.h"
#include "ioManager.h"

Bullets::Bullets(const std::string & n) :
  name(n),
  frameInterval(_gd.getXmlInt(name+"/interval")),
  timeSinceLastFrame(0),
  bulletList(),
  freeList()
{}

bool Bullets::colliedWith(const Drawable* obj) const {
  PerPixelCollisionStrategy cs;
  std::list<Acron>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    if(cs.execute(*ptr, *obj)) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
      return true;
    }
    ++ptr;
  }
  return false;
}

void Bullets::shoot(const Vector2f& pos, const Vector2f& vel, bool face) {
  if(timeSinceLastFrame > frameInterval) {
    if(freeList.empty()) {
      Acron b(name, pos, vel);
      bulletList.push_back(b);
    }
    else {
      Acron b = freeList.front();
      freeList.pop_front();
      b.reset(pos, vel, face);
      bulletList.push_back(b);
    }
    timeSinceLastFrame = 0;
  }
}

void Bullets::draw() const {
  IOManager::getInstance().printMessageValueAt("Bullets: ", bulletCount(), 700, 20);
  IOManager::getInstance().printMessageValueAt("FreeList: ", freeCount(), 700, 40);
  std::list<Acron>::const_iterator ptr = bulletList.begin();
  while(ptr != bulletList.end()) {
    ptr->draw();
    ++ptr;
  }
}

void Bullets::update(unsigned __int32 ticks) {
  timeSinceLastFrame += ticks;
  std::list<Acron>::iterator ptr = bulletList.begin();
  while(ptr != bulletList.end()) {
    ptr->update(ticks);
    if(ptr->landing()) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
    }
    else ++ptr;
  }
}
