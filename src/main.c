#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#include "main.h"
#include "layout.h"

int
main(int argc, char **argv)
{
  Uint64 ticks;
  unsigned int delta, delay = SECOND / Ctx.FPSDESIGNED;
  /* LAYOUT STUFF */
  struct lay_context lctx;
  lay_id root, list;
  float w, h;
  /* ============ */
  Ctx.argc = argc;
  Ctx.argv = argv;
  init();
  /* LAYOUT STUFF */
  lay_init(&lctx);
  lay_reserve(&lctx, 20);
  root = lay_createitem(&lctx);
  lay_setsize(&lctx, root, Ctx.WIDTH, Ctx.HEIGHT);
  lay_getsize(&lctx, root, &w, &h);
  lay_setparentflags(&lctx, root, LAY_ROW);
  printf("root: %fx%f\n", w, h);
  list = lay_createitem(&lctx);
  lay_insert(&lctx, root, list);
  lay_setsize(&lctx, list, 400, 0);
  lay_setchildflags(&lctx, list, LAY_VFILL);
  lay_getsize(&lctx, list, &w, &h);
  printf("list: %fx%f\n", w, h);
  /* ============ */
  while (Ctx.status == RUNNING) {
    ticks = SDL_GetTicks64();
    handleevents();
    delta = SDL_GetTicks64() - ticks;
    if (delta < delay)
      SDL_Delay(delay - delta);
  }
  quit();
  return SUCCESS;
}

void
init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, PROGNAME": %s\n", SDL_GetError());
    exit(INITFAILURE);
  }
  if (!(Ctx.win = SDL_CreateWindow(PROGNAME,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   Ctx.WIDTH,
                                   Ctx.HEIGHT,
                                   SDL_WINDOW_SHOWN))) {
    fprintf(stderr, PROGNAME": %s\n", SDL_GetError());
    exit(INITFAILURE);
  }
  Ctx.sfc = SDL_GetWindowSurface(Ctx.win);
  Ctx.status = RUNNING;
}

void
handleevents()
{
  SDL_Event ev;
  while (SDL_PollEvent(&ev))
    switch (ev.type) {
    case SDL_QUIT:
      Ctx.status = NOTRUNNING;
      return;
    case SDL_KEYDOWN:
      handlekeydown(ev.key);
      return;
    }
}

void
handlekeydown(SDL_KeyboardEvent kev)
{
  switch (kev.keysym.scancode) {
  case SDL_SCANCODE_W:
    puts("W");
    return;
  case SDL_SCANCODE_A:
    puts("A");
    return;
  case SDL_SCANCODE_S:
    puts("S");
    return;
  case SDL_SCANCODE_D:
    puts("D");
    return;
  default:
    break;
  }
  switch (kev.keysym.sym) {
  case SDLK_ESCAPE:
    Ctx.status = NOTRUNNING;
    return;
  case SDLK_INSERT:
    printscreen();
    return;
  }
}

void
printscreen(void)
{
  enum { sz = 24 };
  static const char fmt[] = "%Y-%m-%d-%H-%M-%S.bmp";
  static char filename[sz] = "";
  static time_t raw;
  static struct tm *t;
  time(&raw);
  t = localtime(&raw);
  strftime(filename, sz, fmt, t);
  if (SDL_SaveBMP(Ctx.sfc, filename) < 0) {
    fprintf(stderr, PROGNAME": %s\n", SDL_GetError());
    return;
  }
  puts(filename);
}

void
quit(void)
{
  SDL_DestroyWindow(Ctx.win);
  SDL_Quit();
}
