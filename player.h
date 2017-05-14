#ifndef PLAYER__H
#define PLAYER__H

#include "multiwaysprite.h"
#include "bullets.h"

  enum PlayerStatus {
    MOVELEFT = 0,
    MOVERIGHT,
    LAYDOWN,
    STAND,
    BLOWN,
    THROW
};

class Player : public MultiWaySprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual ~Player() {}

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

  void setstatus(PlayerStatus s) { state = s; }

  void shoot();
  bool hit(const Drawable* obj);

  bool getGameOver() { return gameOver; }
  void setGameOver() { gameOver = true; }

private:
  PlayerStatus state;
  Bullets bullets;
  bool gameOver;

  virtual void advanceFrame(unsigned __int32 ticks);
  void setCurrentFrame(unsigned min, unsigned max);
};

#endif
