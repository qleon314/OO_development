#ifndef BOMB__H
#define BOMB__H

#include "pendant.h"
#include "multisprite.h"
#include "sound.h"

class Bomb : public Pendant {
public:
  Bomb(const std::string&,  Bee &);
  virtual ~Bomb() {}

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);

  virtual void anchor();
  virtual void detach();

  virtual bool collidedWith(const Drawable *) const;

private:
	bool isExplode;
  bool runOneTime;  // explode
	MultiSprite explosion;
	void explode();
  SDLSound sound;

  virtual void advanceFrame(unsigned __int32 ticks);
  
};

#endif
