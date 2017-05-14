#ifndef PENDANT__H
#define PENDANT__H

#include "multiwaysprite.h"
#include "bee.h"

class Bee;

class Pendant : public MultiWaySprite {
public:
  Pendant(const std::string&, Bee &);
  virtual ~Pendant() { }

  virtual void anchor() = 0;
  virtual void detach() = 0;

  // finish adjacent event
  virtual bool isFinish() { return finished; }
  void setFinished(bool f) { finished = f; }

  // detach a pendant
  virtual bool isDetach() { return detached; }
  void setDetached(bool d) { detached = d; }

protected:
  Bee & bee;
  bool finished;
  bool detached;
};

#endif
