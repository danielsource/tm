#include "main.h"

int
main(/*int argc, char **argv*/)
{
  init();
  SDL_Delay(3000);
  SDL_DestroyWindow(Ctx.window);
  SDL_Quit();
  return 0;
}

static void
init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, PROGNAME": %s\n", SDL_GetError() );
    exit(2);
  }
  if (!(Ctx.window = SDL_CreateWindow(PROGNAME,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      Ctx.WIDTH,
                                      Ctx.HEIGHT,
                                      SDL_WINDOW_SHOWN))) {
    fprintf(stderr, PROGNAME": %s\n", SDL_GetError() );
    exit(2);
  }
  Ctx.surface = SDL_GetWindowSurface(Ctx.window);
}
