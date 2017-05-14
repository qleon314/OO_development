#include <SDL.h>
#include "menu.h"
#include "clock.h"
#include "ioManager.h"
#include "vector2f.h"

class MenuManager {
public:
  MenuManager ();
  ~MenuManager();
  void play();

private:
  bool env;  
  const IOManager& io;
  ParseXML parser;
  SDL_Surface *screen;
  SDL_Surface *menubacksurface;
  SDL_Surface *instructionsurface;
  const Clock& clock;
  const std::string title;


  
//  SDL_Color backColor;
  Menu menu;
  int numberOfSprites;

  void drawBackground() const;
  void drawInstruction() const;
  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
  void getNumberOfSprites();
  void showInstruction();
};
