#define PROGNAME "tm"

enum exitstatus { SUCCESS = 0, FAILURE = 1, INITFAILURE = 2 };
enum millisecond { SECOND = 1000 };
enum status { NOTRUNNING = 0, RUNNING = 1 };

static struct context {
  SDL_Window *win;
  SDL_Surface *sfc;
  int argc;
  char **argv;
  enum status status;
  const unsigned int FPSDESIGNED;
  const unsigned int WIDTH;
  const unsigned int HEIGHT;
}
Ctx = { NULL, NULL, 0, NULL, NOTRUNNING, 30, 640, 480 };

static void init(void);
static void handleevents(void);
static void handlekeydown(SDL_KeyboardEvent kev);
static void printscreen(void);
static void quit(void);
