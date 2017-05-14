#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "menumanager.h"
#include "manager.h"

MenuManager::~MenuManager() {
  SDL_FreeSurface(menubacksurface);
  SDL_FreeSurface(instructionsurface);
}

MenuManager::MenuManager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  parser( "xmlSpec/menu.xml" ),
  screen( io.getScreen() ),
  menubacksurface( io.loadAndSet( parser.getXmlStr("back/file"), false )), 
  instructionsurface( io.loadAndSet( parser.getXmlStr("instruction/file"), false )),
  clock( Clock::getInstance() ),
  title(parser.getXmlStr("screenTitle")),
  menu(),
  numberOfSprites(-1)
{ 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }  
  SDL_WM_SetCaption(title.c_str(), NULL);
  SDL_WM_SetCaption( "Faceless Beeeeeeeeee", NULL );

  atexit(SDL_Quit); 
}

void MenuManager::drawBackground() const {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, 0, 0, 0) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( menubacksurface, NULL, screen, &dest );
}

void MenuManager::drawInstruction() const {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, 0, 0, 0) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( instructionsurface, NULL, screen, &dest );
}

void MenuManager::showInstruction() {
  drawInstruction();
  SDL_Event event;
  bool done = false;
  while ( !done ) {
    Uint8 *keystate = SDL_GetKeyState(NULL);
    while ( SDL_PollEvent(&event) )
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
        }
      }
    }
    if ( !done ) {
      SDL_Flip(screen);
      
    }
  }
}
void MenuManager::getNumberOfSprites() {
  IOManager& io = IOManager::getInstance().getInstance();
  SDL_Event event;
  bool done = false;
  bool nameDone = false;
  const string msg("How many sprites: ");
  io.clearString();
  while ( !done ) {
    Uint8 *keystate = SDL_GetKeyState(NULL);
    while ( SDL_PollEvent(&event) )
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
        }
        if (keystate[SDLK_RETURN]) {
          nameDone = true;
        }
        io.buildString(event);
      }
    }
    drawBackground();
    io.printStringAfterMessage(msg, 20, 120);
    if ( nameDone ) {
      std::string number = io.getString();
      std::stringstream strm;
      strm << number;
      strm >> numberOfSprites;
      strm.clear(); // clear error flags
      strm.str(std::string()); // clear contents
      strm << "Okay -- you'll see " << numberOfSprites << " stars";
      io.printMessageAt(strm.str(), 20, 160);
      SDL_Flip(screen);
      SDL_Delay(1000);
      done = true;
    }
    if ( !done ) {
      SDL_Flip(screen);
    }
  }
}

void MenuManager::play() {
  SDL_Event event;
  bool done = false;

  while ( !done ) {
    drawBackground();
    menu.draw();
    SDL_Flip(screen);
    while ( SDL_PollEvent(&event) ) {
      if (event.type ==  SDL_QUIT) { break; }
      if(event.type == SDL_KEYDOWN) {
        switch ( event.key.keysym.sym ) {
          case SDLK_ESCAPE :
          case SDLK_q : {
            done = true;
            break;
          }
          case SDLK_RETURN : {
            menu.lightOn();
            if ( menu.getIconClicked() == "Normal Mode" ) {
              Manager manager;
              manager.createBees();
              manager.play();
            }

            if ( menu.getIconClicked() == "GOD MODE" ) {
              Manager manager;
              manager.setGodMode();
              manager.createBees();
              manager.play();
            }

            if ( menu.getIconClicked() == "Insain" ) {
              Manager manager;
              manager.setInsain();
              manager.createBees();
              manager.play();
            }
            if ( menu.getIconClicked() == "Help" ) {
              showInstruction();
            }
            if ( menu.getIconClicked() == "Exit" ) {
              drawBackground();
              menu.draw();
              SDL_Flip(screen);
              SDL_Delay(250);
              done = true;
            }
          }
          break;
          case SDLK_DOWN   : {
              menu.increment();
            break;
          }
          case SDLK_UP   : {
              menu.decrement();
            break;
          }
          default          : break;
        }
      }
      if(event.type == SDL_KEYUP) { 
        menu.lightOff();
      }
    }
  }
}
