#include <SDL2/SDL.h>
#include <stdio.h>

#define PROGNAME "tm"

static struct {
  SDL_Window *window;
  SDL_Surface *surface;
  const int WIDTH;
  const int HEIGHT;
}
Ctx = { NULL, NULL, 640, 480 };

static void init(void);
