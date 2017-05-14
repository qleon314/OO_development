#include "gamedata.h"
#include "frameFactory.h"
#include "player.h"

Player::Player( const std::string& name) :
  MultiWaySprite(name),
  state(STAND),
  bullets("acorn"),
  gameOver(false)
{ }

Player::Player(const Player& s) :
  MultiWaySprite(s),
  state(s.state),
  bullets(s.bullets),
  gameOver(s.gameOver)
{ }

void Player::draw() const { 
  unsigned __int32 x = static_cast<unsigned __int32>(X());
  unsigned __int32 y = static_cast<unsigned __int32>(Y());
  if( !gameOver ){
    frames[currentFrame]->draw(x, y, 0, zoomx, zoomy);
    bullets.draw();
  }
}

void Player::update(unsigned __int32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  switch(state) {
  case STAND:
    velocityX(0);
    velocityY(0);
    break;
  case MOVELEFT:
    velocityX( -abs(v[0]) );
    zoomx = -1;
    break;
  case MOVERIGHT:
    velocityX( abs(v[0]) );
    zoomx = 1;
    break;
  default:
    break;
  }

  if ( X() < 0) {
    velocityX(0);
    X(0);
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX(0);
    X(worldWidth-frameWidth);
  }
  bullets.update(ticks);
}

void Player::advanceFrame(unsigned __int32 ticks) {
  unsigned min = 0;
  unsigned max = 0;

  switch(state){
    case MOVELEFT:
    case MOVERIGHT:
      min = 0; max = 4; break;
    case THROW:
      min = 9; max = 14; break;
    case BLOWN:
      min = 15; max = 17; break;
    case STAND:
    default:
      min = 5; max = 8; break;
  }

  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    setCurrentFrame(min, max);
    timeSinceLastFrame = 0;
  }
}

void Player::setCurrentFrame(unsigned min, unsigned max) {
  currentFrame++;
  if(currentFrame > max || currentFrame < min) currentFrame = min;
}

void Player::shoot() {
  float x = X() + 20;
  float y = Y() + 20;
  bool face = zoomx > 0 ? false : true;
  bullets.shoot(Vector2f(x, y), getVelocity(), face);
}

bool Player::hit(const Drawable* obj) {
  return bullets.colliedWith(obj);
}
