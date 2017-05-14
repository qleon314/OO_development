#include "gamedata.h"
#include "frameFactory.h"
#include "pendant.h"

Pendant::Pendant(const std::string& name, Bee & b) :
  MultiWaySprite(name),
  bee(b),
  finished(false),
  detached(false)
{
  b.attach(this);
}
