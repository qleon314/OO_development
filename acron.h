#ifndef ACRON__H
#define ACRON__H

#include "sprite.h"

class Acron : public Sprite {
public:
	Acron(const std::string&);
	Acron(const std::string&, const Vector2f&, const Vector2f&);
  virtual ~Acron() {};

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);

  bool landing();
  void reset(const Vector2f &, const Vector2f &, bool);
private:
	Vector2f v;
	float rotate;
};

#endif
