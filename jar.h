#ifndef JAR__H
#define JAR__H

#include "pendant.h"
#include "explodingSprite.h"

class Jar : public Pendant {
public:
  Jar(const std::string&,  Bee &);
  virtual ~Jar() { if(explosion) delete explosion; }

  virtual void draw() const;
  virtual void update(unsigned __int32 ticks);

  virtual void anchor();
  virtual void detach();

  virtual bool collidedWith(const Drawable *) const;

  void getCollide() { collided = true; }

private:
	bool runOneTime;
	bool exploded;
	ExplodingSprite * explosion;
	void explode();

	bool collided;

	Jar & operator=(const Jar &);
	Jar(const Jar &);
};

class Acceleration {
	float v;
	float a;
public:
	Acceleration(float fv, float fa) : v(fv), a(fa) {}

	float getV(unsigned __int32 ticks) {
		return v + a * static_cast<float>(ticks) * 0.001;
	}
	float getIncr(unsigned __int32 ticks) {
		float t = static_cast<float>(ticks) * 0.001;
		return v * t + a * t * t / 2.0;
	}
};

#endif
