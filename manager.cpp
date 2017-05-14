#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "gamedata.h"
#include "manager.h"
#include "aaline.h"
#include "collisionStrategy.h"

using namespace std;

Manager::~Manager() {
  delete player;
  for (unsigned i = 0; i < bees.size(); ++i) {
    delete bees[i];
  }
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  for (unsigned i = 0; i < worlds.size(); ++i) {
    delete worlds[i];
  }

}

Manager::Manager() :
  env( SDL_putenv( const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  sound(),
  viewport( Viewport::getInstance() ),
  worlds(),
  bees(),
  sprites(),
  player( new Player("faceless") ),
  hud("hud"),
  health("health"),
  makeVideo( false ),
  isCollision(false),
  isDead(false),
  isGodMode(false),
  isInsain(false),
  isWritten(false),
  frameCount( 0 ),
  jarCaptured( 0 ),
  interval(700),// TBD
  tickos(0),
  username(_gd.getXmlStr("username") ),
  title(_gd.getXmlStr("screenTitle") ),
  frameMax(_gd.getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  buildWorld();
  //createBees();
  viewport.setObjectToTrack(player);
  SDL_WM_SetCaption( "Faceless Beeeeeeeeee", NULL );
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::buildWorld() {
  worlds.reserve(7);
  worlds.push_back(new World("back1"));
  worlds.push_back(new World("back2"));
  worlds.push_back(new World("back3"));
  worlds.push_back(new World("back4"));
  worlds.push_back(new World("back5"));
  worlds.push_back(new World("back6"));
  worlds.push_back(new World("back7"));

  std::sort(worlds.begin(), worlds.end(), FactorCompare());
}

void Manager::createBees() {
  unsigned countBee = _gd.getXmlInt("bee/count");
  bees.reserve( countBee );
  sprites.reserve( countBee );
  for( unsigned i = 0; i < countBee; ++i ) {
    Bee * b = new Bee("bee", *player);
    bees.push_back(b);
    Drawable *hang;
    if( isGodMode == true ) {
      sprites.push_back(new Jar("jar", *b));
    }
    if( isInsain == true ) {
      sprites.push_back(new Bomb("bomb", *b));
    }
    else {
      int rd = _gd.getRandInRange(0, 2);
      if(rd == 0) hang = new Bomb("bomb", *b);
      else hang = new Jar("jar", *b);
      sprites.push_back(hang);
    }
  }
}


//TODOPP
void Manager::checkForCollisions() {
    for(unsigned i = 0; i < sprites.size(); ++i) {
      if(sprites[i]->collidedWith(player)) {
        if(sprites[i]->getName() == "bomb" && !isGodMode) {
          if(clock.getTicks() - tickos > interval) {
            tickos = clock.getTicks();
            isCollision = true;
            health.updateValue(-40);
            player->setstatus(BLOWN);
            break;
          }
        } 
        else if(sprites[i]->getName() =="jar" && !isInsain){    
          if(clock.getTicks() - tickos > interval) {
            tickos = clock.getTicks();
            isCollision = true;
            dynamic_cast<Jar*>(sprites[i])->getCollide();
            sound[1];
            health.updateValue(30);
            ++jarCaptured;
            break;
          }
        }
      }
    }
  // bees get collide with ammo
  for(unsigned i = 0; i < bees.size(); ++i) {
    if(player->hit(bees[i])) {
      static_cast<Bee*>(bees[i])->getHit();
      break;
    }
  }

}

void Manager::randomDropBomb() {
  int index = _gd.getRandInRange(0, bees.size());
  int rd = _gd.getRandInRange(0, 50);
  if(rd == 5 && sprites[index]->getName() == "bomb")
    static_cast<Bee*>(bees[index])->getHit();
}

void Manager::draw() const {
  for(unsigned int i = 0; i < worlds.size();++i) {
    worlds[i]->draw();
  }
  player->draw();
  io.printMessageValueAt("Jars: ", getJar(), 700, 60);

  if(isDead){
    io.printgameoverCenteredAt("GAME OVER", 200); 
    io.printMessageAt("Press Esc to start a new game!", 300, 100);//?
    io.printMessageValueAt("Your Score ", getJar(), 380, 340);  
    io.printMessageValueAt("Best Score ", getBestScore(), 380, 370);  
    }

  for (unsigned i = 0; i < bees.size(); ++i) {
    bees[i]->draw();
  }
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  hud.draw();
  health.draw();
  viewport.draw();

  SDL_Flip(screen);
}

void Manager::update() {
  ++clock;
  unsigned __int32 ticks = clock.getElapsedTicks();
  for(unsigned int i = 0; i < worlds.size();++i) {
    worlds[i]->update();
  }
  for (unsigned int i = 0; i < bees.size(); ++i) {
    bees[i]->update(ticks);
  }
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  player->update(ticks);
  hud.update(ticks);
  health.update(ticks);

  if(health.getCurrentLength() > 0) {
    checkForCollisions(); 
    randomDropBomb();
  }
  else {
        player->setGameOver();
        isDead = true;
        if(!isWritten) {
          ofstream myfile;
          myfile.open ("example.txt",ios::ate|ios::app);
          myfile << getJar() <<"\n";
          myfile.close();
          isWritten = true;
        }
        getBestScore();
      }

  viewport.update();

  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
}

int Manager::getBestScore() const {
  std::ifstream ifs("example.txt");
  int score[100];
  int n=1,i=0,lines = 0;
  while(ifs>>n){
    score[i]=n;
    i++;
  }
  lines = i - 1;
  sort(score, score + lines);

  return score[lines - 1];
}

bool Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( !done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }

    if(event.type == SDL_KEYUP) { 
      keyCatch = false;
      player->setstatus(STAND);
    }

    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      /*if (keystate[SDLK_t] && !keyCatch) {
        keyCatch = true;
        sound.toggleMusic();
      }*/
      if (keystate[SDLK_r] && !keyCatch) {
        keyCatch = true;
        return true;
        break;
      }
      if (keystate[SDLK_m] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_F4] && !makeVideo) {
        std::cout << "Making video frames" << std::endl;
        makeVideo = true;
      }
      if (keystate[SDLK_F1] && !keyCatch) {
        keyCatch = true;
        hud.toggle();
      }
      if (keystate[SDLK_v] && !keyCatch) {
        keyCatch = true;
        unsigned index = _gd.getRandInRange(0, bees.size());
        static_cast<Bee*>(bees[index])->getHit();
      }
    }

    if (keystate[ SDLK_LEFT ]) {
      player->setstatus(MOVELEFT);
    }

    if (keystate[ SDLK_RIGHT ]) {
      player->setstatus(MOVERIGHT);
    }

    if (keystate[ SDLK_DOWN ]) {
      player->setstatus(LAYDOWN);
    }

    if (keystate[SDLK_SPACE]) {
      player->shoot();
      player->setstatus(THROW);
      sound[0]; 
    }

    draw();
    update();
  }
  return false;
}

