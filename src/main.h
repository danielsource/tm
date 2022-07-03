#define PROGNAME "tm"

enum exitstatus { SUCCESS = 0, FAILURE = 1, INITFAILURE = 2 };
enum millisecond { SECOND = 1000 };
enum status { NOTRUNNING = 0, RUNNING = 1 };

static struct context {
  SDL_Window *win;
  SDL_Surface *sfc;
  int argc;
  char **argv;
  enum status flags;
  const int FPSDESIGNED;
  const int WIDTH;
  const int HEIGHT;
} Ctx = { NULL, NULL, 0, NULL, NOTRUNNING, 60, 640, 480 };

static void init(void);
static void handleevents(void);
static void handlekeydown(SDL_KeyboardEvent kev);
static void printscreen(void);
static void quit(void);
