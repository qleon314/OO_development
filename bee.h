#ifndef BEE__H
#define BEE__H

#include "multiwaysprite.h"
#include "pendant.h"
#include "player.h"

enum BeeStatus {
  NORMAL,
  BLOWUP
};

class Pendant;

class Bee : public MultiWaySprite {
public:
  Bee(const std::string&, const Player &);
  virtual ~Bee() {;}

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);

  const Vector2f & getAnchorPos() { return anchorPos; }

  void getHit() { status = BLOWUP; }

  void attach(Pendant * obs) { pendant = obs; }

  bool getDirection() { return direction; }

  virtual bool collidedWith(const Drawable *) const { return false; };

private:
  BeeStatus status;
  bool flag;  // blow up once
  bool direction; // 0 right, 1 left
  Vector2f anchorPos;
  Pendant * pendant;
  const Player & enemy;
  
  void initialize();
  void reInit();
  void notify(BeeStatus status);

  Bee & operator=(const Bee &);
  Bee(const Bee &);
};

#endif
