#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "bee.h"
#include "jar.h"
#include "bomb.h"
#include "hud.h"
#include "health.h"
#include "sound.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  bool play();
  void pause() { clock.pause(); }
  void unpause() { clock.unpause(); }
  void setGodMode() { isGodMode = true; }
  void setInsain() { isInsain = true; }
  int getJar() const { return jarCaptured; }
  void createBees();

 

private:
  const bool env;
  const IOManager& io;
  Clock& clock;


  SDL_Surface * const screen;

  SDLSound sound;
  Viewport& viewport;
  std::vector<World*> worlds;
  std::vector<Drawable*> bees;
  std::vector<Drawable*> sprites;
  Player * player;
  Hud hud;
  Health health;

  bool makeVideo;
  bool isCollision;
  bool isDead;
  bool isGodMode;
  bool isInsain;
  bool isWritten;
  int frameCount;
  int jarCaptured;
  unsigned interval;
  unsigned tickos;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  void drawGameOver() const;
  void update();

  int getBestScore() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();

  void buildWorld();

  void checkForCollisions();

  void randomDropBomb();
};
