#define PROGNAME "tm"

enum exitstatus { SUCCESS = 0, FAILURE = 1, INITFAILURE = 2 };
enum millisecond { SECOND = 1000 };
enum status { NOTRUNNING = 0, RUNNING = 1 };

static struct context {
  SDL_Window *win;
  SDL_Surface *sfc;
  struct lay_context lctx;
  char **argv;
  int argc;
  enum status flags;
  const int FPSDESIGNED;
  const int WIDTH;
  const int HEIGHT;
} Ctx = { NULL, NULL, { NULL, NULL, 0, 0 }, NULL, 0, NOTRUNNING, 60, 640, 480 };

static void init(void);
static void initlayout(void);
static void handleevents(void);
static void handlekeydown(SDL_KeyboardEvent kev);
static void update(void);
static void render(void);
static void printscreen(void);
static void quit(void);
