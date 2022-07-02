#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#define PROGNAME "tm"

typedef enum Boolean { false = 0, true = 1 } bool;
enum ExitStatus { SUCCESS = 0, FAILURE = 1, INITFAILURE = 2 };
enum Millisecond { SECOND = 1000 };

static struct Context {
  SDL_Window *win;
  SDL_Surface *sfc;
  int argc;
  char **argv;
  bool isrunning;
  const unsigned char FPSDESIGNED;
  const unsigned short WIDTH;
  const unsigned short HEIGHT;
}
Ctx = { NULL, NULL, 0, NULL, 0, 30, 640, 480 };

static void init(void);
static void handleevents(void);
static void handlekeydown(SDL_KeyboardEvent kev);
static void printscreen(void);
static void quit(void);
