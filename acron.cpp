#include <cmath>
#include "gamedata.h"
#include "frameFactory.h"
#include "acron.h"

Acron::Acron(const std::string& name) : 
  Sprite(name),
  v(Vector2f(
    abs(_gd.getXmlFloat(name+"/speedX")),
    -abs(_gd.getXmlFloat(name+"/speedY")))
  ),
  rotate(_gd.getXmlFloat(name + "/rotate"))
{ }

Acron::Acron(const std::string& name, const Vector2f& pos, const Vector2f& vel) :
  Sprite(name, pos, vel),
  v(Vector2f(
    abs(_gd.getXmlFloat(name+"/speedX")),
    -abs(_gd.getXmlFloat(name+"/speedY")))
  ),
  rotate(_gd.getXmlFloat(name + "/rotate"))
{
  reset(pos, vel, 0);
}

void Acron::draw() const { 
  unsigned __int32 x = static_cast<unsigned __int32>(X());
  unsigned __int32 y = static_cast<unsigned __int32>(Y());
  frame->draw(x, y, rotate); 
}

void Acron::update(unsigned __int32 ticks) {
/*
  if(velocityX() > 0) {
    float v = velocityX() - 0.5 * static_cast<float>(ticks);
    velocityX(std::max(v, 0.0f));
  } else if(velocityX() < 0) {
    float v = velocityX() + 0.5 * static_cast<float>(ticks);
    velocityX(std::min(v, 0.0f));
  }
*/
  velocityY(velocityY() + 0.4 * static_cast<float>(ticks));

  if(landing()) {
    Y(worldHeight-frameHeight - 20);
    setVelocity(Vector2f());
  } else {
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
  }

  rotate += _gd.getXmlFloat(getName() + "/rotate");
}

bool Acron::landing() {
  return Y() >= worldHeight-frameHeight - 20;
}

void Acron::reset(const Vector2f & pos, const Vector2f & vel, bool face) {
  setPosition(pos);
  setVelocity(vel); // for disable warning
  setVelocity(v);
  float incr(abs(_gd.getXmlFloat(getName() + "/speedXShift")));
  if(face) velocityX(-v[0] - incr);
  else velocityX(v[0] + incr);
}

