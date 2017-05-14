#include <SDL.h>

class ExtractSurface {
public:
  static ExtractSurface& getInstance();
  SDL_Surface* get(SDL_Surface*, int, int, int, int) const;
private:
  unsigned __int32 getpixel(SDL_Surface*, int, int) const;
  void putpixel(SDL_Surface *, int, int, unsigned __int32) const;
};
